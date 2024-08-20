/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     drv_pwm.h
 * @brief    header file for pwm driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CSI_PWM_H_
#define _CSI_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>


/// definition for pwm handle.
typedef void *pwm_handle_t;

/****** PWM specific error codes *****/
typedef enum {
    EDRV_PWM_MODE  = (DRV_ERROR_SPECIFIC + 1),     ///< Specified Mode not supported
} csi_pwm_error_e;


/**
  \brief       Initialize PWM Interface. 1. Initializes the resources needed for the PWM interface 2.registers event callback function
  \param[in]   idx pwm idx
  \return      handle pwm handle to operate.
*/
pwm_handle_t csi_pwm_initialize(uint32_t idx);

/**
  \brief       De-initialize PWM Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle pwm handle to operate.
*/
void csi_pwm_uninitialize(pwm_handle_t handle);
/**
  \brief       control pwm power.
  \param[in]   handle  pwm handle to operate.
  \param[in]   state   power state.\ref csi_power_stat_e.
  \return      error code
*/
int32_t csi_pwm_power_control(pwm_handle_t handle, csi_power_stat_e state);

/**
  \brief       config pwm mode.
  \param[in]   handle           pwm handle to operate.
  \param[in]   channel          chnnel num.
  \param[in]   period_us        the PWM period in us
  \param[in]   pulse_width_us   the PMW pulse width in us
  \return      error code
*/
int32_t csi_pwm_config(pwm_handle_t handle,
                       uint8_t channel,
                       uint32_t period_us,
                       uint32_t pulse_width_us);

/**
  \brief       start generate pwm signal.
  \param[in]   handle   pwm handle to operate.
  \param[in]   channel  chnnel num.
*/
void csi_pwm_start(pwm_handle_t handle, uint8_t channel);

/**
  \brief       Stop generate pwm signal.
  \param[in]   handle   pwm handle to operate.
  \param[in]   channel  chnnel num.
*/
void csi_pwm_stop(pwm_handle_t handle, uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_PWM_H_ */
