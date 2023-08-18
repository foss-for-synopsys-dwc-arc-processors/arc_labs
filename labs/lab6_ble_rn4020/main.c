/* ------------------------------------------
 * Copyright (c) 2018, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */

#include "embARC.h"
#include "embARC_debug.h"

#include "board.h"
#include "device/ip_hal/dev_uart.h"
#include "rn4020.h"

#define RN4020_PRV_SERV_HIGH_UUID  0x1122334455667788
#define RN4020_PRV_SERV_LOW_UUID   0x9900AABBCCDDEEFF
#define RN4020_PRV_CHAR_HIGH_UUID  0x0102030405060708
#define RN4020_PRV_CHAR_LOW_UUID   0x09000A0B0C0D0E0F

int32_t rn4020_set_prv_uuid(RN4020_DEF_PTR rn4020, uint64_t high_uuid, uint64_t low_uuid)
{
    uint8_t i;
    uint8_t uuid_data[16];

    for(i = 0; i < 16; i++) 
    {
        if(i < 8) uuid_data[i] = (high_uuid >> ((7-i) << 3)) & 0xff;
        else uuid_data[i] = (low_uuid >> ((15-i) << 3)) & 0xff;
    }

    return rn4020_add_prv_service(rn4020, uuid_data);

}

int32_t rn4020_set_prv_char(RN4020_DEF_PTR rn4020, uint64_t high_uuid, uint64_t low_uuid, 
                            uint8_t property, uint8_t size, uint8_t security)
{
    uint8_t i;
    uint8_t uuid_data[16];

    for(i = 0; i < 16; i++) 
    {
        if(i < 8) uuid_data[i] = (high_uuid >> ((7-i) << 3)) & 0xff;
        else uuid_data[i] = (low_uuid >> ((15-i) << 3)) & 0xff;
    }

    return rn4020_add_prv_char(rn4020, uuid_data, property, size, security);

}

int main(void)
{

	uint32_t battery = 100;

	RN4020_DEFINE(rn4020_ble, DFSS_UART_3_ID, DFSS_GPIO_4B0_ID, 2, DFSS_GPIO_4B0_ID, 1, DFSS_GPIO_4B0_ID, 3);

	EMBARC_PRINTF("rn4020 test application\r\n");

	rn4020_setup(rn4020_ble);
	rn4020_reset_to_factory(rn4020_ble);

    /* Set device Name */
	rn4020_set_dev_name(rn4020_ble, "IoT DK"); 

    /* Set device services */
	rn4020_set_services(rn4020_ble, RN4020_SERVICE_DEVICE_INFORMATION |
		                            RN4020_SERVICE_BATTERY |
	                                RN4020_SERVICE_USER_DEFINED);

	rn4020_set_features(rn4020_ble, RN4020_FEATURE_SERVER_ONLY);
    rn4020_clear_private(rn4020_ble);
    
    /* Set private service UUID and private characteristic */
    rn4020_set_prv_uuid(rn4020_ble, RN4020_PRV_SERV_HIGH_UUID, RN4020_PRV_SERV_LOW_UUID);
    rn4020_set_prv_char(rn4020_ble, RN4020_PRV_CHAR_HIGH_UUID, RN4020_PRV_CHAR_LOW_UUID, 0x18, 0x06, RN4020_PRIVATE_CHAR_SEC_NONE);

    /* Reboot RN4020 to make changes effective */
    rn4020_reset(rn4020_ble);

    rn4020_refresh_handle_uuid_table(rn4020_ble);

    rn4020_advertise(rn4020_ble);


    while (1) {

		rn4020_battery_set_level(rn4020_ble, battery--);

		board_delay_ms(1000, 0);
		if (battery < 30) {
			battery = 100;
		}
	}
    
	return E_SYS;
}

