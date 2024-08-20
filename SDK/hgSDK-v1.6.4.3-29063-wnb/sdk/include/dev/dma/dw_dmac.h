#ifndef _DW_DMAC_H_
#define _DW_DMAC_H_

#include "hal/dma.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! max dmac hardware channel
 */
#define DW_DMAC_MAX_DMAC_CHN                    4
/*! max dmac hardware channel mask
 */
#define DW_DMAC_MAX_DMAC_CHN_MASK               0xF

/**
  * @brief DMAC controller (IP)
  */
struct dw_dmac_hw_ch {
    __IO uint32 SARL;
    __IO uint32 SARH;
    __IO uint32 DARL;
    __IO uint32 DARH;
    __IO uint32 FIFO0[2];     //LLPL,LLPH, NO USE
    __IO uint32 CTLL;
    __IO uint32 CTLH;
    __IO uint32 FIFO1[8];     //SSTATL,SSTATH,DSTATL,DSTATH,SSTATARL,SSTATARH,DSTATARL,DSTATARH
    __IO uint32 CFGL;
    __IO uint32 CFGH;
    __IO uint32 SGRL;
    __IO uint32 SGRH;
    __IO uint32 DSRL;
    __IO uint32 DSRH;
};
    
/**
  * @brief DMAC
  */
struct hgdma_dw_hw {
    struct dw_dmac_hw_ch CH[4];
    __IO uint32        FIFO0[22*4];
    __IO uint32        RawTfrL;
    __IO uint32        RawTfrH;
    __IO uint32        RawBlockL;
    __IO uint32        RawBlockH;
    __IO uint32        RawSrcTranL;
    __IO uint32        RawSrcTranH;
    __IO uint32        RawDstTranL;
    __IO uint32        RawDstTranH;
    __IO uint32        RawErrL;
    __IO uint32        RawErrH;
    __IO uint32        FIFO1[5*2];
    __IO uint32        MaskTfrL;
    __IO uint32        MaskTfrH;
    __IO uint32        MaskBlockL;
    __IO uint32        MaskBlockH;
    __IO uint32        MaskSrcTranL;
    __IO uint32        MaskSrcTranH;
    __IO uint32        MaskDstTranL;
    __IO uint32        MaskDstTranH;
    __IO uint32        MaskErrL;
    __IO uint32        MaskErrH;
    __IO uint32        ClearTfrL;
    __IO uint32        ClearTfrH;
    __IO uint32        ClearBlockL;
    __IO uint32        ClearBlockH;
    __IO uint32        ClearSrcTranL;
    __IO uint32        ClearSrcTranH;
    __IO uint32        ClearDstTranL;
    __IO uint32        ClearDstTranH;
    __IO uint32        ClearErrL;
    __IO uint32        ClearErrH;
    __IO uint32        FIFO2[2];
    __IO uint32        ReqSrcRegL;
    __IO uint32        ReqSrcRegH;
    __IO uint32        ReqDstRegL;
    __IO uint32        ReqDstRegH;
    __IO uint32        SglReqSrcRegL;
    __IO uint32        SglReqSrcRegH;
    __IO uint32        SglReqDstRegL;
    __IO uint32        SglReqDstRegH;
    __IO uint32        LstSrcRegL;
    __IO uint32        LstSrcRegH;
    __IO uint32        LstDstRegL;
    __IO uint32        LstDstRegH;
    __IO uint32        DmaCfgRegL;
    __IO uint32        DmaCfgRegH;
    __IO uint32        ChEnRegL;
    __IO uint32        ChEnRegH;
    __IO uint32        FIFO3[2];
    __IO uint32        DmaTestRegL;
    __IO uint32        DmaTestRegH;
};

struct hgdma_dw {
    struct dma_device      dev;
    struct hgdma_dw_hw   *hw;
    uint32               irq_num;
    uint32               opened;
    struct os_semaphore  mem_chn;
    struct os_semaphore  dev_chn;
    struct os_mutex      dev_mutex;
    dma_irq_hdl          irq_hdl[DW_DMAC_MAX_DMAC_CHN];
    uint32               irq_data[DW_DMAC_MAX_DMAC_CHN];
    uint32               state[DW_DMAC_MAX_DMAC_CHN];
    uint32               chn_used_flag;
};

/** @brief DW DMAC register constant table definition
  * @{
  */

/***** DW_PARAMS Register *****/
/*! number of channels
 */
#define DW_DMAC_PARAMS_NR_CHAN                  4
/*! number of AHB masters
 */
#define DW_DMAC_PARAMS_NR_MASTER                2


/***** DWC_PARAMS Register *****/
/*! multi block transfer
 */
#define DW_DMACC_PARAMS_MBLK_EN                 11


/***** CTLx Register *****/
/*! irqs enabled
 */
#define DW_DMAC_CTLL_INT_EN                     (1UL << 0)
/*! The size of each element of destination transmission.
 */
#define DW_DMAC_CTLL_DST_WIDTH(n)               (((n)&0x7) << 1)
/*! The size of each element of source transmission.
 */
#define DW_DMAC_CTLL_SRC_WIDTH(n)               (((n)&0x7) << 4)
/*! Indicates destination address how to change on every source transfer.
 */
#define DW_DMAC_CTLL_DST_DIR(n)                 (((n)&0x3) << 7)
/*! Indicates source address how to change on every source transfer.
 */
#define DW_DMAC_CTLL_SRC_DIR(n)                 (((n)&0x3) << 9)
/*! Number of data items to be written to de destination every time. 
 */
#define DW_DMAC_CTLL_DST_MSIZE(n)               (((n)&0x7) << 11)
/*! Number of data items to be read from the source every time. 
 */
#define DW_DMAC_CTLL_SRC_MSIZE(n)               (((n)&0x7) << 14)
/*! src gather
 */
#define DW_DMAC_CTLL_S_GATH_EN                  (1UL << 17)
/* dst scatter 
 */
//#define DW_DMAC_CTLL_D_SCAT_EN                (1UL << 18)
/*! Transfer type and flow control.
 */
#define DW_DMAC_CTLL_FC(n)                      (((n)&0x7) << 20)
/*! dst master select : 1 for memory, 0 for peripherals
 */
#define DW_DMAC_CTLL_DMS(n)                     (((n)&0x3) << 23)
/*! src master select : 1 for memory, 0 for peripherals
 */
#define DW_DMAC_CTLL_SMS(n)                     (((n)&0x3) << 25)
/* dest block chain 
 */
//#define DW_DMAC_CTLL_LLP_D_EN                   (1UL << 27)
/* src block chain 
 */
//#define DW_DMAC_CTLL_LLP_S_EN                   (1UL << 28)


/***** CTL_HI Register *****/
/*! Block transfer done
 */
#define DW_DMAC_CTLH_DONE                       (0x00001000)
/*! Block transfer size. The max block size is 4095.
 */
#define DW_DMAC_CTLH_BLOCK_TS_MASK              (0x00000FFF)


/***** CFG_LO Register *****/
/*! Channel priority mask
 */
#define DW_DMAC_CFGL_CH_PRIOR_MASK              (0x7UL << 5)
/*! Channel priority
 */
#define DW_DMAC_CFGL_CH_PRIOR(n)                (((n)&0x7) << 5)
/*! Channle Suspend. Suspends all DMA data transfers from the source until this
 *  bit is cleared.
 */
#define DW_DMAC_CFGL_CH_SUSP                    (1UL << 8)
/*! Indicates if there is data left in the channel FIFO.
 */
#define DW_DMAC_CFGL_FIFO_EMPTY                 (1UL << 9)
/*! Destination software or hardware handshaking select.
 */
#define DW_DMAC_CFGL_HS_DST                     (1UL << 10)
/*! Source software or hardware handshaking select.
 */
#define DW_DMAC_CFGL_HS_SRC                     (1UL << 11)
//#define DW_DMAC_CFGL_LOCK_CH_LEVEL(n)           (((n)&0x3) << 12)
//#define DW_DMAC_CFGL_LOCK_BUS_LEVEL(n)          (((n)&0x3) << 14)
//#define DW_DMAC_CFGL_LOCK_CH                    (1UL << 16)
//#define DW_DMAC_CFGL_LOCK_BUS                   (1UL << 17)
/*! Destination handshaking interface polarity.
 */
#define DW_DMAC_CFGL_HS_DST_POL                 (1UL << 18)
/*! Source handshaking interface polarity.
 */
#define DW_DMAC_CFGL_HS_SRC_POL                 (1UL << 19)
/*! Maximum AMBA burst length that is used for DMA transfers on this channel.
 */
#define DW_DMAC_CFGL_MAX_BURST(n)               (((n)&0x2FF) << 20)
/*! Automatic source reload.
 */
#define DW_DMAC_CFGL_RELOAD_SAR                 (1UL << 30)
/*! Automatic desination reload.
 */
#define DW_DMAC_CFGL_RELOAD_DAR                 (1UL << 31)


/***** CFG_HI Register *****/
/*! Flow control mode.
 */
#define DW_DMAC_CFGH_FCMODE                     (1UL << 0)
/*! FIFO mode select.
 */
#define DW_DMAC_CFGH_FIFO_MODE                  (1UL << 1)
/*! Protection control.
 */
#define DW_DMAC_CFGH_PROTCTL(n)                 (((n)&0x7) << 2)
//#define DW_DMAC_CFGH_DS_UPD_EN                  (1UL << 5)
//#define DW_DMAC_CFGH_SS_UPD_EN                  (1UL << 6)
/*! Assigns a hardware handshaking interface to the source of channel.
 */
#define DW_DMAC_CFGH_SRC_PER(n)                 (((n)&0xF) << 7)
/*! Assigns a hardware handshaking interface to the destination of channel.
 */
#define DW_DMAC_CFGH_DST_PER(n)                 (((n)&0xF) << 11)


/***** SGR Register *****/
/*! Source gather interval.
 */
#define DW_DMAC_SGR_SGI(n)                      (((n)&0xFFFFF) << 0)
/*! Source gather count.
 */
#define DW_DMAC_SGR_SGC(n)                      (((n)&0xF) << 20)


/***** DSR Register *****/
//#define DW_DMAC_DSR_DSI(x)                      (((n)&0xFFFFF) << 0)
//#define DW_DMAC_DSR_DSC(x)                      (((n)&0xF) << 20)


/***** DmaCfgReg Register *****/
/*! dmac enable.
 */
#define DW_DMAC_CFG_DMA_EN                      (1UL << 0)

/***** ChEnRegL/MaskTfrL/MaskErrL/MaskDstTranL/MaskSrcTranL/MaskBlockL/ Register *****/
/*! Source gather count.
 */
#define DW_DMAC_WRITE_EN(n)                     ((1 << (n+8)) | (1 << n))
/*! Source gather count.
 */
#define DW_DMAC_WRITE_DIS(n)                    (1 << (n+8))

#define DW_DMAC_XFER_DONE(n)                    (1 << (n))
#define DW_DMAC_XFER_ERR(n)                     (1 << (n+8))


/**
  * @}
  */

/** @brief DW DMAC external constant definition
  * @{
  */

/**
  * @breif Number of data items to be transferred(of width TR_WIDTH)
  */
enum dw_dmac_msize {
    /*! damc data width : 1 TR_WIDTH
     */
    DW_DMAC_MSIZE_1,
    /*! damc data width : 4 TR_WIDTH
     */

    DW_DMAC_MSIZE_4,
    /*! damc data width : 8 TR_WIDTH
     */
    DW_DMAC_MSIZE_8,
    // The following MSIZE is not supported.
//    DW_DMAC_MSIZE_16,
//    DW_DMAC_MSIZE_32,
//    DW_DMAC_MSIZE_64,
//    DW_DMAC_MSIZE_128,
//    DW_DMAC_MSIZE_256,
};

/**
  * @brief The size of each element of destination transmission. The unit is bit.
  */
enum dw_dmac_tr_width {
    /*! damc xfer width : 8 bit
     */
    DW_DMAC_TR_8,
    /*! damc xfer width : 16bit
     */
    DW_DMAC_TR_16,
    /*! damc xfer width : 32bit
     */
    DW_DMAC_TR_32,
    // The following TR_WIDTH is not supported.0
//    DW_DMAC_TR_64,
//    DW_DMAC_TR_128,
//    DW_DMAC_TR_256,
};

/**
  * @brief Indicates destination address how to change on every source transfer.
  */
enum dw_dmac_addr_dir {
    /*! Increment
     */
    DW_DMAC_ADDR_INC,
    /*! Decrement
     */
    DW_DMAC_ADDR_DEC,
    /*! No change
     */
    DW_DMAC_ADDR_NO_CHANGE,
};

/**
  * @breif flow controller
@verbatim   
-------------------------------------------------------------------------------
CTLL.TT_FC Field        Transfer Type                   Flow Controller    
-------------------------------------------------------------------------------
      000               Memory to Memory                DW_anb_dmac
      001               Memory to Peripheral            DW_anb_dmac
      010               Peripheral to Memory            DW_anb_dmac
      011               Peripheral to Peripheral        DW_anb_dmac
      100               Peripheral to Memory            Peripheral
      101               Peripheral to Peripheral        Source Peripheral
      110               Memory to Peripheral            Peripheral
      111               Peripheral to Peripheral        Destination Peripheral
@endverbatim
  */
enum dw_dmac_fc {
    /*! Memory to Memory
     */
    DW_DMAC_FC_D_M2M,
    /*! Memory to Peripheral
     */
    DW_DMAC_FC_D_M2P,
    /*! Peripheral to Memory
     */
    DW_DMAC_FC_D_P2M,
    /*! Peripheral to Peripheral
     */
    DW_DMAC_FC_D_P2P,
    // The following flow control is not supported.
//  DW_DMAC_FC_P_P2M,
//  DW_DMAC_FC_SP_P2P,
//  DW_DMAC_FC_P_M2P,
//  DW_DMAC_FC_DP_P2P,
};

/**
  * @}
  */

int32 dw_dmac_search_src_id(uint32 addr);
int32 dw_dmac_search_dest_id(uint32 addr);
int32 dw_dmac_attach(uint32 dev_id, struct hgdma_dw *dmac);

#ifdef __cplusplus
}
#endif

#endif
