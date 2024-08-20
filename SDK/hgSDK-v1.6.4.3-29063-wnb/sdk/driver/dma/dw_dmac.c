#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "string.h"
#include "osal/irq.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "hal/dma.h"
#include "dev/dma/dw_dmac.h"

__weak int32 dw_dmac_search_src_id(uint32 addr)
{
    return -1;
}

__weak int32 dw_dmac_search_dest_id(uint32 addr)
{
    return -1;
}

static void dw_dmac_irq_handler(void *data)
{
    uint32 ch;
    struct hgdma_dw *dma = (struct hgdma_dw *)data;
    
    for(ch=0; ch<DW_DMAC_MAX_DMAC_CHN; ch++) {
        if((dma->hw->MaskTfrL & BIT(ch)) && (dma->hw->RawTfrL & BIT(ch))) {
            dma->hw->ClearTfrL = BIT(ch);
            dma->state[ch]    |= DW_DMAC_XFER_DONE(ch);
            if(dma->irq_hdl[ch]) {
                dma->irq_hdl[ch]((void *)dma, ch, DMA_IRQ_TYPE_DONE, dma->irq_data[ch]);
            }
        }
        if((dma->hw->MaskErrL & BIT(ch)) && (dma->hw->RawErrL & BIT(ch))) {
            dma->hw->ClearErrL = BIT(ch);
            dma->state[ch]    |= DW_DMAC_XFER_ERR(ch);
            if(dma->irq_hdl[ch]) {
                dma->irq_hdl[ch]((void *)dma, ch, DMA_IRQ_TYPE_ERROR, dma->irq_data[ch]);
            }
        }
    }
}

static int32 dw_dmac_xfer(struct dma_device *dma, struct dma_xfer_data *data)
{
    uint32 ch;
    uint32 flags;
    uint32 src_id;
    uint32 dest_id;
    uint32 direct;
    struct hgdma_dw    *dev = (struct hgdma_dw *)dma;
    struct hgdma_dw_hw *hw  = (struct hgdma_dw_hw *)dev->hw;
    
    if(!dev->opened) {
        return RET_ERR;
    }
    
    src_id  = dw_dmac_search_src_id(data->src);
    dest_id = dw_dmac_search_dest_id(data->dest);
    direct  = (src_id == -1 ? 0 : 2) | (dest_id == -1 ? 0 : 1);
    
    /* get free channel */
    flags = disable_irq();
    for(ch=0; ch<DW_DMAC_MAX_DMAC_CHN; ch++) {
        if(!(dev->chn_used_flag & BIT(ch))) {
            dev->chn_used_flag |= BIT(ch);
            break;
        }
    }
    enable_irq(flags);
    
    if(ch >= DW_DMAC_MAX_DMAC_CHN)
        return -EBUSY;

    ASSERT(data->element_per_width < DMA_SLAVE_BUSWIDTH_8_BYTES);
    if(data->element_per_width >= DMA_SLAVE_BUSWIDTH_8_BYTES) {
        return RET_ERR;
    }
    
    hw->CH[ch].SARH = 0x0000;
    hw->CH[ch].DARH = 0x0000;
    hw->CH[ch].SARL = data->src;
    hw->CH[ch].DARL = data->dest;
    switch(direct) {
        case DW_DMAC_FC_D_M2M:
            hw->CH[ch].CTLL = DW_DMAC_CTLL_SMS(1) | DW_DMAC_CTLL_DMS(1)     |
                              DW_DMAC_CTLL_FC(DW_DMAC_FC_D_M2M)             |
                              DW_DMAC_CTLL_SRC_DIR(DW_DMAC_ADDR_INC)        |
                              DW_DMAC_CTLL_DST_DIR(DW_DMAC_ADDR_INC);
            /* Configure dma req channel */
            hw->CH[ch].CFGH = DW_DMAC_CFGH_DST_PER(0)                       |
                              DW_DMAC_CFGH_SRC_PER(0)                       |
                              DW_DMAC_CFGH_PROTCTL(1);
            break;
        case DW_DMAC_FC_D_P2M:
            hw->CH[ch].CTLL = DW_DMAC_CTLL_SMS(0) | DW_DMAC_CTLL_DMS(1)     |
                              DW_DMAC_CTLL_FC(DW_DMAC_FC_D_P2M)             |
                              DW_DMAC_CTLL_SRC_DIR(DW_DMAC_ADDR_NO_CHANGE)  |
                              DW_DMAC_CTLL_DST_DIR(DW_DMAC_ADDR_INC);
            /* Configure dma req channel */
            hw->CH[ch].CFGH = DW_DMAC_CFGH_DST_PER(0)                       |
                              DW_DMAC_CFGH_SRC_PER(src_id)                  |
                              DW_DMAC_CFGH_PROTCTL(1);
            break;
        case DW_DMAC_FC_D_M2P:
            hw->CH[ch].CTLL = DW_DMAC_CTLL_SMS(1) | DW_DMAC_CTLL_DMS(0)     |
                              DW_DMAC_CTLL_FC(DW_DMAC_FC_D_M2P)             |
                              DW_DMAC_CTLL_SRC_DIR(DW_DMAC_ADDR_INC)        |
                              DW_DMAC_CTLL_DST_DIR(DW_DMAC_ADDR_NO_CHANGE);
            /* Configure dma req channel */
            hw->CH[ch].CFGH = DW_DMAC_CFGH_DST_PER(dest_id)                 |
                              DW_DMAC_CFGH_SRC_PER(0)                       |
                              DW_DMAC_CFGH_PROTCTL(1);
            break;
        case DW_DMAC_FC_D_P2P:
            hw->CH[ch].CTLL = DW_DMAC_CTLL_SMS(0) | DW_DMAC_CTLL_DMS(0)     |
                              DW_DMAC_CTLL_FC(DW_DMAC_FC_D_P2P)             |
                              DW_DMAC_CTLL_SRC_DIR(DW_DMAC_ADDR_NO_CHANGE)  |
                              DW_DMAC_CTLL_DST_DIR(DW_DMAC_ADDR_NO_CHANGE);
            /* Configure dma req channel */
            hw->CH[ch].CFGH = DW_DMAC_CFGH_DST_PER(dest_id)                 |
                              DW_DMAC_CFGH_SRC_PER(src_id)                  |
                              DW_DMAC_CFGH_PROTCTL(1);
            break;
        default:
           dev->chn_used_flag &= ~ BIT(ch);
           return RET_ERR;
    }
    /* Configure block size */
    hw->CH[ch].CTLH = data->element_num;
    
    hw->CH[ch].CTLL |= DW_DMAC_CTLL_INT_EN                                  |
                       DW_DMAC_CTLL_SRC_MSIZE(DW_DMAC_MSIZE_1)              |
                       DW_DMAC_CTLL_DST_MSIZE(DW_DMAC_MSIZE_1)              |
                       DW_DMAC_CTLL_SRC_WIDTH(data->element_per_width)      |
                       DW_DMAC_CTLL_DST_WIDTH(data->element_per_width);
    /* AMBA burst length no limited. */
    hw->CH[ch].CFGL  = DW_DMAC_CFGL_MAX_BURST(0);

    dev->state[ch]    = 0x0000;
    dev->irq_hdl[ch]  = data->irq_hdl;
    dev->irq_data[ch] = data->irq_data;

    //start xfer
    hw->ChEnRegL = DW_DMAC_WRITE_EN(ch);
    return ch;
}

static int32 dw_dmac_get_status(struct dma_device *dma, uint32 chn)
{
    struct hgdma_dw *dev = (struct hgdma_dw *)dma;

    if(!dev->opened) {
        return RET_ERR;
    }
    
    if(dev->state[chn] & DW_DMAC_XFER_ERR(chn)) {
        return DMA_ERROR;
    } else if(dev->state[chn] & DW_DMAC_XFER_DONE(chn)) {
        return DMA_SUCCESS;
    } else {
        return DMA_IN_PROGRESS;
    }
}

static int32 dw_dmac_stop(struct dma_device *dma, uint32 chn)
{
    uint32 flags;
    
    struct hgdma_dw       *dev       = (struct hgdma_dw *)dma;
    struct hgdma_dw_hw    *p_dmac    = (struct hgdma_dw_hw *)dev->hw;

    flags = disable_irq();
    if(dev->chn_used_flag & BIT(chn)) {
        p_dmac->ChEnRegL    = DW_DMAC_WRITE_DIS(chn);
        dev->chn_used_flag &= ~ BIT(chn);
    }
    enable_irq(flags);
    
    return RET_OK;
}

__init int32 dw_dmac_attach(uint32 dev_id, struct hgdma_dw *dmac)
{
    uint32 ch;
    
    dmac->opened                   = 1;
    dmac->dev.memcpy               = NULL;
    dmac->dev.memset               = NULL;
    dmac->dev.pause                = NULL;
    dmac->dev.resume               = NULL;
    dmac->dev.xfer                 = dw_dmac_xfer;
    dmac->dev.get_status           = dw_dmac_get_status;
    dmac->dev.stop                 = dw_dmac_stop;
    
    for(ch=0; ch<DW_DMAC_MAX_DMAC_CHN; ch++) {
        dmac->irq_hdl[ch]  = NULL;
        dmac->irq_data[ch] = 0;
        dmac->state[ch]    = 0;
    }
    
    dmac->hw->ChEnRegL   = 0xFF00;
    dmac->hw->DmaCfgRegL = 0x0000;
    
        /* reset dmac */
    dmac->hw->ClearBlockL   = DW_DMAC_MAX_DMAC_CHN_MASK;
    dmac->hw->ClearDstTranL = DW_DMAC_MAX_DMAC_CHN_MASK;
    dmac->hw->ClearErrL     = DW_DMAC_MAX_DMAC_CHN_MASK;
    dmac->hw->ClearSrcTranL = DW_DMAC_MAX_DMAC_CHN_MASK;
    dmac->hw->ClearTfrL     = DW_DMAC_MAX_DMAC_CHN_MASK;
    
    /* disable mask */
    dmac->hw->MaskErrL      = 0xFFFF;
    dmac->hw->MaskTfrL      = 0xFFFF;
    dmac->hw->MaskBlockL    = 0xFF00;
    dmac->hw->MaskDstTranL  = 0xFF00;
    dmac->hw->MaskSrcTranL  = 0xFF00;
    
    /* enable DMAC */
    dmac->hw->DmaCfgRegL = DW_DMAC_CFG_DMA_EN;
    
    irq_enable(dmac->irq_num);
    request_irq(dmac->irq_num, dw_dmac_irq_handler, dmac);
    dev_register(dev_id, (struct dev_obj *)dmac);
    return RET_OK;
}
