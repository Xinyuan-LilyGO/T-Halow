
// @file    rf_device.h
// @author  wangying
// @brief   This file contains all the rf-device APIs.
// Revision History
// V1.0.0  01-14-2019  First Release
// V1.0.1  03-16-2019  add rf_device_soft_reset()
// V1.0.2  06-27-2019  add rf_device_read_reg()
// V1.0.3  07-23-2019  add lo_table_ctrl(), lo_table_cfg(), read_reg() and write_reg()
// V1.0.4  11-01-2019  add rf_device_rx_bb_ana_out() and rf_device_tx_bb_ana_out()
// V1.0.5  12-11-2019  add arguements for rx_imb_calib()
// V1.0.6  12-27-2019  modify lo_table_cfg and add lo_table_kick/rf_device_lo_table_kick for lo table switch husf

#ifndef _HAL_RF_DEVICE_H_
#define _HAL_RF_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
* @breif : enum of RF mode
*/
enum rf_mode {
    RF_DISABLE = 0,
    RF_EN      = 1,
    RX_EN      = 2,
    TX_EN      = 3
};

struct rf_device {
    struct dev_obj dev;
    int32(*open)(struct rf_device *rf_dev);
    int32(*close)(struct rf_device *rf_dev);
    int32(*lo_freq_set)(struct rf_device *rf_dev, uint32 freq);
    int32(*check_lo_lock)(struct rf_device *rf_dev);
    int32(*lo_table_ctrl)(struct rf_device *rf_dev, uint8 onoff);
    int32(*lo_table_cfg)(struct rf_device *rf_dev, uint32 *freq_list, uint16 count);
    int32(*lo_table_kick)(struct rf_device *rf_dev);
    int32(*tx_dcoc_calib)(struct rf_device *rf_dev);
    int32(*rx_dcoc_calib)(struct rf_device *rf_dev);
    int32(*dpd_dcoc_calib)(struct rf_device *rf_dev);
    int32(*vco_calib)(struct rf_device *rf_dev);
    int32(*tx_imb_calib)(struct rf_device *rf_dev);
    int32(*dpd_imb_calib)(struct rf_device *rf_dev);
    int32(*rx_imb_calib)(struct rf_device *rf_dev, uint8 rx_bw, uint8 gain_idx);
    int32(*tx_power_set)(struct rf_device *rf_dev, int8 tx_power_dbm);
    int32(*rx_gain_set)(struct rf_device *rf_dev, int8 rx_gain_db);
    int32(*rx_bb_ana_out)(struct rf_device *rf_dev);
    int32(*tx_bb_ana_out)(struct rf_device *rf_dev);
    int32(*soft_reset)(struct rf_device *rf_dev);
    int32(*rf_regs_read)(struct rf_device *rfdev);
    int32(*read_reg)(struct rf_device *rfdev, uint16 reg_addr);
    int32(*write_reg)(struct rf_device *rfdev, uint16 reg_addr, uint16 reg_val);
};

static inline int32 rf_device_open(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->open) {
        return rf_dev->open(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_close(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->close) {
        return rf_dev->close(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_lo_freq_set(struct rf_device *rf_dev, uint32 freq)
{
    if (rf_dev && rf_dev->lo_freq_set) {
        return rf_dev->lo_freq_set(rf_dev, freq);
    }
    return RET_ERR;
}

static inline int32 rf_device_check_lo_lock(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->check_lo_lock) {
        return rf_dev->check_lo_lock(rf_dev);
    }
    return RET_ERR;
}

//for open or close lo table control mode
static inline int32 rf_device_lo_table_ctrl(struct rf_device *rf_dev, uint8 onoff)
{
    if (rf_dev && rf_dev->lo_table_ctrl) {
        return rf_dev->lo_table_ctrl(rf_dev, onoff);
    }
    return RET_ERR;
}

static inline int32 rf_device_lo_table_cfg(struct rf_device *rf_dev, uint32 *freq_list, uint16 count)
{
    if (rf_dev && rf_dev->lo_table_cfg) {
        return rf_dev->lo_table_cfg(rf_dev, freq_list, count);
    }
    return RET_ERR;
}
// add hu 191216
static inline int32 rf_device_lo_table_kick(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->lo_table_kick) {
        return rf_dev->lo_table_kick(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_tx_dcoc_calib(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->tx_dcoc_calib) {
        return rf_dev->tx_dcoc_calib(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_dpd_dcoc_calib(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->dpd_dcoc_calib) {
        return rf_dev->dpd_dcoc_calib(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_rx_dcoc_calib(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->rx_dcoc_calib) {
        return rf_dev->rx_dcoc_calib(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_vco_calib(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->vco_calib) {
        return rf_dev->vco_calib(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_tx_imb_calib(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->tx_imb_calib) {
        return rf_dev->tx_imb_calib(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_dpd_imb_calib(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->dpd_imb_calib) {
        return rf_dev->dpd_imb_calib(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_rx_imb_calib(struct rf_device *rf_dev, uint8 rx_bw, uint8 gain_idx)
{
    if (rf_dev && rf_dev->rx_imb_calib) {
        return rf_dev->rx_imb_calib(rf_dev, rx_bw, gain_idx);
    }
    return RET_ERR;
}

static inline int32 rf_device_tx_power_set(struct rf_device *rf_dev, int8 tx_power_dbm)
{
    if (rf_dev && rf_dev->tx_power_set) {
        return rf_dev->tx_power_set(rf_dev, tx_power_dbm);
    }
    return RET_ERR;
}

static inline int32 rf_device_rx_gain_set(struct rf_device *rf_dev, int8 rx_gain_db)
{
    if (rf_dev && rf_dev->rx_gain_set) {
        return rf_dev->rx_gain_set(rf_dev, rx_gain_db);
    }
    return RET_ERR;
}

static inline int32 rf_device_soft_reset(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->soft_reset) {
        return rf_dev->soft_reset(rf_dev);
    }
    return RET_ERR;
}

//read all regs
static inline int32 rf_device_rf_regs_read(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->rf_regs_read) {
        return rf_dev->rf_regs_read(rf_dev);
    }
    return RET_ERR;
}

//read a single reg
static inline int32 rf_device_read_reg(struct rf_device *rf_dev, uint16 reg_addr)
{
    if (rf_dev && rf_dev->read_reg) {
        return rf_dev->read_reg(rf_dev, reg_addr);
    }
    return RET_ERR;
}

static inline int32 rf_device_write_reg(struct rf_device *rf_dev, uint16 reg_addr, uint16 reg_val)
{
    if (rf_dev && rf_dev->write_reg) {
        return rf_dev->write_reg(rf_dev, reg_addr, reg_val);
    }
    return RET_ERR;
}

static inline int32 rf_device_rx_bb_ana_out(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->rx_bb_ana_out) {
        return rf_dev->rx_bb_ana_out(rf_dev);
    }
    return RET_ERR;
}

static inline int32 rf_device_tx_bb_ana_out(struct rf_device *rf_dev)
{
    if (rf_dev && rf_dev->tx_bb_ana_out) {
        return rf_dev->tx_bb_ana_out(rf_dev);
    }
    return RET_ERR;
}

#ifdef __cplusplus
}
#endif
#endif

