/* Copyright 2020 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Mock USB TC state machine */

#include "common.h"
#include "console.h"
#include "usb_tc_sm.h"
#include "mock/usb_tc_sm_mock.h"
#include "memory.h"

#ifndef CONFIG_COMMON_RUNTIME
#define cprints(format, args...)
#endif

struct mock_tc_port_t mock_tc_port[CONFIG_USB_PD_PORT_MAX_COUNT];

void mock_tc_port_reset(void)
{
	int port;

	for (port = 0 ; port < CONFIG_USB_PD_PORT_MAX_COUNT ; ++port) {
		mock_tc_port[port].rev = PD_REV30;
		mock_tc_port[port].pd_enable = 0;
		mock_tc_port[port].power_role = PD_ROLE_SINK;
		mock_tc_port[port].data_role = PD_ROLE_DISCONNECTED;
		mock_tc_port[port].msg_tx_id = 0;
		mock_tc_port[port].msg_rx_id = 0;
		mock_tc_port[port].sop = TCPC_TX_INVALID;
		mock_tc_port[port].lcl_rp = TYPEC_RP_RESERVED;
	}
}

enum pd_cable_plug tc_get_cable_plug(int port)
{
	return PD_PLUG_FROM_DFP_UFP;
}

uint8_t tc_get_pd_enabled(int port)
{
	return mock_tc_port[port].pd_enable;
}

void typec_select_src_collision_rp(int port, enum tcpc_rp_value rp)
{
	mock_tc_port[port].lcl_rp = rp;
}

int typec_update_cc(int port)
{
	return EC_SUCCESS;
}
