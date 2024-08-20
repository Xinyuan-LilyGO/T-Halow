#ifndef _HAL_DMA_H_
#define _HAL_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * enum dma_status - DMA transaction status
 * @DMA_SUCCESS: transaction completed successfully
 * @DMA_IN_PROGRESS: transaction not yet processed
 * @DMA_PAUSED: transaction is paused
 * @DMA_ERROR: transaction failed
 */
enum dma_status {
    DMA_SUCCESS,
    DMA_IN_PROGRESS,
    DMA_PAUSED,
    DMA_ERROR,
};


/**
 * enum dma_slave_buswidth - defines bus with of the DMA slave
 * device, source or target buses
 */
enum dma_slave_buswidth {
    DMA_SLAVE_BUSWIDTH_1_BYTE       = 0,
    DMA_SLAVE_BUSWIDTH_2_BYTES      = 1,
    DMA_SLAVE_BUSWIDTH_4_BYTES      = 2,
    DMA_SLAVE_BUSWIDTH_8_BYTES      = 3,
    DMA_SLAVE_BUSWIDTH_UNDEFINED    = 4,
};

enum dma_irq_type {
    DMA_IRQ_TYPE_DONE,
    DMA_IRQ_TYPE_ERROR,
};

struct dma_device;

typedef void (*dma_irq_hdl)(struct dma_device *p_dma, uint32 ch, enum dma_irq_type irq, uint32 data);

struct dma_xfer_data {
    uint32 dest;
    uint32 src;
    uint32 element_per_width;
    uint32 element_num;
    uint32 irq_data;
    dma_irq_hdl irq_hdl;
};

struct dma_device {
    struct dev_obj dev;
    int32(*pause)(struct dma_device *dma, uint32 ch);
    int32(*resume)(struct dma_device *dma, uint32 ch);
    int32(*xfer)(struct dma_device *dma, struct dma_xfer_data *data);
    int32(*get_status)(struct dma_device *dma, uint32 ch);
    int32(*stop)(struct dma_device *dma, uint32 ch);
    void(*memcpy)(struct dma_device *dma, void *dst, const void *src, uint32 n);
    void(*memset)(struct dma_device *dma, void *dst, uint8 c, uint32 n);
};

static inline int32 dma_pause(struct dma_device *dma, uint32 ch)
{
    if(dma && dma->pause) {
        return dma->pause(dma, ch);
    }
    return RET_ERR;
}

static inline int32 dma_resume(struct dma_device *dma, uint32 ch)
{
    if(dma && dma->resume) {
        return dma->resume(dma, ch);
    }
    return RET_ERR;
}

static inline void dma_memcpy(struct dma_device *dma, void *dst, const void *src, uint32 n)
{
    ASSERT(dma->memcpy);
    dma->memcpy(dma, dst, src, n);
}

static inline void dma_memset(struct dma_device *dma, void *dst, uint8 c, uint32 n)
{
    ASSERT(dma->memset);
    dma->memset(dma, dst, c, n);
}

static inline int32 dma_xfer(struct dma_device *dma, struct dma_xfer_data *data)
{
    if(dma && dma->xfer) {
        return dma->xfer(dma, data);
    }
    return RET_ERR;
}

static inline int32 dma_status(struct dma_device *dma, uint32 ch)
{
    if(dma && dma->get_status) {
        return dma->get_status(dma, ch);
    }
    return RET_ERR;
}

static inline int32 dma_stop(struct dma_device *dma, uint32 ch)
{
    if(dma && dma->stop) {
        return dma->stop(dma, ch);
    }
    return RET_ERR;
}


#ifdef __cplusplus
}
#endif

#endif
