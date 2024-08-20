#include "typesdef.h"
#include "list.h"
#include "errno.h"
#include "dev.h"
#include "devid.h"
#include "osal/string.h"
#include "osal/semaphore.h"
#include "osal/mutex.h"
#include "osal/irq.h"
#include "dev/crc/hg_crc.h"
#include "hal/crc.h"

struct hgcrc_config {
    char  *name;
    uint32 poly;
    uint32 poly_bits;
    uint32 init_val;
    uint32 xor_out;
    char   ref_in;
    char   ref_out;
};

const struct hgcrc_config hgcrc_cfg[] = {
    [CRC_TYPE_CRC5_USB] = {
        .name = "crc5-usb",
        .init_val = 0x1f,
        .xor_out = 0x1f,
        .poly = 0x14,
        .poly_bits = 5,
        .ref_in = 1,
        .ref_out = 1,
    },
    [CRC_TYPE_CRC7_MMC] = {
        .name = "crc7-mmc",
        .init_val = 0x0,
        .xor_out = 0x0,
        .poly = 0x48,
        .poly_bits = 7,
        .ref_in = 0,
        .ref_out = 0,
    },
    [CRC_TYPE_CRC8_ITU] = {
        .name = "crc8-itu",
        .init_val = 0x0,
        .xor_out = 0x55,
        .poly = 0xE0,
        .poly_bits = 8,
        .ref_in = 0,
        .ref_out = 0,
    },
    [CRC_TYPE_CRC8] = {
        .name = "crc8",
        .init_val = 0x0,
        .xor_out = 0x00,
        .poly = 0xE0,
        .poly_bits = 8,
        .ref_in = 0,
        .ref_out = 0,
    },    
    [CRC_TYPE_CRC16_MODBUS] = {
        .name = "crc16-modbus",
        .init_val = 0xFFFF,
        .xor_out = 0x0,
        .poly = 0xA001,
        .poly_bits = 16,
        .ref_in = 1,
        .ref_out = 1,
    },
    [CRC_TYPE_CRC32_WINRAR] = {
        .name = "crc32-winrar",
        .init_val = 0xFFFFFFFF,
        .xor_out = 0xFFFFFFFF,
        .poly = 0xEDB88320,
        .poly_bits = 32,
        .ref_in = 1,
        .ref_out = 1,
    },
};

static void hg_crc_irq_handler(void *data)
{
    struct hg_crc *crc = (struct hg_crc *)data;
    crc->hw->CRC_KST = LL_CRC_KST_DMA_PENDING_CLR;
    os_sema_up(&crc->done);
}

static int32 hg_crc_calc(struct crc_dev *crc, struct crc_dev_req *req, uint32 *crc_value)
{
    int32 tmo = 2000;
    int32 ret = 0;
    struct hg_crc *dev = (struct hg_crc *)crc;
    const struct hgcrc_config *p_cfg;
    uint32 cfg_reg = 0;

    if (req == NULL || req->data == NULL || req->len == 0) {
        return RET_OK;
    }

    if (req->type < sizeof(hgcrc_cfg)/sizeof(struct hgcrc_config)) {
        p_cfg = &hgcrc_cfg[req->type];
    } else {
        return -EINVAL;
    }

    ret = os_mutex_lock(&dev->lock, tmo);
    if (ret) {
        os_printf("crc dev tx timeout!\r\n");
        return RET_ERR;
    }

    cfg_reg  = (dev->hw->CRC_CFG & LL_CRC_CFG_INT_EN) | \
               LL_CRC_CFG_POLY_BITS(p_cfg->poly_bits) | \
               LL_CRC_CFG_DMAWAIT_CLOCK(5);

    if (p_cfg->ref_in) {
        cfg_reg |= LL_CRC_CFG_BIT_ORDER_RIGHT;
    } else {
        cfg_reg |= LL_CRC_CFG_BIT_ORDER_LEFT;
    }

    /* config */
    dev->hw->CRC_INIT = p_cfg->init_val;
    dev->hw->CRC_INV  = p_cfg->xor_out;
    dev->hw->CRC_POLY = p_cfg->poly;
    dev->hw->CRC_CFG  = cfg_reg;

    /* kick */
    dev->hw->DMA_ADDR = (uint32)req->data;
    dev->hw->DMA_LEN  = req->len;

    ret = os_sema_down(&dev->done, tmo);

    *crc_value = dev->hw->CRC_OUT;
    os_mutex_unlock(&dev->lock);
    return ret > 0 ? RET_OK : RET_ERR;
}

/* Start the hardware crc calculation first */
static int32 hg_crc_kick(struct crc_dev *crc, struct crc_dev_req *req)
{
    int32 tmo = 2000;
    int32 ret = 0;
    struct hg_crc *dev = (struct hg_crc *)crc;
    const struct hgcrc_config *p_cfg;
    uint32 cfg_reg = 0;

    if (req == NULL || req->data == NULL || req->len == 0) {
        return RET_OK;
    }

    if (req->type < sizeof(hgcrc_cfg)/sizeof(struct hgcrc_config)) {
        p_cfg = &hgcrc_cfg[req->type];
    } else {
        return -EINVAL;
    }

    ret = os_mutex_lock(&dev->lock, tmo);
    if (ret) {
        os_printf("crc dev tx timeout!\r\n");
        return RET_ERR;
    }

    cfg_reg  = (dev->hw->CRC_CFG & LL_CRC_CFG_INT_EN) | \
               LL_CRC_CFG_POLY_BITS(p_cfg->poly_bits) | \
               LL_CRC_CFG_DMAWAIT_CLOCK(5);

    if (p_cfg->ref_in) {
        cfg_reg |= LL_CRC_CFG_BIT_ORDER_RIGHT;
    } else {
        cfg_reg |= LL_CRC_CFG_BIT_ORDER_LEFT;
    }

    /* config */
    dev->hw->CRC_INIT = p_cfg->init_val;
    dev->hw->CRC_INV  = p_cfg->xor_out;
    dev->hw->CRC_POLY = p_cfg->poly;
    dev->hw->CRC_CFG  = cfg_reg;

    /* kick */
    dev->hw->DMA_ADDR = (uint32)req->data;
    dev->hw->DMA_LEN  = req->len;
    return RET_OK;
}

/* Then get the crc calculation result */
static uint32 hg_crc_get(struct crc_dev *crc)
{
    int32 tmo = 2000;
    struct hg_crc *dev = (struct hg_crc *)crc;
    uint32 crc_value;

    os_sema_down(&dev->done, tmo);
    
    crc_value = dev->hw->CRC_OUT;

    os_mutex_unlock(&dev->lock);
    return crc_value;
}

__init int32 hg_crc_attach(uint32 dev_id, struct hg_crc *crc)
{
#if defined(TX4001A)
    return RET_ERR;
#else
    crc->dev.calc   = hg_crc_calc;
    crc->dev.kick   = hg_crc_kick;
    crc->dev.get    = hg_crc_get;
    os_mutex_init(&crc->lock);
    os_sema_init(&crc->done, 0);
    SYSCTRL_REG_OPT(
        sysctrl_crc_clk_open();
        sysctrl_crc_reset();
    );
    request_irq(crc->irq_num, hg_crc_irq_handler, crc);
    crc->hw->CRC_CFG |= LL_CRC_CFG_INT_EN;
    irq_enable(crc->irq_num);
    dev_register(dev_id, (struct dev_obj *)crc);
    return RET_OK;
#endif
}




