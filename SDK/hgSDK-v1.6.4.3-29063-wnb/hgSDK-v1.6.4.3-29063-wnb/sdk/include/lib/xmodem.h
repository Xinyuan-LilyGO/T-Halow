#ifndef _XMODEM_LIB_H_
#define _XMODEM_LIB_H_

enum xmodem_flags {
    XMODEM_START,
    XMODEM_ACK,
    XMODEM_NAK,
    XMODEM_STOP,
};

struct xmodem_hdl {
    void (*out)(uint8 data);
    uint8(*in)(uint32 tmo, int32 *err);
    uint8 pktno;
};

int32 xmodem_receive(struct xmodem_hdl *xmodem, enum xmodem_flags flags, uint8 *buff, int32 size);
int32 xmodem_fwupgrade_hdl(const char *cmd, uint8 *data, int32 len);

#endif
