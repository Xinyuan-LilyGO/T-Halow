#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "osal/irq.h"
#include "osal/semaphore.h"
#include "hal/uart.h"
#include "hal/dma.h"
#include "dev/uart/hguart.h"

static void hguart_dma_tx_irq_hdl(struct dma_device *p_dma, uint32 ch, enum dma_irq_type irq, uint32 data)
{
    struct hguart *dev = (struct hguart *)data;
    dma_stop(p_dma, ch); /* release channel */
    os_sema_up(&dev->tx_dma_sema);
}

static void hguart_dma_rx_irq_hdl(struct dma_device *p_dma, uint32 ch, enum dma_irq_type irq, uint32 data)
{
    struct hguart *dev = (struct hguart *)data;
    dma_stop(p_dma, ch); /* release channel */
    //os_sema_up(&dev->rx_dma_sema);
    dev->irq_hdl(UART_INTR_RX_DATA_AVAIL, dev->irq_data, 0);
}

static int32 hguart_set_baudrate(struct uart_device *uart_t, int32 baudrate)
{
    int32 baudrate_cal = sys_get_apbclk() / baudrate;

    struct hguart *uart = (struct hguart *)uart_t;
#if UART_FIFO_EN
    while ((uart->hw->USR & BIT(2)) == 0);
#else
    while ((uart->hw->LSR & BIT(5)) == 0);
#endif
    uart->hw->LCR |= BIT(7);
    uart->hw->DLL = (uint8)(baudrate_cal >> 4);
    uart->hw->DLH = (uint8)((baudrate_cal >> 4) >> 8);
    uart->hw->DLF = baudrate_cal & 0x0f;
    uart->hw->LCR &= ~BIT(7);
    return RET_OK;
}

static int32 hguart_open(struct uart_device *uart_t)
{
    struct hguart *uart = (struct hguart *)uart_t;
    int32 ret;

    if (uart->opened) {
        return RET_OK;
    }

    ret = os_sema_init(&uart->tx_dma_sema, 0);
    if (ret != RET_OK) {
        return ret;
    }
    ret = os_sema_init(&uart->rx_dma_sema, 0);
    if (ret != RET_OK) {
        os_sema_del(&uart->tx_dma_sema);
        return ret;
    }

    pin_func(uart_t->dev.dev_id, 1);
    uart->hw->MCR = 0x00000000;

    hguart_set_baudrate(uart_t, HGUART_DEFAULT_BAUDRATE);

    uart->hw->LCR = (HGUART_DEFAULT_DATABITS) | (HGUART_DEFAULT_STOPBITS) | (HGUART_DEFAULT_PARITY);
#if UART_FIFO_EN
    //FCR, enable FIFO; reset FIFO; set FIFO trigger
    uart->hw->FCR = 0x01 | 0x06 | (HGUARTx_RXFIFO_TRIG & 0xC0) | (HGUARTx_TXFIFO_TRIG & 0x30);
#else
    //FCR, disable FIFO;
    uart->hw->FCR = 0x00000000;
#endif

    uart->opened = 1;

    return RET_OK;
}

static int32 hguart_close(struct uart_device *uart_t)
{
    struct hguart *uart = (struct hguart *)uart_t;

    if (!uart->opened) {
        return RET_OK;
    }

    pin_func(uart_t->dev.dev_id, 0);
    uart->hw->IER = 0;

    os_sema_del(&uart->tx_dma_sema);
    os_sema_del(&uart->rx_dma_sema);

    uart->opened = 0;

    return RET_OK;
}

static int32 hguart_set_parity(struct uart_device *uart_t, int32 parity)
{
    struct hguart *uart = (struct hguart *)uart_t;
#if UART_FIFO_EN
    while ((uart->hw->USR & BIT(2)) == 0);
#else
    while ((uart->hw->LSR & BIT(5)) == 0);
#endif
    switch (parity) {
        case HGUART_PARITY_NONE: {
            uart->hw->LCR &= ~BIT(3);
            uart->hw->LCR &= ~BIT(4);
        }
        break;
        case HGUART_PARITY_ODD: {
            uart->hw->LCR |=  BIT(3);
            uart->hw->LCR &= ~BIT(4);
        }
        break;
        case HGUART_PARITY_EVEN: {
            uart->hw->LCR |= BIT(3);
            uart->hw->LCR |= BIT(4);
        }
        break;
        default:
            break;
    }
    return RET_OK;
}

static int32 hguart_set_databits(struct uart_device *uart_t, int32 databits)
{
    struct hguart *uart = (struct hguart *)uart_t;
#if UART_FIFO_EN
    while ((uart->hw->USR & BIT(2)) == 0);
#else
    while ((uart->hw->LSR & BIT(5)) == 0);
#endif
    uart->hw->LCR &= ~HGUART_DATABITS_8;
    uart->hw->LCR |= databits;
    return RET_OK;
}

static int32 hguart_set_stopbits(struct uart_device *uart_t, int32 stopbits)
{
    uint32 ret = 0;
    struct hguart *uart = (struct hguart *)uart_t;
#if UART_FIFO_EN
    while ((uart->hw->USR & BIT(2)) == 0);
#else
    while ((uart->hw->LSR & BIT(5)) == 0);
#endif
    if (stopbits == UART_STOP_BIT_1) {
        uart->hw->LCR &= ~HGUART_2_STOPBIT;
    } else if (stopbits == UART_STOP_BIT_1_5) {
        ret = uart->hw->LCR & 0x3;
        if (ret == 0) {
            uart->hw->LCR |= HGUART_2_STOPBIT;
        } else {
            return RET_ERR;
        }
    } else if (stopbits == UART_STOP_BIT_2) {
        ret = uart->hw->LCR & 0x3;
        if (ret != 0) {
            uart->hw->LCR |= HGUART_2_STOPBIT;
        } else {
            return RET_ERR;
        }
    }
    return RET_OK;
}

static int32 hguart_putc(struct uart_device *uart_t, int8 Data)
{
    struct hguart *uart = (struct hguart *)uart_t;
#if UART_FIFO_EN
    while ((uart->hw->USR & BIT(1)) == 0); //tx fifo full
    uart->hw->RBR = Data;
#else
    uart->hw->RBR = Data;
    while ((uart->hw->LSR & BIT(5)) == 0);
#endif
    return RET_OK;
}

static uint8 hguart_getc(struct uart_device *uart_t)
{
    struct hguart *uart = (struct hguart *)uart_t;

    while ((uart->hw->LSR & BIT(0)) == 0);
    return uart->hw->RBR;
}

static int32 hguart_puts(struct uart_device *uart, uint8 *buf, uint32 size)
{
    uint32 i;
    struct hguart *dev = (struct hguart *)uart;
    struct dma_xfer_data xfer_data;

    if (dev->dma) {
        xfer_data.dest              = (uint32)&dev->hw->THR;
        xfer_data.src               = (uint32)buf;
        xfer_data.element_per_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
        xfer_data.element_num       = size;
        xfer_data.irq_hdl           = hguart_dma_tx_irq_hdl;
        xfer_data.irq_data          = (uint32)dev;
        dma_xfer(dev->dma, &xfer_data);
        os_sema_down(&dev->tx_dma_sema, osWaitForever); /* wait done */
    } else {
        for (i = 0; i < size; i++) {
            hguart_putc(uart, buf[i]);
        }
    }
    return RET_OK;
}

static int32 hguart_gets(struct uart_device *uart, uint8 *buf, uint32 size)
{
    uint32 i;
    struct hguart *dev = (struct hguart *)uart;
    struct dma_xfer_data xfer_data;

    if (dev->dma) {
        xfer_data.dest              = (uint32)buf;
        xfer_data.src               = (uint32)&dev->hw->RBR;
        xfer_data.element_per_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
        xfer_data.element_num       = size;
        xfer_data.irq_hdl           = hguart_dma_rx_irq_hdl;
        xfer_data.irq_data          = (uint32)dev;
        dma_xfer(dev->dma, &xfer_data);
        //os_sema_down(&dev->rx_dma_sema, osWaitForever);/* wait done */
    } else {
        for (i = 0; i < size; i++) {
            buf[i] = hguart_getc(uart);
        }
    }
    return RET_OK;
}

static void hguart_irq_handle(void *data)
{
    uint32 irq_id = 0;
    uint32 irq_clear = 0;
    uint32 rev_data = 0;
    struct hguart *uart = (struct hguart *)data;

    irq_id = uart->hw->IIR;
    irq_clear = irq_clear;
    switch ((irq_id & 0xf)) {
        case HGUART_INTR_MODEM_STATUS:
            if (uart->irq_hdl) {
                uart->irq_hdl(UART_INTR_MODEM_STATUS, uart->irq_data, 0);
            }
            irq_clear = uart->hw->MSR;  /*clear interrupt flag*/
            break;
        case HGUART_INTR_THR_EMPTY:
            if (uart->irq_hdl) {
                uart->irq_hdl(UART_INTR_THR_EMPTY, uart->irq_data, 0);
            }
            irq_clear = uart->hw->RBR;/*clear interrupt flag*/
            break;
        case HGUART_INTR_RX_DATA_AVAIL:
            if (uart->irq_hdl) {
                rev_data = hguart_getc((struct uart_device *)uart);
                uart->irq_hdl(UART_INTR_RX_DATA_AVAIL, uart->irq_data, rev_data);
            }
            break;
        case HGUART_INTR_RX_LINE_STATUS:
            if (uart->irq_hdl) {
                uart->irq_hdl(UART_INTR_RX_LINE_STATUS, uart->irq_data, 0);
            }
            irq_clear = uart->hw->LSR;/*clear interrupt flag*/
            break;
        case HGUART_INTR_BUSY_DETECT:
            if (uart->irq_hdl) {
                uart->irq_hdl(UART_INTR_BUSY_DETECT, uart->irq_data, 0);
            }
            irq_clear = uart->hw->USR;  /*clear interrupt flag*/
            break;
        case HGUART_INTR_CHAR_TIMEOUT:
            if (uart->irq_hdl) {
                uart->irq_hdl(UART_INTR_CHAR_TIMEOUT, uart->irq_data, 0);
            }
            irq_clear = uart->hw->RBR;/*clear interrupt flag*/
            break;
    }
}

int32 hguart_request_irq(struct uart_device *uart_t, uart_irq_hdl irq_hdl, uint32 irqbits, uint32 data)
{
    struct hguart *uart = (struct hguart *)uart_t;
    uart->irq_data = data;
    uart->irq_hdl  = irq_hdl;
    uart->hw->IER = irqbits;
    request_irq(uart->irq_num, hguart_irq_handle, uart);
    irq_enable(uart->irq_num);
    return RET_OK;
}

static int32 hguart_ioctl(struct uart_device *uart_t, int32 cmd, uint32 param)
{
    int32 ret = RET_OK;
    struct hguart *uart = (struct hguart *)uart_t;

    switch (cmd) {
        case UART_IOCTL_CMD_USE_DMA:
            uart->dma = (struct dma_device *)param;
            break;
        case UART_IOCTL_CMD_DATA_RDY:
            ret = (uart->hw->LSR & 0x1);
            break;
        default:
            return RET_ERR;
    }
    return ret;
}

__init void hguart_attach(uint32 dev_id, struct hguart *uart)
{
    uart->opened               = 0;
    uart->irq_hdl              = NULL;
    uart->irq_data             = NULL;
    uart->dev.open             = hguart_open;
    uart->dev.close            = hguart_close;
    uart->dev.baudrate         = hguart_set_baudrate;
    uart->dev.parity           = hguart_set_parity;
    uart->dev.databits         = hguart_set_databits;
    uart->dev.stopbits         = hguart_set_stopbits;
    uart->dev.putc             = hguart_putc;
    uart->dev.getc             = hguart_getc;
    uart->dev.puts             = hguart_puts;
    uart->dev.gets             = hguart_gets;
    uart->dev.request_irq      = hguart_request_irq;
    uart->dev.ioctl            = hguart_ioctl;
    irq_disable(uart->irq_num);
    dev_register(dev_id, (struct dev_obj *)uart);
}

