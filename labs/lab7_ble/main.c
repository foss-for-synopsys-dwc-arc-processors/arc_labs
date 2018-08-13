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
#include "dev_uart.h"
#include "hm1x.h"

#define MAX_COUNT 0xfffff

uint8_t isr_flag = 0;

void init_Ble_HM_10(HM1X_DEF_PTR obj, uint32_t baudrate, uint32_t mode, uint32_t type, uint32_t role)
{
	EMBARC_PRINTF("Init HM1X with baudrate %dbps\r\n", baudrate);
	hm1x_init(obj, baudrate);

	hm1x_flush(obj);

	while(hm1x_test_command(obj))
	{
		EMBARC_PRINTF("test command Failed\r\n");
	}
	EMBARC_PRINTF("test command Successfully\r\n");

	while(hm1x_restart(obj))
	{
		EMBARC_PRINTF("Restart Failed\r\n");
	}
	EMBARC_PRINTF("Restart Successfully\r\n");

	while(hm1x_set_mode(obj, mode))
	{
		EMBARC_PRINTF("SET MODE Failed\r\n");
	}
	EMBARC_PRINTF("SET MODE to %d\r\n", mode);

	while(hm1x_set_type(obj, type))
	{
		EMBARC_PRINTF("SET TYPE Failed\r\n");
	}
	EMBARC_PRINTF("SET TYPE to %d\r\n", type);

	while(hm1x_set_role(obj, role))
	{
		EMBARC_PRINTF("SET ROLE Failed\r\n");
	}
	EMBARC_PRINTF("SET ROLE to %d\r\n", role);
}

static void timer0_isr(void *ptr)
{
	static uint32_t led_val = 1;
    /* 将未执行中断标志位清零 */
	timer_int_clear(TIMER_0);

	if (isr_flag == 1)
	{
		if(led_val >= 0x0100)
		{
			led_val = 0x0001;
		}
		else
		{
			led_val <<= 1;
		}

		led_write(led_val, BOARD_LED_MASK);
	}
}

void init_Run_Timer(void)
{
	int_disable(INTNO_TIMER0);
	timer_stop(TIMER_0);

	int_handler_install(INTNO_TIMER0, timer0_isr);
	int_pri_set(INTNO_TIMER0, INT_PRI_MIN);

	int_enable(INTNO_TIMER0);
	timer_start(0, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT);
}

uint8_t compare_chars(uint8_t* buf, uint8_t* cmd, uint8_t num)
{
	uint8_t i = 0;
	uint8_t cnt = 0;

	for (i = 0; i < num; ++i)
	{
		if(buf[i] == cmd[i])
		{
			cnt++;
		}
	}

	if(cnt == num)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void LED_ALL_FUN(void)
{
	isr_flag = 0;

	led_write(BOARD_LED_MASK, BOARD_LED_MASK);
}

void LED_OFF_FUN(void)
{
	isr_flag = 0;

	led_write(~BOARD_LED_MASK, BOARD_LED_MASK);
}

void LED_WRI_FUN(uint8_t* num_buf, uint8_t* num_cmd)
{
	uint8_t i = 0;
	uint8_t k = 0;
	uint32_t led_val = 0;

	isr_flag = 0;

	for(k = 0; k < 3; ++k)
	{
		for (i = 0; i < 16; ++i)
		{
			if(num_buf[k] == num_cmd[i])
			{
				led_val += i;
			}
		}
		led_val <<= 4;
	}
	led_val >>= 4;
	led_write(led_val, BOARD_LED_MASK);
}

void LED_RUN_FUN(void)
{
	isr_flag = 1;
}

void LED_RED_FUN(void)
{
	uint32_t led_val = 0;

	led_val = led_read(BOARD_LED_MASK);
	EMBARC_PRINTF("The Led is 0x0%x\r\n",led_val);
}

int main(void)
{
	uint8_t rcv_buf[20];
	int32_t rcv_cnt = 0;

	uint8_t cmd_buf[20];
	int32_t cmd_cnt = 0;

	uint8_t rcv_flag = 0;
	uint8_t pre_flag = 0;

	uint8_t LED_ALL_CMD[6] = {'L','E','D','A','L','L'};
	uint8_t LED_OFF_CMD[6] = {'L','E','D','O','F','F'};
	uint8_t LED_WRI_CMD[6] = {'L','E','D','W','R','I'};
	uint8_t LED_RUN_CMD[6] = {'L','E','D','R','U','N'};
	uint8_t LED_RED_CMD[6] = {'L','E','D','R','E','D'};

	uint8_t Num_CMD[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

	uint8_t	LED_ALL_FLAG = 0;
	uint8_t LED_OFF_FLAG = 0;
	uint8_t LED_WRI_FLAG = 0;
	uint8_t LED_RUN_FLAG = 0;
	uint8_t LED_RED_FLAG = 0;

	HM1X_DEFINE(hm1x, HM_1X_UART_ID);
	init_Ble_HM_10(hm1x, UART_BAUDRATE_9600, BLE_HM1X_MODE_0, BLE_HM1X_TYPE_0, BLE_HM1X_SLAVE_ROLE);
	init_Run_Timer();

	EMBARC_PRINTF("\r\n/*****Enter THE TEST MODE*****/\r\n");

	while (1)
	{
		LED_ALL_FLAG = 0;
		LED_OFF_FLAG = 0;
		LED_WRI_FLAG = 0;
		LED_RUN_FLAG = 0;
		LED_RED_FLAG = 0;

    	rcv_cnt = hm1x_read(hm1x, rcv_buf, sizeof(rcv_buf));
		rcv_buf[rcv_cnt] = '\0';

		if (rcv_cnt)
		{
			rcv_flag = 1;
		}
		else
		{
			rcv_flag = 0;
		}

		if(rcv_flag)
		{
			for (int i = 0; i < rcv_cnt; ++i)
			{
				cmd_buf[cmd_cnt + i] = rcv_buf[i];
			}
			cmd_cnt += rcv_cnt;
			//EMBARC_PRINTF("The count is %d\r\n", cmd_cnt);
		}

		if((rcv_flag == 0)&&(pre_flag == 1))
		{
			if(cmd_cnt == 6)
			{
				LED_ALL_FLAG = compare_chars(cmd_buf, LED_ALL_CMD, 6);
				LED_OFF_FLAG = compare_chars(cmd_buf, LED_OFF_CMD, 6);
				LED_RUN_FLAG = compare_chars(cmd_buf, LED_RUN_CMD, 6);
				LED_RED_FLAG = compare_chars(cmd_buf, LED_RED_CMD, 6);
			}
			else if(cmd_cnt == 9)
			{
				LED_WRI_FLAG = compare_chars(cmd_buf, LED_WRI_CMD, 6);
			}
			else
			{
				EMBARC_PRINTF("\r\nThe command is wrong. The count is %d\r\n", cmd_cnt);
			}

			cmd_buf[cmd_cnt] = '\r';
			cmd_buf[cmd_cnt+1] = '\n';
			cmd_buf[cmd_cnt+2] = '\0';
			hm1x_write(hm1x, cmd_buf, cmd_cnt+2);

			cmd_cnt = 0;
		}

		pre_flag = rcv_flag;
		board_delay_ms(10, 1);

		if(LED_ALL_FLAG)
		{
			EMBARC_PRINTF("\r\nLED_ALL_FUN\r\n");
			LED_ALL_FUN();
		}
		else if (LED_OFF_FLAG)
		{
			EMBARC_PRINTF("\r\nLED_OFF_FUN\r\n");
			LED_OFF_FUN();
		}
		else if (LED_WRI_FLAG)
		{
			EMBARC_PRINTF("\r\nLED_WRI_FUN\r\n");
			LED_WRI_FUN(cmd_buf+6, Num_CMD);
		}
		else if (LED_RUN_FLAG)
		{
			EMBARC_PRINTF("\r\nLED_RUN_FUN\r\n");
			LED_RUN_FUN();
		}
		else if (LED_RED_FLAG)
		{
			EMBARC_PRINTF("\r\nLED_RED_FUN\r\n");
			LED_RED_FUN();
		}

	}
	return E_SYS;
}

