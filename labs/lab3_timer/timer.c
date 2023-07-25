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

#include "arc/arc_timer.h"
#include "arc/arc.h"
#include "arc/arc_builtin.h"

#define BOARD_CPU_CLOCK			CLK_CPU
#define MAX_COUNT 0x0fffffff
/** main entry for testing arc timer**/
int main(void)
{

	/*Check the timer configuration information through the Timer BCR register.*/
	uint32_t bcr = arc_aux_read(AUX_BCR_TIMERS);
	int timer0_flag = (bcr >> 8) & 1;
	int timer1_flag = (bcr >> 9) & 1;
	int RTC_flag = (bcr >> 10) & 1;
	if (timer0_flag) {
		EMBARC_PRINTF("Does this timer0 exist?  YES\r\n");
		/*Read auxiliary register configuration information*/
		EMBARC_PRINTF("timer0's operating mode:0x%08x\r\n",arc_aux_read(AUX_TIMER0_CTRL));
		EMBARC_PRINTF("timer0's limit value :0x%08x\r\n",arc_aux_read(AUX_TIMER0_LIMIT));
		EMBARC_PRINTF("timer0's current cnt_number:0x%08x\r\n",arc_aux_read(AUX_TIMER0_CNT));
	} else {
		EMBARC_PRINTF("\r\nDoes this timer0 exist?  NO\r\n");
	}

	if (timer1_flag) {
		EMBARC_PRINTF("\r\nDoes this timer1 exist?  YES\r\n");
		/*Read auxiliary register configuration information*/
		EMBARC_PRINTF("timer1's operating mode:0x%08x\r\n",arc_aux_read(AUX_TIMER1_CTRL));
		EMBARC_PRINTF("timer1's limit value :0x%08x\r\n",arc_aux_read(AUX_TIMER1_LIMIT));
		EMBARC_PRINTF("timer1's current cnt_number:0x%08x\r\n",arc_aux_read(AUX_TIMER1_CNT));
	} else {
		EMBARC_PRINTF("\r\nDoes this timer1 exist?  NO\r\n");
	}

	if (RTC_flag) {
		EMBARC_PRINTF("\r\nDoes this RTC_timer exist?  YES\r\n");
		/*Read auxiliary register configuration information*/
		EMBARC_PRINTF("RTC_timer's operating mode:0x%08x\r\n",arc_aux_read(AUX_RTC_CTRL));
		EMBARC_PRINTF("timer1's current tick:0x%08x\r\n",arc_aux_read(AUX_RTC_LOW));
	} else {
		EMBARC_PRINTF("\r\nDoes this RTC_timer exist?   NO\r\n");
	}

	/*Configure the timer through auxiliary registers*/
	if (timer0_flag) {
		/* Stop it first since it might be enabled before */
		arc_aux_write(AUX_TIMER0_CTRL, 0);
		arc_aux_write(AUX_TIMER0_LIMIT,0);
		arc_aux_write(AUX_TIMER0_CNT, 0);
		/*This is a example about timer0's timer function.*/
		uint32_t mode = TIMER_CTRL_NH;/*Timing without triggering interruption.*/
		uint32_t val = MAX_COUNT;
		arc_aux_write(AUX_TIMER0_CNT, 0);
		arc_aux_write(AUX_TIMER0_LIMIT, val);
		/*start the specific timer*/
		arc_aux_write(AUX_TIMER0_CTRL, mode);
		uint32_t start_cnt = arc_aux_read(AUX_TIMER0_CNT);
		EMBARC_PRINTF("\r\nThe start_cnt number is:%d",start_cnt);

		EMBARC_PRINTF("\r\n/******** TEST MODE START ********/\r\n");
	    	EMBARC_PRINTF("\r\nThis is TEST CODE.\r\n");
	   	EMBARC_PRINTF("\r\nThis is TEST CODE.\r\n");
	   	EMBARC_PRINTF("\r\nThis is TEST CODE.\r\n");
	    	board_delay_ms(100, 1);
	    	EMBARC_PRINTF("\r\n/******** TEST MODE END ********/\r\n");

		uint32_t end_cnt = arc_aux_read(AUX_TIMER0_CNT);
		EMBARC_PRINTF("The end_cnt number is:%d\r\n", end_cnt);
		uint32_t time = (end_cnt-start_cnt)/(BOARD_CPU_CLOCK/1000);
		EMBARC_PRINTF("\r\nTotal time of TEST CODE BLOCK operation:%d\r\n",time);
	} else {
		EMBARC_PRINTF("timer 0 is not present\r\n");
	}

	return E_SYS;
}
