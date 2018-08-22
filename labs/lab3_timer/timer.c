#include "embARC.h"
#include "embARC_debug.h"

#include "arc_timer.h"
#include "arc.h"
#include "arc_builtin.h"

#define BOARD_CPU_CLOCK			CLK_CPU
#define MAX_COUNT 0x0fffffff
/** main entry for testing arc timer**/
int main(void)
{

	/*Check the timer configuration information through the Timer BCR register.*/
	uint32_t bcr = _arc_aux_read(AUX_BCR_TIMERS);
	int timer0_flag = (bcr >> 8) & 1;
	int timer1_flag = (bcr >> 9) & 1;
	int RTC_flag = (bcr >> 10) & 1;
	if (timer0_flag) {
		EMBARC_PRINTF("Does this timer0 exist?  YES\r\n");
		/*Read auxiliary register configuration information*/
		EMBARC_PRINTF("timer0's operating mode:0x%08x\r\n",_arc_aux_read(AUX_TIMER0_CTRL));
		EMBARC_PRINTF("timer0's limit value :0x%08x\r\n",_arc_aux_read(AUX_TIMER0_LIMIT));
		EMBARC_PRINTF("timer0's current cnt_number:0x%08x\r\n",_arc_aux_read(AUX_TIMER0_CNT));
	} else {
		EMBARC_PRINTF("\r\nDoes this timer0 exist?  NO\r\n");
    }

    if (timer1_flag) {
		EMBARC_PRINTF("\r\nDoes this timer1 exist?  YES\r\n");
		/*Read auxiliary register configuration information*/
		EMBARC_PRINTF("timer1's operating mode:0x%08x\r\n",_arc_aux_read(AUX_TIMER1_CTRL));
		EMBARC_PRINTF("timer1's limit value :0x%08x\r\n",_arc_aux_read(AUX_TIMER1_LIMIT));
		EMBARC_PRINTF("timer1's current cnt_number:0x%08x\r\n",_arc_aux_read(AUX_TIMER1_CNT));
	} else {
		EMBARC_PRINTF("\r\nDoes this timer1 exist?  NO\r\n");
    }

    if (RTC_flag) {
		EMBARC_PRINTF("\r\nDoes this RTC_timer exist?  YES\r\n");
		/*Read auxiliary register configuration information*/
		EMBARC_PRINTF("RTC_timer's operating mode:0x%08x\r\n",_arc_aux_read(AUX_RTC_CTRL));
		EMBARC_PRINTF("timer1's current tick:0x%08x\r\n",_arc_aux_read(AUX_RTC_LOW));
	} else {
		EMBARC_PRINTF("\r\nDoes this RTC_timer exist?   NO\r\n");
    }


    /*Configure the timer through auxiliary registers*/
    if (timer0_flag) {
    	/* Stop it first since it might be enabled before */
    	_arc_aux_write(AUX_TIMER0_CTRL, 0);
		_arc_aux_write(AUX_TIMER0_LIMIT,0);
		_arc_aux_write(AUX_TIMER0_CNT, 0);
		/*This is a example about timer0's timer function.*/
		uint32_t mode = TIMER_CTRL_NH;/*Timing without triggering interruption.*/
		uint32_t val = MAX_COUNT;
		_arc_aux_write(AUX_TIMER0_CNT, 0);
		_arc_aux_write(AUX_TIMER0_LIMIT, val);
        /*start the specific timer*/
		_arc_aux_write(AUX_TIMER0_CTRL, mode);
		uint32_t start_cnt = _arc_aux_read(AUX_TIMER0_CNT);
        EMBARC_PRINTF("\r\nThe start_cnt number is:%d",start_cnt);

        EMBARC_PRINTF("\r\n/******** TEST MODE START ********/\r\n");
	    EMBARC_PRINTF("\r\nThis is TEST CODE.\r\n");
	    EMBARC_PRINTF("\r\nThis is TEST CODE.\r\n");
	    EMBARC_PRINTF("\r\nThis is TEST CODE.\r\n");
	    board_delay_ms(100, 1);
	    EMBARC_PRINTF("\r\n/******** TEST MODE END ********/\r\n");

        uint32_t end_cnt = _arc_aux_read(AUX_TIMER0_CNT);
        EMBARC_PRINTF("The end_cnt number is:%d\r\n", end_cnt);
        uint32_t time = (end_cnt-start_cnt)/(BOARD_CPU_CLOCK/1000);
        EMBARC_PRINTF("\r\nTotal time of TEST CODE BLOCK operation:%d\r\n",time);
    } else {
		EMBARC_PRINTF("timer 0 is not present\r\n");
    }
	while(1);
	return E_SYS;
}
