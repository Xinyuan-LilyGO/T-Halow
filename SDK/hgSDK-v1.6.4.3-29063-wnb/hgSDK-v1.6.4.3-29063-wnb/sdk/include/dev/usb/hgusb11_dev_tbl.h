/*****************************************************************************
 * Module    : usb
 * File      : usb_dev_tbl.h
 * Author    : 
 * Function  : USB驱动的一些常量表的申明
 *****************************************************************************/
#ifndef USB_DEV_TBL_H
#define USB_DEV_TBL_H

#ifdef __cplusplus
 extern "C" {
#endif
     
    
extern const uint8_t tbl_usb_device_descriptor[18];
extern const uint8_t tbl_usb_config_all_descriptor_gen[9];
extern const uint8_t tbl_usb_config_all_descriptor_wifi[23];
extern const uint8_t tbl_usb_config_all_descriptor_mass[23];
extern const uint8_t tbl_usb_config_all_descriptor_audio_ctrl_head[19];
extern const uint8_t tbl_usb_config_all_descriptor_audio_ctrl_speaker[31];
extern const uint8_t tbl_usb_config_all_descriptor_audio_ctrl_mic[30];
extern const uint8_t tbl_usb_config_all_descriptor_speaker_stream[52];
extern const uint8_t tbl_usb_config_all_descriptor_mic_stream[52];
extern const uint8_t tbl_usb_config_all_descriptor_hid[25];
extern const uint8_t tbl_usb_hid_report_descriptor[33];
extern const uint8_t tbl_usb_language_id[4];
extern const uint8_t tbl_usb_str_manufacturer[16];
extern const uint8_t tbl_usb_str_product[28];
extern const uint8_t tbl_usb_str_serial_number[30];
extern const uint8_t tbl_scsi_inquiry_data[36];

#ifdef __cplusplus
}
#endif

#endif

