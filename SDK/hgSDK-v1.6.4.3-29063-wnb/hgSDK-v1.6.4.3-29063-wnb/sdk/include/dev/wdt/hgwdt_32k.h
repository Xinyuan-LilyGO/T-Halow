#ifndef _HGWDT_32K_H
#define _HGWDT_32K_H

#ifdef __cplusplus
extern "C" {
#endif

#define HG_WDT_RESET_INT             0x1
#define HG_WDT_RESTART_COUNTER       0x76
#define HG_WDT_INT_PEND              0x1
#define HG_WDT_TOP_INIT(n)          (((n)&0xF)<<4)
#define HG_WDT_TOP(n)               (((n)&0xF)<<0)
#define HG_WDT_EN                   (1<<0)
#define HG_WDT_NORMAL               (1<<1)
#define HG_WDT_INT_CLR              (1<<0)
#define HG_WDT_CLOCK                (32.768)

enum wdt_work_mode {
    WDT_NORMAL = 0,
    WDT_TEST   = 2
};

enum wdt_plck_cycles {
    WDT_PCLK_CYCLES1 = 0x0,
    WDT_PCLK_CYCLES2 = 0x1,
    WDT_PCLK_CYCLES3 = 0x2,
    WDT_PCLK_CYCLES4 = 0x3,
    WDT_PCLK_CYCLES5 = 0x4,
    WDT_PCLK_CYCLES6 = 0x5,
    WDT_PCLK_CYCLES7 = 0x6,
    WDT_PCLK_CYCLES8 = 0x7,
};

struct hgwdt_32k_hw {
    __IO uint32 WDT_CR;
    __IO uint32 WDT_TORR;
    __IO uint32 WDT_CCVR;
    __IO uint32 WDT_CRR;
    __IO uint32 WDT_STAT;
    __IO uint32 WDT_EOI;
    uint32 WDT_RSV[51];
    __IO uint32 WDT_COMP_PARAMS_5;
    __IO uint32 WDT_COMP_PARAMS_4;
    __IO uint32 WDT_COMP_PARAMS_3;
    __IO uint32 WDT_COMP_PARAMS_2;
    __IO uint32 WDT_COMP_PARAMS_1;
    __IO uint32 WDT_COMP_VERSION;
    __IO uint32 WDT_COMP_TYPE;
};

struct hgwdt_32k {
    struct watchdog_device  dev;
    struct hgwdt_32k_hw    *hw;
    wdt_irq_hdl         irq_hdl;
    uint32              irq_num;
    uint32              clock;
};

int32 hgwdt_32k_attach(uint32 dev_id, struct hgwdt_32k *watchdog);
#ifdef __cplusplus
}
#endif


#endif
















































