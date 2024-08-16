#ifndef _HAL_TDMA_H_
#define _HAL_TDMA_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @breif : enum of TDMA RAM Direction mode
  */
enum tdma_ram_dir_mode {
    TDMA_RAMOUT_MODE      = 0,
    TDMA_RAMIN_MODE       = 1,
};

/**
  * @breif : enum of TDMA reload mode
  */
enum tdma_rld_mode {
    TDMA_NON_RELOAD_MODE  = 0,
    TDMA_RELOAD_MODE      = 1,
};

struct tdma_device {
    struct dev_obj dev;
    int32(*set_mode)(struct tdma_device *tdma, enum tdma_ram_dir_mode ram_dir_mode, enum tdma_rld_mode rld_mode);
    int32(*irq_en)(struct tdma_device *tdma);
    int32(*set_buff)(struct tdma_device *tdma, uint32 buff_addr, uint32 buff_len);
    int32(*set_trig_len)(struct tdma_device *tdma, uint32 trig_len);
    int32(*start)(struct tdma_device *tdma);
    int32(*abort)(struct tdma_device *tdma);
    uint32(*get_pd)(struct tdma_device *tdma);
    int32(*clear_pd)(struct tdma_device *tdma);
};

static inline int32 tdma_set_mode(struct tdma_device *tdma_dev,
                                  enum tdma_ram_dir_mode ram_dir_mode, enum tdma_rld_mode rld_mode)
{
    if (tdma_dev && tdma_dev->set_mode) {
        return tdma_dev->set_mode(tdma_dev, ram_dir_mode, rld_mode);
    }
    return RET_ERR;
}

static inline int32 tdma_enable_irq(struct tdma_device *tdma_dev)
{
    if (tdma_dev && tdma_dev->irq_en) {
        tdma_dev->irq_en(tdma_dev);
        return RET_OK;
    }
    return RET_ERR;
}

static inline int32 tdma_set_buff(struct tdma_device *tdma_dev, uint32 buff_addr, uint32 buff_len)
{
    if (tdma_dev && tdma_dev->set_buff) {
        return tdma_dev->set_buff(tdma_dev, buff_addr, buff_len);
    }
    return RET_ERR;
}

static inline int32 tdma_set_trig_len(struct tdma_device *tdma_dev, uint32 trig_len)
{
    if (tdma_dev && tdma_dev->set_trig_len) {
        return tdma_dev->set_trig_len(tdma_dev, trig_len);
    }
    return RET_ERR;
}

static inline int32 tdma_start(struct tdma_device *tdma_dev)
{
    if (tdma_dev && tdma_dev->start) {
        tdma_dev->start(tdma_dev);
        return RET_OK;
    }
    return RET_ERR;
}

static inline int32 tdma_abort(struct tdma_device *tdma_dev)
{
    if (tdma_dev && tdma_dev->abort) {
        tdma_dev->abort(tdma_dev);
        return RET_OK;
    }
    return RET_ERR;
}

static inline uint32 tdma_get_pd(struct tdma_device *tdma_dev)
{
    if (tdma_dev && tdma_dev->get_pd) {
        return tdma_dev->get_pd(tdma_dev);
    }
    return 0xffffffff;
}

static inline int32 tdma_clear_pd(struct tdma_device *tdma_dev)
{
    if (tdma_dev && tdma_dev->clear_pd) {
        tdma_dev->clear_pd(tdma_dev);
        return RET_OK;
    }
    return RET_ERR;
}

#ifdef __cplusplus
}
#endif
#endif

