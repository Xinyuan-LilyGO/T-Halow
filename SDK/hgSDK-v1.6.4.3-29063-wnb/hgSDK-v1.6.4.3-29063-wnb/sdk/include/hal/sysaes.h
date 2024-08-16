#ifndef _HAL_SYSAES_H_
#define _HAL_SYSAES_H_

#ifdef __cplusplus
extern "C" {
#endif

struct sysaes_para {
    uint8  mode;
    uint8 *src;
    uint8 *dest;
    uint32 block_num;
    uint32 key[8];
};

struct sysaes_dev {
    struct dev_obj dev;
    int32(*encrypt)(struct sysaes_dev *dev, struct sysaes_para *para);
    int32(*decrypt)(struct sysaes_dev *dev, struct sysaes_para *para);
};

static inline int32 sysaes_encrypt(struct sysaes_dev *dev, struct sysaes_para *para)
{
    if(dev && dev->encrypt) {
        return dev->encrypt(dev, para);
    }
    return RET_ERR;
}

static inline int32 sysaes_decrypt(struct sysaes_dev *dev, struct sysaes_para *para)
{
    if(dev && dev->decrypt) {
        return dev->decrypt(dev, para);
    }
    return RET_ERR;
}

#ifdef __cplusplus
}
#endif
#endif /* _HAL_SYSAES_H_ */

