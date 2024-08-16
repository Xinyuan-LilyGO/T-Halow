/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 /******************************************************************************
 * @file     vectors.S
 * @brief    define default vector handlers. Should use with
 *           GCC for CSKY Embedded Processors
 * @version  V1.0
 * @date     28. Nove 2017
 ******************************************************************************/

#include <csi_config.h>

.import trap_c

.section .bss
    .align  2
    .globl  g_trapstackalloc
    .global g_trapstackbase
    .global g_top_trapstack
g_trapstackalloc:
g_trapstackbase:
    .space 512
g_top_trapstack:

.text

/******************************************************************************
 * Functions:
 *     void trap(void);
 * default exception handler
 ******************************************************************************/
    .global trap
    .type   trap, %function
trap:
    psrset  ee
    subi    sp, 4
    stw     r0, (sp)

    lrw     r0, g_top_trapstack
    subi    r0, 76
    stm     r0-r15, (r0)
    stw     r28, (r0, 64)

    ldw     r1, (sp)
    addi    sp, 4
    stw     sp, (r0, 56) /* save r14 */
    mov     sp, r0
    stw     r1, (sp)     /* save r0 */

    mfcr    r1, epsr
    stw     r1, (sp, 68)
    mfcr    r1, epc
    stw     r1, (sp, 72)

    jbsr    trap_c

    .align  2
    .weak   Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    br      trap
    .size   Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .globl  \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler trap0_handler
    def_irq_handler tspend_handler
    def_irq_handler CORET_IRQHandler
    def_irq_handler IIC0_IRQHandler
    def_irq_handler UART0_IRQHandler
    def_irq_handler UART1_IRQHandler
    def_irq_handler SPI0_IRQHandler
    def_irq_handler SPI1_IRQHandler
    def_irq_handler SPI3_IRQHandler
    def_irq_handler WDT_IRQHandler
    def_irq_handler RTC_IRQHandler
    def_irq_handler DMAC_IRQHandler
    def_irq_handler GPIOA_IRQHandler
    def_irq_handler TIM0_IRQHandler
    def_irq_handler TIM1_IRQHandler
    def_irq_handler TIM2_IRQHandler
    def_irq_handler TIM3_IRQHandler
    def_irq_handler SDIO_SLAVE_IRQHandler
    def_irq_handler PD_TMR_IRQHandler
    def_irq_handler TDMA_IRQHandler
    def_irq_handler GMAC_IRQHandler
    def_irq_handler USB_CTL_IRQHandler
    def_irq_handler USB_SOF_IRQHandler
    def_irq_handler CE_IRQHandler
    def_irq_handler SDIO_HOST_IRQHandler
    def_irq_handler GPIOB_IRQHandler
    def_irq_handler LMAC_IRQHandler
    def_irq_handler CRC_IRQHandler
    def_irq_handler WAKEUP_IRQHandler
    def_irq_handler SDIO_SLAVE_RST_IRQHandler
    def_irq_handler SYS_ERR_IRQHandler
    def_irq_handler LVD_IRQHandler
    def_irq_handler SYS_AES_IRQHandler    
    def_irq_handler MIPI_IRQHandler    
    
