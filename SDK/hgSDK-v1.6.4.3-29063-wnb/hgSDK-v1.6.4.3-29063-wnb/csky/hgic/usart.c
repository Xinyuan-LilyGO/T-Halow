
#include "typesdef.h"
#include "list.h"
#include "dev.h"
#include "devid.h"
#include "osal/string.h"
#include "hal/uart.h"

#include "csi_core.h"
#include "drv_usart.h"

int32_t csi_usart_getchar(usart_handle_t handle, uint8_t *ch)
{
    *ch = uart_getc((struct uart_device *)handle);
    return RET_OK;
}

int32_t csi_usart_putchar(usart_handle_t handle, uint8_t ch)
{
    return uart_putc((struct uart_device *)handle, ch);
}

