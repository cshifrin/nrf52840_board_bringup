/**
 * Copyright (c) 2016 - 2021 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef MAC_MLME_RESET_H_INCLUDED
#define MAC_MLME_RESET_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "mac_common.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC MLME Reset module declares the MAC Reset primitives and necessary types
 * according to the MAC specification.
 *
 * @defgroup mac_reset MAC MLME Reset API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME Reset API.
 * @details The MAC Reset module declares MLME Reset primitives and necessary types according to
 * the MAC specification. More specifically, MLME Reset request aka mlme_reset_req(), and MLME
 * Reset confirm callback typedef aka mlme_reset_conf_cb_t primitives are declared.
 */

/**@brief   MLME-Reset.confirm
 *
 * @details The MLME-Reset.confirm primitive reports the results of a request
 * to reset MAC layer of the device.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.9.2
 */
typedef struct
{
    mac_status_t    status;                /**< Status of operation. */
} mlme_reset_conf_t;

/**@brief   MLME-RESET.request
 *
 * @details The MLME-RESET.request primitive allows the next
 * higher layer to request that the MLME performs a reset operation.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.9.1
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t  service;

    /** Confirm to this request. */
    mlme_reset_conf_t   confirm;

    bool                set_default_pib;   /**< Set the default PIB. */
} mlme_reset_req_t;


/**
 * @brief   MLME-RESET confirm callback
 *
 * @details The MLME-RESET.confirm primitive is generated by the MLME and
 * issued to its next higher layer in response to an MLME-RESET.request primitive and
 * following the receipt of the PLME-SET-TRXSTATE.confirm primitive.
 *
 * @param  reset status (@c MAC_SUCCESS only).
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.9.2
 */
typedef void (* mlme_reset_conf_cb_t)(mlme_reset_conf_t *);


/**
 * @brief   MLME-RESET request
 *
 * @details The MLME-RESET.request primitive is generated by the next higher layer and
 * issued to the MLME to request a reset of the MAC sublayer to its initial conditions.
 * The MLME-RESET.request primitive is issued prior to the use of the MLME-START.request
 * or the MLME-ASSOCIATE.request primitives.
 *
 * @param[in]  req pointer to MCPS-RESET.request structure.
 * @param[in]  conf_cb pointer to user callback.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.9.1
 */
void mlme_reset_req(mlme_reset_req_t * req, mlme_reset_conf_cb_t conf_cb);

/** @} */

#endif // MAC_MLME_RESET_H_INCLUDED
