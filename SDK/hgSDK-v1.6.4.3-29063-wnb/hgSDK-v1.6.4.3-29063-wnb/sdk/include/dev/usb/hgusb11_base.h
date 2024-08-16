/*****************************************************************************
* Module    : usb
* File      : usb.c
* Author    :
* Function  : USB驱动的一些公用模块
*****************************************************************************/
#ifndef USB_H
#define USB_H

#ifdef __cplusplus
extern "C" {
#endif

//typedef int8 bool;

#define MAX_EP                  2      //最大的EP号

//in IC, in latest FPGA
#define USB_FIX_BUG_0                    0      //=0,       =1
#define USB_FIX_BUG_1                    0      //=1,       =1 
#define USB_FIX_BUG_2                    0      //=0,       =1 
#define USB_FIX_BUG_3                    0      //=0,       =1 
#define USB_FIX_BUG_4                    0      //=0,       =1 

#define UCFG2_CNT                       0x2000
//USB SIE REG(common)
#define M_FADDR               0x00
#define M_POWER               0x01
#define M_INTRTX1             0x02
#define M_INTRTX2             0x03
#define M_INTRRX1             0x04
#define M_INTRRX2             0x05
#define M_INTRUSB             0x06
#define M_INTRTX1E            0x07
#define M_INTRTX2E            0x08
#define M_INTRRX1E            0x09
#define M_INTRRX2E            0x0A
#define M_INTRUSBE            0x0B
#define M_FRAMENUM1           0x0C
#define M_FRAMENUM2           0x0D
#define M_INDEX               0x0E
#define M_DEVCTL              0x0F
//USB SIE REG(host & slave)
#define M_TXMAXP              0x10
#define M_CSR0                0x11
#define M_TXCSR1              0x11
#define M_TXCSR2              0x12
#define M_RXMAXP              0x13
#define M_RXCSR1              0x14
#define M_RXCSR2              0x15
#define M_COUNT0              0x16
#define M_RXCOUNT1            0x16
#define M_RXCOUNT2            0x17
#define M_TXTYPE              0x18
#define M_TXINTERVAL          0x19
#define M_RXTYPE              0x1A
#define M_RXINTERVAL          0x1B

#define M_FIFOSIZE            0x1F


#define M_FIFO0               0x20  //FIFOS for endpoint0
#define M_FIFO1               0x24  //FIFOS for endpoint1
#define M_FIFO2               0x28  //FIFOS for endpoint2

///USB DMA1_CTL/DMA2_CTL
#define UDC_BUS_ERR            (1<<15)
#define UDC_MAXPKT_8BYTE(n)    (((n)&0x7F)<<8)
#define UDC_EP(n)              (((n)&0xF)<<4)
#define UDC_IE                 (1<<3)
#define UDC_MODE(n)            (((n)&0x1)<<2)
#define UDC_DIR_RX             ((0)<<1)
#define UDC_DIR_TX             ((1)<<1)
#define UDC_EN                 ((1)<<0)

///UCFG1
#define DMA4_MASK               (1<<22)
#define DMA3_MASK               (1<<21)
#define DMA2_MASK               (1<<20)
#define DMA1_MASK               (1<<19)
#define VBUS_Error_MASK         (1<<18)
#define Sess_Req_MASK           (1<<17)
#define Discon_MASK             (1<<16)
#define Conn_MASK               (1<<15)
#define Reset_MASK              (1<<14)
#define Resume_MASK             (1<<13)
#define Suspend_MASK            (1<<12)
#define EP2TX_MASK              (1<<11)
#define EP1TX_MASK              (1<<10)
#define EP0_MASK                (1<<9)
#define EP2RX_MASK              (1<<8)
#define EP1RX_MASK              (1<<7)
#define SOF_MASK                (1<<6)

#define USB_DIF                 (1<<3)
#define USB_DIM                 (1<<2)
#define USB_DIP                 (1<<1)
#define USB_TM1                 (1<<0)      ///0: normal mode  1:testmode, shorter time for simulation

#define USBIE_EN()              //NVIC_EnableIRQ(USB_CTL_IRQn);
#define USBIE_DIS()             //NVIC_DisableIRQ(USB_CTL_IRQn);

#define USB_REG_CRITICAL_ENTER()  //osMutexWait(usb_reg_lock_id, osWaitForever);  
#define USB_REG_CRITICAL_EXIT()  //osMutexRelease(usb_reg_lock_id);

//写USB SIE寄存器
#define write_usb_reg(reg_addr, reg_data)   do {p_dev->usb_hw->SIE##reg_addr = reg_data;} while(0)
//void write_usb_reg_index(uint8_t index, uint32_t reg_addr, uint8_t reg_data);
#define write_usb_reg_index(index, reg_addr, reg_data)\
        do {\
            USB_REG_CRITICAL_ENTER();\
            p_dev->usb_hw->SIEM_INDEX = index;\
            *((volatile uint8_t *)((uint32_t)&p_dev->usb_hw->SIEM_FADDR + reg_addr)) = reg_data;\
            USB_REG_CRITICAL_EXIT();\
        } while(0)


//读USB SIE寄存器
#define read_usb_reg(reg_addr)              (p_dev->usb_hw->SIE##reg_addr)
//uint8_t read_usb_reg_index(uint8_t index, uint32_t reg_addr);
#define read_usb_reg_index(index, reg_addr, reg_data)\
        do {\
            USB_REG_CRITICAL_ENTER();\
            p_dev->usb_hw->SIEM_INDEX = index;\
            reg_data = *((volatile uint8_t *)((uint32_t)&p_dev->usb_hw->SIEM_FADDR + reg_addr));\
            USB_REG_CRITICAL_EXIT();\
        } while(0)




//USB当前状态机
enum {
    USB_DEFAULT_STATE,
    USB_ADDRESS_STATE,
    USB_CONFIG_STATE
};

//EP0状态机
enum {
    IDLE_STATE,
    TRANSER_OVER_STATE,
    TRANSFERING_STATE,
    RECEIVING_STATE
};

//接收者
enum {
    REQUEST_TO_DEVICE,
    REQUEST_TO_INTERFACE,
    REQUEST_TO_ENDPOINT
};

//设备描述符
enum {
    DEVICE_DESCRIPTOR = 1,
    CONFIGURATION_DESCRIPTOR,
    STRING_DESCRIPTOR,
    INTERFACE_DESCRIPTOR,
    ENDPOINT_DESCRIPTOR,
    DEVICE_QUALIFIER_DESCRIPTOR,
//    OTHER_SPEED_CONFIG_DESCRIPTOR,  USB 1.1没有该选项

    HID_REPORT = 0x22,
};

//Feature Selector
enum {
    ENDPOINT_STALL,
    REMOTE_WAKEUP,
    TEST_MODE
};

//检测模式
enum {
    USB_CHECK_HOST,         //尝试主机检测
    USB_CHECK_OTG,          //尝试OTG检测，是否连接PC
    USB_STABLE_HOST,        //已成功检测为USB主机
    USB_STABLE_DEVICE,      //已成功检测为USB设备
};

//返回值
enum {
    USB_CONNECTED_NONE,     //未连接
    USB_CONNECTED_PC,       //连接PC，当Device
    USB_CONNECTED_UDISK,    //外接U盘，当Host
};

//USB控制结构体
struct hgusb11_dev_ctrl {
    uint8_t error;            //USB通信错误

    struct {
        uint16_t vid;              //VID
        uint16_t pid;              //PID
        uint16_t ver;              //Version
    } info;

//EP0接收的命令
    struct {
        uint8_t rtype;
        uint8_t request;
        uint16_t value;
        uint16_t index;
        uint16_t length;
    } cmd;

    uint8_t reserved[2];
};

struct hgusb11_dev_chk {
    uint8_t check_mode;
    uint8_t check_cnt;
    uint8_t check_delay;
} ;


#define     BYTE0(n)            ((uint8_t)((uint16_t)(n)))
#define     BYTE1(n)            ((uint8_t)(((uint16_t)(n))>>8))
#define     BYTE2(n)            ((uint8_t)(((uint16_t)(((uint32_t)(n))>>8))>>8))
#define     BYTE3(n)            ((uint8_t)(((uint16_t)(((uint32_t)(n))>>16))>>8))

#define     LOAD_U32B(p)        ((((volatile uint8_t *)(p))[0]<<24) | (((volatile uint8_t *)(p))[1]<<16) | (((volatile uint8_t *)(p))[2]<<8) | (((volatile uint8_t *)(p))[3]<<0))
#define     LOAD_U32L(p)        ((((volatile uint8_t *)(p))[0]<<0)  | (((volatile uint8_t *)(p))[1]<<8)  | (((volatile uint8_t *)(p))[2]<<16)| (((volatile uint8_t *)(p))[3]<<24))
#define     LOAD_U16B(p)        ((((volatile uint8_t *)(p))[0]<<8) | (((volatile uint8_t *)(p))[1]<<0))
#define     LOAD_U16L(p)        ((((volatile uint8_t *)(p))[0]<<0) | (((volatile uint8_t *)(p))[1]<<8))

#define SAVE_U32B(p, num)   do { \
                                ((volatile uint8_t *)(p))[0] = BYTE3(num); \
                                ((volatile uint8_t *)(p))[1] = BYTE2(num); \
                                ((volatile uint8_t *)(p))[2] = BYTE1(num); \
                                ((volatile uint8_t *)(p))[3] = BYTE0(num); \
                            } while(0)

#define SAVE_U32L(p, num)   do { \
                                ((volatile uint8_t *)(p))[0] = BYTE0(num); \
                                ((volatile uint8_t *)(p))[1] = BYTE1(num); \
                                ((volatile uint8_t *)(p))[2] = BYTE2(num); \
                                ((volatile uint8_t *)(p))[3] = BYTE3(num); \
                            } while(0)

#define SAVE_U16B(p, num)   do { \
                                ((volatile uint8_t *)(p))[0] = BYTE1(num); \
                                ((volatile uint8_t *)(p))[1] = BYTE0(num); \
                            } while(0)

#define SAVE_U16L(p, num)   do { \
                                ((volatile uint8_t *)(p))[0] = BYTE0(num); \
                                ((volatile uint8_t *)(p))[1] = BYTE1(num); \
                            } while(0)


#ifdef __cplusplus
}
#endif

#endif
