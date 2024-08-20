#ifndef _HUGE_IC_PLATFORM_H_
#define _HUGE_IC_PLATFORM_H_

#define PRO_TYPE_LMAC 1
#define PRO_TYPE_UMAC 2
#define PRO_TYPE_WNB  3
#define PRO_TYPE_UAV  4
#define PRO_TYPE_FMAC 5
#define PRO_TYPE_IOTFMAC 6
#define PRO_TYPE_QA   66
#define PRO_TYPE_QC   88

#include "sys_config.h"

#ifdef TXW4002ACK803
#include "txw4002ack803/txw4002ack803.h"
#include "txw4002ack803/pin_names.h"
#include "txw4002ack803/sysctrl.h"
#endif


#endif
