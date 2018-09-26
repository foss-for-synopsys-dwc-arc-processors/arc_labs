.. _lab4:

ARC features: interrupts
########################

Purpose
========
- To introduce the interrupt module in the ARC embedded processor
- To demonstrate how to use the interrupt and timer APIs already defined in the embARC processor in the program

Equipment
==========
The following hardware and software tools are required:

* PC host
* ARC GNU toolchain/MetaWare Development Toolkit
* ARC board (EM Starter kit/IoT Development Kit)
* embARC OSP packag
* ``labs/lab4_interrupt``

Content
=========
This lab and lab 3 are both introductions to the internal characteristics of the ARC processor. Lab 3 introduces the timer. This lab aims to introduce the interrupt of embARC through **labs\\lab4_interrupt** in the embARC OSP package. The two routines give you a preliminary understanding of the ARC interrupt resources.

Principles
===========
The ARC EM processor uses vector interrupts to handle interrupt events. When the interrupt occurs, the processor stops the execution of the current program, and queries the corresponding interrupt vector in the predefined interrupt vector table according to the current interrupt type. In other words, to find the entry address of the interrupt service program. Then program jumps to the address to execute the interrupt service routine. After the execution is completed, return to the interrupted program and complete the response of the interrupt event.

In embARC OSP, we use the ``int_handler_install()`` function to bind our interrupt function name to the interrupt vector of the corresponding interrupt, and then we can achieve the above functions.

Steps
======

Open and browse lab one
------------------------

Go to the embarc_osp\\example\\Lab\\interrupt directory, where there are two folders, lab_4_1 and lab_4_2.

The lab_4_1 is more fundamental compared to lab_4_2. So we first enter folder lab_4_1, in which the precise timing function is implemented through the timer interrupt.

Open main.c and browse the entire program.

.. code-block:: c

	#include "embARC.h"
	#include "embARC_debug.h"

	#define COUNT (BOARD_CPU_CLOCK/1000)

	volatile static int t0 = 0;
	volatile static int second = 0;

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
	 while(t0<ms);
	}

	/** main entry for testing arc fiq interrupt */
	int main(void)
	{
	  int_disable(INTNO_TIMER0);
	  timer_stop(TIMER_0);

	  int_handler_install(INTNO_TIMER0, timer0_isr);
	  int_pri_set(INTNO_TIMER0, INT_PRI_MIN);

	  EMBARC_PRINTF("\r\nThis is a example about timer interrupt.\r\n");
	  EMBARC_PRINTF("\r\n/******** TEST MODE START ********/\r\n\r\n");

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

Sub-module analysis lab one code
---------------------------------

The code can be roughly divided into three parts: interrupt service function, main function, and delay function.

Let's analyze each one below:

- Interrupt service function:

.. code-block:: c

	static void timer0_isr(void *ptr)
	{
	timer_int_clear(TIMER_0);
	t0++;
	}

This code is a standard example of an interrupt service function, enters the service function, clears the interrupt flag bit, and then performs the processing that needs to be done in the interrupt service function. Other interrupt service functions can also be written using this template.

In this function, we incremented the count variable t0 by one.

- Main function

.. code-block:: c

	int main(void)
	{
	  int_disable(INTNO_TIMER0);
	  timer_stop(TIMER_0);

	  int_handler_install(INTNO_TIMER0, timer0_isr);
	  int_pri_set(INTNO_TIMER0, INT_PRI_MIN);

	  EMBARC_PRINTF("\r\nThis is a example about timer interrupt.\r\n");
	  EMBARC_PRINTF("\r\n/******** TEST MODE START ********/\r\n\r\n");

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

The ``EMBARC_PRINTF`` function in this code is only used to send information to the computer, which can be ignored during analysis.

This code is divided into two parts: initialization and looping.

In the initialization section, we configured the timer and timer interrupts.

Unlike Lab 3, this code uses the embARC OSP API to implement it. In fact, in essence, these two methods are the same. The API just encapsulates the read and write operations of the auxiliary registers for convenience.

**First**, in order to configure **Timer0** and its interrupts, we need to turn them off first. This work is done by the functions ``int_disable`` and ``timer_stop``.

**Then** we configure the interrupt service function and priority for our interrupts. This work is done by the functions ``int_handler_install`` and ``int_pri_set``.

**Finally**, after the interrupt configuration is complete, we need to enable the **Timer0** and interrupts that we previously turned off. This work is done by the functions ``int_enable`` and ``timer_start``.
The implementation of the ``timer_start`` function is basically the same as the reading and writing of the auxiliary registers in our lab_3. Interested students can view them in the file arc_timer.c. One point to note in this step is the configuration of ``timer_limit`` (the last parameter of ``timer_start``). We need to configure the interrupt time to 1ms , so we need to do a simple calculation (the formula is the expression after COUNT).

In this example, the loop body only serves as an effect display. We call our own delay function in the loop body to print the time per second.

.. note::
    Since nSIM is only simulated by computer, there may be time inaccuracy when using this function. Interested students can use the EMSK to program the program in the development board. In this case, the time will be much higher than that in nSIM.

- Delay function

.. code-block:: c

	static void timer0_isr(void *ptr)
	{
	t0 = 0;
	while(t0<ms);
	}

This code is very simple and the idea is clear. When we enter the function, we clear the global variable t0. Since we have set the interrupt interval to 1ms in the above timer_start, we can think that every time t0 is incremented, the time has passed 1ms.

Then, we wait through the while(t0<ms) sentence, so that we can get the full ms delay with higher precision.

Lab one Labal phenomenon
-------------------------

After the lab one program is successfully downloaded, the serial output is as follows:

.. code-block:: console

    embARC Build Time: Mar 16 2018, 09:58:46
    Compiler Version: Metaware, 4.2.1 Compatible Clang 4.0.1

    This is an example about timer interrupt
    /********TEST MODE START********/
    0s

    1s

    2s

    3s

    4s

    5s

    ...

Open and browse the lab two
----------------------------

We then enter lab_4_2, which mainly shows the working state of priority and interrupt nesting.

Open main.c and browse through the entire program.

.. code-block:: c

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
			timer_start(TIMER_1, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT/100);
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

Sub-module analysis lab two code
---------------------------------

Lab two seems complicated, but it is very simple. The code for Lab two only needs to be divided into two parts: the interrupt service function and the main function.

- Interrupt service function

.. code-block:: c

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

    static void timer1_isr(void *ptr)
    {
	timer_int_clear(TIMER_1);

	timer_flag = 1;
    }

First, in order to analyze the code, we first ignore the extraneous parts (such as EMBARC_PRINTF, delay and hits in if).

In this case, we can find that for the interrupt service function timer0_isr, it is impossible to have the timer_flag of 1 only when it is itself. The only way to do this is to have another higher priority interrupt between timer_flag=0 and if statement set it.

Following this line of thought, let's look at timer1_isr again, and sure enough.

Regarding EMBARC_PRINTF, it is used to indicate the status.

Regarding the delay, its role is to lengthen this period of time, making nesting more likely.

Regarding hits, it will be mentioned in the main function module.

- main function

.. code-block:: c

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
			timer_start(TIMER_1, TIMER_CTRL_IE | TIMER_CTRL_NH, MAX_COUNT/100);
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

The main function looks very long, but in fact there is a considerable part of it that is repetitive (we can also build a small function to make the code look more concise).

In the first lab, we have already discussed the configuration of the timer and the creation of the interrupt, we will not repeat them here.

The main function is simple: when the interrupt of timer0 occurs 5 times, change the priority relationship of the two interrupts. The hits mentioned earlier are count variables to assist in the above functions.

Lab two Labal phenomenon
-------------------------

The labal phenomenon of Lab two is shown in the figure.

"Interrupt nesting!" indicates that interrupt nesting has occurred, and "Interrupt" indicates that it has not occurred.

For a better understanding, let's go back and look at the priority settings in the main function.

It is easy to see that when the timer0 interrupt priority is low (INT_PRI_MAX is low priority, this setting is contrary to most people's intuition), the timer1 interrupt can be embedded therein; when the timer0 interrupt priority is high, the timer1 interrupt cannot be embedded.

To summarize, high-priority interrupts can interrupt low-priority interrupts, and low-priority interrupts can be embedded by high-priority interrupts. The Main function can be understood as the lowest priority interrupt.

.. code-block:: console

    embARC Build Time: Mar 16 2018, 09:58:46
    Compiler Version: Metaware, 4.2.1 Compatible Clang 4.0.1

    This test will start in 1s.

    /********TEST MODE START********/

    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt
    Interrupt
    Interrupt
    Interrupt
    Interrupt
    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt  nesting!
    Interrupt
    Interrupt
    Interrupt

Exercises
==========

Try using an interrupt other than a timer to write a small program. (For example, try to implement a button controled LED using GPIO interrupt)

