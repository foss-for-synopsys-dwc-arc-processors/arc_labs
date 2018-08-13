/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

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

#define MAX_COUNT 0xfffff

volatile static uint8_t timer_flag = 0;
volatile static uint8_t hits = 0;

volatile static uint8_t nesting_flag = 1;

/** arc timer 0 interrupt routine */
static void timer0_isr(void *ptr)
{
	timer_int_clear(TIMER_0);

	timer_flag = 0;

	board_delay_ms(10, 1);

	if(timer_flag)
	{
		EMBARC_PRINTF("Interrupt nesting!\r\n");
	}
	else
	{
		EMBARC_PRINTF("Interrupt\r\n");
	}

	hits++;
}

/** arc timer 1 interrupt routine */
static void timer1_isr(void *ptr)
{
	timer_int_clear(TIMER_1);

	timer_flag = 1;
}

/** main entry for testing arc fiq interrupt */
int main(void)
{
	timer_stop(TIMER_0);
	timer_stop(TIMER_1);

	int_disable(INTNO_TIMER0);
	int_disable(INTNO_TIMER1);

	int_handler_install(INTNO_TIMER0, timer0_isr);
	int_pri_set(INTNO_TIMER0, INT_PRI_MAX);

	int_handler_install(INTNO_TIMER1, timer1_isr);
	int_pri_set(INTNO_TIMER1, INT_PRI_MIN);

	EMBARC_PRINTF("\r\nThe test will start in 1s.\r\n");
	EMBARC_PRINTF("\r\n/******** TEST MODE START ********/\r\n\r\n");

	int_enable(INTNO_TIMER0);
	int_enable(INTNO_TIMER1);

	timer_start(TIMER_0, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT);
	timer_start(TIMER_1, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT/100);

	while(1)
	{
		if((hits >= 5)&&(nesting_flag == 1))
		{
			timer_stop(TIMER_0);
			timer_stop(TIMER_1);

			int_disable(INTNO_TIMER0);
			int_disable(INTNO_TIMER1);

			int_pri_set(INTNO_TIMER0, INT_PRI_MIN);
			int_pri_set(INTNO_TIMER1, INT_PRI_MAX);

			nesting_flag = 0;

			int_enable(INTNO_TIMER0);
			int_enable(INTNO_TIMER1);

			timer_start(TIMER_0, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT);
			timer_start(TIMER_1, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT/10);
		}
		else if((hits >= 10)&&(nesting_flag == 0))
		{
			timer_stop(TIMER_0);
			timer_stop(TIMER_1);

			int_disable(INTNO_TIMER0);
			int_disable(INTNO_TIMER1);

			int_pri_set(INTNO_TIMER0, INT_PRI_MAX);
			int_pri_set(INTNO_TIMER1, INT_PRI_MIN);

			hits = 0;
			nesting_flag = 1;

			int_enable(INTNO_TIMER0);
			int_enable(INTNO_TIMER1);

			timer_start(TIMER_0, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT);
			timer_start(TIMER_1, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT/100);
		}
	}
	return E_SYS;
}
