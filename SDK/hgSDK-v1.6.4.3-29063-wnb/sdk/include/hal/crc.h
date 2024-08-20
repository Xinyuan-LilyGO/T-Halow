#ifndef _HAL_CRC_H_
#define _HAL_CRC_H_
#ifdef __cplusplus
extern "C" {
#endif

enum CRC_TYPE {
    CRC_TYPE_CRC5_USB = 0   ,
    CRC_TYPE_CRC7_MMC       ,
    CRC_TYPE_CRC8_ITU       ,
    CRC_TYPE_CRC8           ,
    CRC_TYPE_CRC16_MODBUS   ,
    CRC_TYPE_CRC32_WINRAR   ,
};

struct crc_dev_req {
    uint32 type;
    uint8 *data;
    uint32 len;
};

struct crc_dev {
    struct dev_obj dev;
    int32(*calc)(struct crc_dev *calc, struct crc_dev_req *req, uint32 *crc_val);
    int32(*kick)(struct crc_dev *calc, struct crc_dev_req *req);
    uint32(*get)(struct crc_dev *calc);
};

static inline int32 crc_dev_calc(struct crc_dev *dev, struct crc_dev_req *req, uint32 *crc_val)
{
    return (dev && dev->calc) ? dev->calc(dev, req, crc_val) : 0;
}

static inline int32 crc_dev_kick(struct crc_dev *dev, struct crc_dev_req *req)
{
    return (dev && dev->kick) ? dev->kick(dev, req) : 0;
}

static inline uint32 crc_dev_get(struct crc_dev *dev)
{
    return (dev && dev->get) ? dev->get(dev) : 0;
}

#ifdef __cplusplus
}
#endif

#endif

