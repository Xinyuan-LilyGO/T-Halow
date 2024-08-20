#ifndef _HUGEIC_DEV_H_
#define _HUGEIC_DEV_H_

#ifdef __cplusplus
extern "C" {
#endif

struct dev_obj{
    int32 dev_id;
    struct list_head list;
};

/**
 * dev core module initialize
 * @return return RET_OK if initialize sucess, else return RET_ERR.
 **/
extern int32 dev_init(void);

/**
 * get dev by dev_id
 * @param[in] dev_id device id
 * @return return device object if device exist, else return NULL.
 **/
extern struct dev_obj *dev_get(int32 dev_id);

/**
 * register device into dev manager.
 * @param[in] device object to register.
 * @return return RET_OK if register sucess, else return RET_ERR.
 **/
extern int32 dev_register(uint32 dev_id, struct dev_obj *device);

/**
 * unregister device, after device unregisted, it can not find by dev_get()
 * @param[in] device object to unregister.
 * @return return RET_OK if unregister sucess, else return RET_ERR.
 **/
extern int32 dev_unregister(struct dev_obj *device);

extern int32 pin_func(int32 dev_id, int32 request);

extern void user_pin_func(int dev_id, int request);

#ifdef __cplusplus
}
#endif

#endif
