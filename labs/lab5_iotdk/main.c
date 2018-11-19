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

/* embARC HAL */
#include "embARC.h"
#include "embARC_debug.h"

#define IOTDK_LED_ID		DFSS_GPIO_4B2_ID
#define IOTDK_LED_PIN		0


/**
 * \brief	Test hardware board without any peripheral
 */
int main(void)
{
	DEV_GPIO_PTR gpio_led;

	io_arduino_config(ARDUINO_PIN_0, ARDUINO_GPIO, IO_PINMUX_ENABLE);

	gpio_led = gpio_get_dev(IOTDK_LED_ID);
	if (gpio_led->gpio_open((1 << IOTDK_LED_PIN)) == E_OPNED)
	{
		gpio_led->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT,
								(void *)(1 << IOTDK_LED_PIN));
	}

	while (1)
	{
		gpio_led->gpio_write(1, 1 << IOTDK_LED_PIN);
		board_delay_ms(10, 1);
		gpio_led->gpio_write(0, 1 << IOTDK_LED_PIN);
		board_delay_ms(190, 1);
	}

	return E_SYS;
}

/** @} */