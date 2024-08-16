#ifndef _LMAC_RX_H_
#define _LMAC_RX_H_

#ifdef __cplusplus
extern "C" {
#endif

struct s1g_rx_vec_ndp_1m {
    uint64      ndp_body :   25,    //B3[0],B2[7:0],B1[7:0],B0[7:0],
                ndp_ind  :   1,     //B3[1]
                crc4     :   4,     //[5:2]
                reserved1:   34;
};
struct s1g_rx_vec_ndp_2m {
    uint64      ndp_body :   37,    //B4[4:0],B3[7:0],B2[7:0],B1[7:0],B0[7:0]
                ndp_ind  :   1,     //B4[5]
                crc4     :   4,     //B5[1:0],B4[7:6]
                reserved1:   22;
};

struct s1g_rx_vec_frm_1m {
    uint64      nsts        :   2,  //B0[1:0]
                short_gi    :   1,  //B0[2]
                coding      :   1,  //B0[3]
                ldpc_extra  :   1,  //B0[4]
                stbc        :   1,  //B0[5]
                reserved    :   1,  //B0[6]
                mcs         :   4,  //B1[2:0],B0[7]
                aggregation :   1,  //B1[3]
                length      :   9,  //B2[4:0],B1[7:4]
                resp_ind    :   2,  //B2[6:5]
                smoothing   :   1,  //B2[7]
                travel_pilot:   1,  //B3[0]
                ndp_ind     :   1,  //B3[1]
                crc4        :   4,  //B3[5:2]
                reserved1   :   26, //B6[7:0],B5[7:0],B4[7:0],B3[7:6]
                sym_cnt70   :   8;  //B7[7:0]
    uint64      sym_cnt98   :   2,  //B8[1:0]
                reserved2   :   62;

};

struct s1g_rx_vec_frm_short {
    uint64      reserved    :   1,  //B0[0]
                stbc        :   1,  //B0[1]
                uplink_ind  :   1,  //B0[2]
                band_width  :   2,  //B0[4:3]
                nsts        :   2,  //B0[6:5]
                id          :   9,  //B1[7:0],B0[7]
                short_gi    :   1,  //B2[0]
                coding      :   1,  //B2[1]
                ldpc_extra  :   1,  //B2[2]
                mcs         :   4,  //B2[6:3]
                smoothing   :   1,  //B2[7]
                aggregation :   1,  //B3[0]
                length      :   9,  //B4[1:0],B3[7:1]
                resp_ind    :   2,  //B4[3:2]
                travl_pilot :   1,  //B4[4]
                ndp_ind     :   1,  //B4[5]
                crc4        :   4,  //B5[1:0],B4[7:6]
                reserved1   :   14, //B6[7:0],B5[7:2]
                sym_cnt70   :   8;  //B7[7:0]
    uint64      sym_cnt98   :   2,  //B8[1:0]
                reserved2   :   62;
};

struct s1g_rx_vec_frm_long {
    uint64      mu_su       :   1,  //B0[0]
                stbc        :   1,  //B0[1]
                uplink_ind  :   1,  //B0[2]
                band_width  :   2,  //B0[4:3]
                nsts        :   2,  //B0[6:5]
                id          :   9,  //B1[7:0],B0[7]
                short_gi    :   1,  //B2[0]
                coding      :   1,  //B2[1]
                ldpc_extra  :   1,  //B2[2]
                mcs         :   4,  //B2[6:3]
                smoothing   :   1,  //B2[7]
                aggregation :   1,  //B3[0]
                length      :   9,  //B4[1:0],B3[7:1]
                resp_ind    :   2,  //B4[3:2]
                reserved1   :   1,  //B4[4]
                travl_pilot :   1,  //B4[5]
                crc4        :   4,  //B5[1:0],B4[7:6]
                reserved2   :   14, //B6[7:0],B5[7:2]
                sym_cnt70   :   8;  //B7[7:0]
    uint64      sym_cnt98   :   2,  //B8[1:0]
                reserved3   :   62;
};


struct s1g_rx_vector {
    union {
        struct s1g_rx_vec_ndp_1m        ndp_1m;
        struct s1g_rx_vec_ndp_2m        ndp_2m;
        struct s1g_rx_vec_frm_1m        frm_1m;
        struct s1g_rx_vec_frm_short     frm_short;
        struct s1g_rx_vec_frm_long      frm_long;
        uint32 rx_vec_val[4];
        uint64 ndp;
    };
};

void lmac_rx_init(struct lmac_init_param *param);
void lmac_irq_rx_subframe(void);
void lmac_irq_rx_end(void);
void update_rx_buff_addr(void);
int32 lmac_rx_data_queue_put(void *frm_info, int32 count);
int32 lmac_rx_data_queue_count(void);
int32 lmac_rx_iface_queue_count(void);
void pd_timer_irq_handler(void *data);

#ifdef __cplusplus
}
#endif

#endif


