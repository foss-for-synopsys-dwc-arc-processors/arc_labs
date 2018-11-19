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

#define COUNT BOARD_CPU_CLOCK/1000

volatile static int t0 = 0;
volatile static int second = 1;

/** arc timer 0 interrupt routine */
static void timer0_isr(void *ptr)
{
	timer_int_clear(TIMER_0);
	t0++;
}

/** arc timer 0 interrupt delay */
void timer0_delay_ms(int ms)
{
	t0 = 0;
	while(t0 < ms);
}

/** main entry for testing arc fiq interrupt */
int main(void)
{
	int_disable(INTNO_TIMER0);
	timer_stop(TIMER_0);

	int_handler_install(INTNO_TIMER0, timer0_isr);
	int_pri_set(INTNO_TIMER0, INT_PRI_MIN);

	EMBARC_PRINTF("\r\nThis is a example about timer interrupt.\r\n");

	int_enable(INTNO_TIMER0);
	timer_start(TIMER_0, TIMER_CTRL_IE | TIMER_CTRL_NH, COUNT);

	while(1)
	{
		timer0_delay_ms(1000);
		EMBARC_PRINTF("\r\n %ds.\r\n",second);
		second ++;
	}
	return E_SYS;
}

