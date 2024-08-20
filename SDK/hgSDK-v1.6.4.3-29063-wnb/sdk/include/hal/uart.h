/**
 * @file uart.h
 * @author HUGE-IC Application Team
 * @brief UART HAL driver
 * @version 1.0.0
 * @date 2021-8-30
 * 
 * @copyright Copyright (c) 2021 HUGE-IC
 */
#ifndef _HAL_UART_H_
#define _HAL_UART_H_
#include "typesdef.h"
#ifdef __cplusplus
extern "C" {
#endif

enum uart_parity_bit {
    UART_PARIRY_NONE = 0x0,
    UART_PARIRY_ODD  = 0x1,
    UART_PARIRY_EVEN = 0x2
};

enum uart_data_bit {
    UART_DATA_BIT_5 = 0x0,
    UART_DATA_BIT_6 = 0x1,
    UART_DATA_BIT_7 = 0x2,
    UART_DATA_BIT_8 = 0x3
};

enum uart_stop_bit {
    UART_STOP_BIT_1   = 0x0,
    UART_STOP_BIT_1_5 = 0x1,
    UART_STOP_BIT_2   = 0x2
};

enum uart_irq_flag {
    UART_INTR_NONE,
    UART_INTR_MODEM_STATUS,
    UART_INTR_THR_EMPTY,
    UART_INTR_RX_DATA_AVAIL,
    UART_INTR_RX_LINE_STATUS,
    UART_INTR_BUSY_DETECT,
    UART_INTR_CHAR_TIMEOUT
};

enum uart_ioctl_cmd {
    UART_IOCTL_CMD_DATA_RDY = 1, /*data has received*/
    UART_IOCTL_CMD_USE_DMA  = 2, /*use dma to transmit*/
};

typedef int32(*uart_irq_hdl)(uint32 irq, uint32 param1, uint32 param2);

struct uart_device {
    struct dev_obj dev;
    int32(*open)(struct uart_device *uart);
    int32(*close)(struct uart_device *uart);
    int32(*baudrate)(struct uart_device *uart, int32 baudrate);
    int32(*parity)(struct uart_device *uart, int32 parity);
    int32(*databits)(struct uart_device *uart, int32 databits);
    int32(*stopbits)(struct uart_device *uart, int32 stopbits);
    int32(*putc)(struct uart_device *uart, int8 value);
    uint8(*getc)(struct uart_device *uart);
    int32(*puts)(struct uart_device *uart, uint8 *buf, uint32 size);
    int32(*gets)(struct uart_device *uart, uint8 *buf, uint32 size);
    int32(*ioctl)(struct uart_device *uart, int32 cmd, uint32 param);
    int32(*request_irq)(struct uart_device *uart, uart_irq_hdl irqhdl, uint32 irqbits, uint32 data);
};

/**
 * @brief UART device open
 * 
 * @param uart  UART device struct
 * @return int32
 * 
 */
static inline int32 uart_open(struct uart_device *uart)
{
    if (uart && uart->open) {
        return uart->open(uart);
    } else {
        return RET_ERR;
    }
}

/**
 * @brief UART device close
 * 
 * @param uart  UART device struct
 * @return int32
 * 
 */
static inline int32 uart_close(struct uart_device *uart)
{
    if (uart && uart->close) {
        return uart->close(uart);
    } else {
        return RET_ERR;
    }
}

/**
 * @brief UART device set baudrate
 * 
 * @param uart  UART device struct
 * @param baudrate  Target baudrate
 * @return int32
 * 
 */
static inline int32 uart_baudrate(struct uart_device *uart, int32 baudrate)
{
    if (uart && uart->baudrate) {
        return uart->baudrate(uart, baudrate);
    } else {
        return RET_ERR;
    }
}

/**
 * @brief UART device set parity
 * 
 * @param uart  UART device struct
 * @param parity  Target parity
 * @return int32
 * 
 */
static inline int32 uart_parity(struct uart_device *uart, int32 parity)
{
    if (uart && uart->parity) {
        return uart->parity(uart, parity);
    } else {
        return RET_ERR;
    }
}

/**
 * @brief UART device set data bits width
 * 
 * @param uart  UART device struct
 * @param databits  Target data bits width
 * @return int32
 * 
 */
static inline int32 uart_databits(struct uart_device *uart, int32 databits)
{
    if (uart && uart->databits) {
        return uart->databits(uart, databits);
    } else {
        return RET_ERR;
    }
}

/**
 * @brief UART device set stop bits width
 * 
 * @param uart  UART device struct
 * @param stopbits  Target stop bits width
 * @return int32
 * 
 */
static inline int32 uart_stopbits(struct uart_device *uart, int32 stopbits)
{
    if (uart && uart->stopbits) {
        return uart->stopbits(uart, stopbits);
    } else {
        return RET_ERR;
    }
}

/**
 * @brief UART device input/output control
 * 
 * @param uart  UART device struct
 * @param cmd  Control command
 * @param param  Control parameter
 * @return int32
 * 
 */
static inline int32 uart_ioctl(struct uart_device *uart, int32 cmd, uint32 param)
{
    if (uart && uart->ioctl) {
        return uart->ioctl(uart, cmd, param);
    } else {
        return RET_ERR;
    }
}

/**
 * @brief UART device send a char
 * 
 * @param uart  UART device struct
 * @param value  To send char
 * @return int32
 * 
 */
static inline int32 uart_putc(struct uart_device *uart, int8 value)
{
    if (uart && uart->putc) {
        return uart->putc(uart, value);
    }
    return RET_ERR;
}

/**
 * @brief UART device read a char
 * 
 * @param uart  uart device struct
 * @return uint8
 * @retval recv char
 * 
 */
static inline uint8 uart_getc(struct uart_device *uart)
{
    if (uart && uart->getc) {
        return uart->getc(uart);
    } else {
        return 0;
    }
}

/**
 * @brief UART device read multi-bytes data
 * 
 * @param uart  UART device struct
 * @param buf  Recv data buffer
 * @param len  Recv data length
 * @return int32
 * 
 */
static inline int32 uart_gets(struct uart_device *uart, void *buf, uint32 len)
{
    if (uart && uart->gets) {
        return uart->gets(uart, buf, len);
    }
    return RET_ERR;
}

/**
 * @brief UART device write multi-bytes data
 * 
 * @param uart  UART device struct
 * @param buf  Send data buffer
 * @param len  Send data length
 * @return int32
 * 
 */
static inline int32 uart_puts(struct uart_device *uart, void *buf, uint32 len)
{
    if (uart && uart->puts) {
        return uart->puts(uart, buf, len);
    }
    return RET_ERR;
}

/**
 * @brief UART device request irq with flags
 * 
 * @param uart  UART device struct
 * @param irqhdl  UART irq handler function
 * @param irqbits  UART irq register bits?
 * @param data  UART irq handler function data
 * @return int32
 * 
 */
static inline int32 uart_request_irq(struct uart_device *uart, uart_irq_hdl irqhdl, uint32 irqbits, uint32 data)
{
    if (uart && uart->request_irq) {
        return uart->request_irq(uart, irqhdl, irqbits, data);
    }
    return RET_ERR;
}

/**
 * @brief UART device check data ready
 * 
 * @param uart  UART device struct
 * @return int32
 * 
 */
static inline int32 uart_data_rdy(struct uart_device *uart)
{
    return uart_ioctl(uart, UART_IOCTL_CMD_DATA_RDY, 0);
}

#ifdef __cplusplus
}
#endif
#endif

