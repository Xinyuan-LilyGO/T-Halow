#ifndef _HGUART_H
#define _HGUART_H

#include "typesdef.h"
#ifdef __cplusplus
extern "C" {
#endif

#define UART_FIFO_EN  1

struct hguart_hw {
    union {
        __IO uint32 RBR;
        __IO uint32 THR;
        __IO uint32 DLL;
    };
    union {
        __IO uint32 DLH;
        __IO uint32 IER;
    };
    union {
        __IO uint32 IIR;
        __IO uint32 FCR;
    };
    __IO uint32 LCR;
    __IO uint32 MCR;
    __IO uint32 LSR;
    __IO uint32 MSR;
    __IO uint32 SCR;

    __IO uint32 LPDLL;
    __IO uint32 LPDLH;
    __IO uint32 FIFO[0x12];

    __IO uint32 FAR;
    __IO uint32 TFR;
    __IO uint32 RFW;
    __IO uint32 USR;

    __IO uint32 TFL;
    __IO uint32 RFL;
    __IO uint32 SRR;
    __IO uint32 SRTS;

    __IO uint32 SBCR;
    __IO uint32 SDMAM;
    __IO uint32 SFE;
    __IO uint32 SRT;

    __IO uint32 STET;
    __IO uint32 HTX;
    __IO uint32 DMASA;
    __IO uint32 TCR;

    __IO uint32 DE_EN;
    __IO uint32 RE_EN;
    __IO uint32 DET;
    __IO uint32 TAT;

    __IO uint32 DLF;
    __IO uint32 RAR;
    __IO uint32 TAR;
    __IO uint32 LCR_EXT;
} ;

struct hguart {
    struct uart_device   dev;
    struct hguart_hw    *hw;
    uart_irq_hdl         irq_hdl;
    uint32               irq_num;
    uint32               irq_data;
    uint32               opened;
    /* The following variables are used for dma operations */
    struct dma_device   *dma;
    struct os_semaphore  tx_dma_sema;
    struct os_semaphore  rx_dma_sema;
};

enum hguart_intr_en {
    HGUART_INTR_DISABLE           = 0x00,
    HGUART_INTR_RX_DATA_AVAIL_EN  = 0x01,
    HGUART_INTR_RX_LINE_STATUS_EN = 0x04,
    HGUART_INTR_MODEM_STATUS_EN   = 0x08,
    HGUART_INTR_PROGEM_THRE_EN    = 0x80,
    HGUART_INTR_THR_EMPTY_EN      = 0x82,
};

enum hguart_intr_status {
    HGUART_INTR_MODEM_STATUS   = 0x0,
    HGUART_INTR_NO             = 0x1,
    HGUART_INTR_THR_EMPTY      = 0x2,
    HGUART_INTR_RX_DATA_AVAIL  = 0x4,
    HGUART_INTR_RX_LINE_STATUS = 0x6,
    HGUART_INTR_BUSY_DETECT    = 0x7,
    HGUART_INTR_CHAR_TIMEOUT   = 0xC
} ;

#define HGUART_DEFAULT_BAUDRATE             115200    /* baud rate is set 115200*/
#define HGUART_DEFAULT_DATABITS            ((0x3UL<<0))/* data bit is set 8bit   */
#define HGUART_DEFAULT_STOPBITS            ((0x0UL<<2))/* stop bit is set 1bit   */
#define HGUART_DEFAULT_PARITY              ((0x0UL<<3))/* Parity None            */

#define HGUART_LCR_BCB                      (BIT(6))
#define HGUART_DATABITS_8                  ((uint8)0x03)
#define HGUART_PARITY_NONE                 ((uint8)0x00)
#define HGUART_PARITY_ODD                  ((uint8)0x01)
#define HGUART_PARITY_EVEN                 ((uint8)0x02)
#define HGUART_2_STOPBIT                   (0x04)

#define HGUART_MODE_RX                     ((uint8)0x01)
#define HGUART_MODE_TX                     ((uint8)0x02)
#define HGUART_MODE_FIFO                   ((uint8)0x04)

#define HGUART_RXFIFO_TRIG_1CHAR           ((uint8)0x00)
#define HGUART_RXFIFO_TRIG_QTX_UARTER      ((uint8)0x40)
#define HGUART_RXFIFO_TRIG_HALF            ((uint8)0x80)
#define HGUART_RXFIFO_TRIG_2LESS_FULL      ((uint8)0xC0)

#define HGUART_TXFIFO_TRIG_EMPTY           ((uint8)0x00)
#define HGUART_TXFIFO_TRIG_2CHAR           ((uint8)0x10)
#define HGUART_TXFIFO_TRIG_QTX_UARTER      ((uint8)0x20)
#define HGUART_TXFIFO_TRIG_HALF            ((uint8)0x30)

#define HGUARTx_RXFIFO_TRIG                  HGUART_RXFIFO_TRIG_1CHAR
#define HGUARTx_TXFIFO_TRIG                  HGUART_TXFIFO_TRIG_EMPTY


enum hguart_ioctl_cmd {
    HGUART_DMAC_USE             = 0x100,
};

void hguart_attach(uint32 dev_id, struct hguart *uart);
#ifdef __cplusplus
}
#endif

#endif

