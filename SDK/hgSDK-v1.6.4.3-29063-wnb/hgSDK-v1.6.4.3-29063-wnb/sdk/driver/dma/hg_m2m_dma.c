#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "osal/irq.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "osal/string.h"
#include "hal/dma.h"
#include "dev/dma/hg_m2m_dma.h"

static inline int32 mem_dma_get_free_ch(struct mem_dma_dev *dev)
{
    int32  ch = -1;
    uint32 flags = disable_irq();
    for(ch=0; ch<HG_M2M_DMA_NUM; ch++){
        if(!(dev->busy_flag & BIT(ch))){
            dev->busy_flag |= BIT(ch);
            break;
        }
    }
    enable_irq(flags);
    return ch<2?ch:-1;
}

static inline void mem_dma_free_ch(struct mem_dma_dev *dev, int32 ch)
{    
    uint32 flags = disable_irq();
    dev->busy_flag &= ~ BIT(ch);
    enable_irq(flags);
}

static void mem_dma_memcpy(struct dma_device *dma, void *dest, const void *src, uint32 count)
{
    int32 ch;
    struct mem_dma_dev *dev = (struct mem_dma_dev *)dma;
    
    if(count == 0 || !dest || !src) {
       return;
    }
    
    ch = mem_dma_get_free_ch(dev);
    if(ch < 0) {
        os_memcpy(dest, src, count);
    } else {
        dev->hw->dma_ch[ch].DMA_CON  = 0x00;
        dev->hw->dma_ch[ch].DMA_SADR = (uint32)src;
        dev->hw->dma_ch[ch].DMA_TADR = (uint32)dest;
        dev->hw->dma_ch[ch].DMA_DLEN = count - 1;
        dev->hw->dma_ch[ch].DMA_CON  = HG_M2M_DMA_CON_DTE;
        
        while(dev->hw->dma_ch[ch].DMA_CON & HG_M2M_DMA_CON_DTE);
        
        mem_dma_free_ch(dev, ch);
    }
}

static void mem_dma_memset(struct dma_device *dma, void *addr, uint8 val, uint32 count)
{
    struct mem_dma_dev *dev = (struct mem_dma_dev *)dma;
    int32 ch;
    
    if(count == 0 || addr == NULL) {
        return;
    }

    ch = mem_dma_get_free_ch(dev);
    if(ch < 0) {
        os_memset(addr, val, count);
    } else {
        dev->hw->dma_ch[ch].DMA_CON  = 0x00;
        dev->hw->dma_ch[ch].DMA_TADR = (uint32)addr;
        dev->hw->dma_ch[ch].DMA_DATA = val;
        dev->hw->dma_ch[ch].DMA_DLEN = count - 1;
        dev->hw->dma_ch[ch].DMA_CON  = HG_M2M_DMA_CON_DTM | HG_M2M_DMA_CON_DTE;
        
        while(dev->hw->dma_ch[ch].DMA_CON & HG_M2M_DMA_CON_DTE);
        
        mem_dma_free_ch(dev, ch);
    }
}

__init int32 mem_dma_dev_attach(uint32 dev_id, struct mem_dma_dev *p_dma)
{
    p_dma->dev.memcpy  = mem_dma_memcpy;
    p_dma->dev.memset  = mem_dma_memset;
    p_dma->hw->dma_ch[0].DMA_CON  = 0x00;
    p_dma->hw->dma_ch[0].DMA_SAIE = HG_M2M_DMA_SAIE_TCP_PENDING;
    p_dma->hw->dma_ch[0].DMA_CON  = 0x00;
    p_dma->hw->dma_ch[0].DMA_SAIE = HG_M2M_DMA_SAIE_TCP_PENDING;
    dev_register(dev_id, (struct dev_obj *)p_dma);
    return RET_OK;
}

