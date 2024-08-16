#include "typesdef.h"
#include "tx_platform.h"

/*
 *  Peripheral ID query. This is fixed when the IC is designed and is
 *  suitable for the dw_dmac module.
 */

struct dmac_perip_id {
    uint32 reg_addr;
    uint32 perip_id;
};

static const struct dmac_perip_id dmac_src_perip_id[] = {
    {IIC0_BASE + 0x10,  DMA_CH_I2C0_RX, },
    {HG_UART0_BASE,     DMA_CH_UART0_RX,},
    {HG_UART1_BASE,     DMA_CH_UART1_RX,},
    {SPI0_BASE + 0x60,  DMA_CH_SPI0_RX, },
    {SPI1_BASE + 0x60,  DMA_CH_SPI1_RX, },
    {SPI3_BASE + 0x60,  DMA_CH_SPI3_RX, },
};

static const struct dmac_perip_id dmac_dest_perip_id[] = {
    {IIC0_BASE + 0x10,  DMA_CH_I2C0_TX, },
    {HG_UART0_BASE,     DMA_CH_UART0_TX,},
    {HG_UART1_BASE,     DMA_CH_UART1_TX,},
    {SPI0_BASE + 0x60,  DMA_CH_SPI0_TX, },
    {SPI1_BASE + 0x60,  DMA_CH_SPI1_TX, },
    {SPI3_BASE + 0x60,  DMA_CH_SPI3_TX, },
};


int32 dw_dmac_search_src_id(uint32 addr)
{
    int32 left = 0;
    int32 right = sizeof(dmac_src_perip_id)/sizeof(dmac_src_perip_id[0]) - 1;
    int32 half;
    
    /* Binary Search */
    while(left <= right) {
        half = (left + right)/2;
        
        if(dmac_src_perip_id[half].reg_addr < addr) {
            left = half + 1;
        } else if(dmac_src_perip_id[half].reg_addr > addr) {
            right = half - 1;
        } else {
            return dmac_src_perip_id[half].perip_id;
        }
    }
    
    return -1;
}

int32 dw_dmac_search_dest_id(uint32 addr)
{
    int32 left = 0;
    int32 right = sizeof(dmac_dest_perip_id)/sizeof(dmac_dest_perip_id[0]) - 1;
    int32 half;
    
    /* Binary Search */
    while(left <= right) {
        half = (left + right)/2;
        
        if(dmac_dest_perip_id[half].reg_addr < addr) {
            left = half + 1;
        } else if(dmac_dest_perip_id[half].reg_addr > addr) {
            right = half - 1;
        } else {
            return dmac_dest_perip_id[half].perip_id;
        }
    }
    
    return -1;
}



