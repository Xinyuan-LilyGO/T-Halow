#ifndef _HG_M2M_DMA_H_
#define _HG_M2M_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HG_M2M_DMA_NUM              2
    
/** 
  * @brief  M2M_DMA
  */
struct mem_dma_ch {
    __IO uint32 DMA_CON;
    __IO uint32 DMA_SAIE;
    __IO uint32 DMA_DATA;
    __IO uint32 DMA_SADR;
    __IO uint32 DMA_TADR;
    __IO uint32 DMA_DLEN;
};

struct mem_dma_hw {
    struct mem_dma_ch dma_ch[HG_M2M_DMA_NUM];
};

struct mem_dma_dev {
    struct dma_device  dev;
    struct mem_dma_hw *hw;
    uint32             opened;
    uint32             busy_flag;
};


/** @brief M2M DMA register constant table definition
  * @{
  */

/***** DMA_CON *****/
#define HG_M2M_DMA_CON_DTM                  (1UL << 1)
#define HG_M2M_DMA_CON_DTE                  (1UL << 0)

/***** DMA_SAIE *****/
#define HG_M2M_DMA_SAIE_TCIE                (1UL << 16)
#define HG_M2M_DMA_SAIE_TCP_PENDING         (1UL << 0)

/**
  * @}
  */

int32 mem_dma_dev_attach(uint32 dev_id, struct mem_dma_dev *p_dma);

#ifdef __cplusplus
}
#endif

#endif
