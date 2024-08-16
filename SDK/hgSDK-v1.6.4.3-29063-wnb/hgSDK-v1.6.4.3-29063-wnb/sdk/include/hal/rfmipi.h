// rfmipi.h
#ifndef  _HAL_RFMIPI_H_
#define  _HAL_RFMIPI_H_
#ifdef __cplusplus
extern "C" {
#endif

#define K_MIPI_SUCCESS       0
#define K_MIPI_FAIL          1
#define K_MIPI_TIMEOUT_CYC   1000

struct rfmipi_device {
    struct dev_obj dev;
    void(*init)(struct rfmipi_device *pdev);
    uint32(*wr_reg0)(struct rfmipi_device *pdev, uint8 usid, uint8 byte_data);
    uint32(*wr_reg)(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 byte_data);
    uint32(*rd_reg)(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 *p_byte_data_o);
    uint32(*ext_wr_reg)(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 *p_byte_data_vec, uint8 dbn);
    uint32(*ext_rd_reg)(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 *p_byte_data_vec, uint8 dbn);
    void(*cfg_rdv_bit)(struct rfmipi_device *pdev, uint8 enable);
    void(*cfg_trig_src)(struct rfmipi_device *pdev, uint8 enable);
    void (*cfg_vio)(struct rfmipi_device *pdev, uint8 on_off);
};


static inline void rfmipi_device_init(struct rfmipi_device *pdev)
{
    if (pdev && pdev->init) {
        pdev->init(pdev);
    }
}

static inline uint32 rfmipi_device_write0(struct rfmipi_device *pdev, uint8 usid, uint8 byte_data)
{
    if (pdev && pdev->wr_reg0) {
        return pdev->wr_reg0(pdev, usid, byte_data);
    } else {
        return K_MIPI_FAIL;
    }
}

static inline uint32 rfmipi_device_write(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 byte_data)
{
    if (pdev && pdev->wr_reg) {
        return pdev->wr_reg(pdev, usid, sadr, byte_data);
    } else {
        return K_MIPI_FAIL;
    }
}

static inline uint32 rfmipi_device_read(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 *p_byte_data_o)
{
    if (pdev && pdev->rd_reg) {
        return pdev->rd_reg(pdev, usid, sadr, p_byte_data_o);
    } else {
        return K_MIPI_FAIL;
    }
}

static inline uint32 rfmipi_device_extend_write(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 *p_byte_data_vec, uint8 dbn)
{
    if (pdev && pdev->ext_wr_reg) {
        return pdev->ext_wr_reg(pdev, usid, sadr, p_byte_data_vec, dbn);
    } else {
        return K_MIPI_FAIL;
    }
}

static inline uint32 rfmipi_device_extend_read(struct rfmipi_device *pdev, uint8 usid, uint8 sadr, uint8 *p_byte_data_vec, uint8 dbn)
{
    if (pdev && pdev->ext_rd_reg) {
        return pdev->ext_rd_reg(pdev, usid, sadr, p_byte_data_vec, dbn);
    } else {
        return K_MIPI_FAIL;
    }
}

static inline void rfmipi_device_rdv_config(struct rfmipi_device *pdev, uint8 enable)
{
    if (pdev && pdev->cfg_rdv_bit) {
        pdev->cfg_rdv_bit(pdev, enable);
    }
}

static inline void rfmipi_device_trig_src_config(struct rfmipi_device *pdev, uint8 enable)
{
    if (pdev && pdev->cfg_trig_src) {
        pdev->cfg_trig_src(pdev, enable);
    }
}

// 0: off  1: on
static inline void rfmipi_device_vio_config(struct rfmipi_device *pdev, uint8 on_off)
{
    if (pdev && pdev->cfg_vio) {
        pdev->cfg_vio(pdev, on_off);
    }
}

#ifdef __cplusplus
}
#endif
#endif

