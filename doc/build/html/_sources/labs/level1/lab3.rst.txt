.. _lab3:

ARC features: timer and auxiliary registers
###########################################

Purpose
=======
- To learn the timer resource of ARC EM processor
- To learn how to use the auxiliary registers to control the timer
- Read the count value of the timer, and implement a time clock by the timer

Equipment
=========
The following hardware and software tools are required:

* PC host
* ARC GNU toolchain/MetaWare Development Toolkit
* ARC board (EM Starter kit/IoT Development Kit)
* |embarc| package
* ``labs/lab3_timer``

Content
========
Read the auxiliary registers of ARC EM to get the version and  other setting information of the timer resource. As all the EM processors have **Timer0**, we use the **Timer0** in this lab, and write the auxiliary registers to initialize, start and stop the timer. By reading the count value of the timer, we can calculate the execution time of a code block with the count value and the clock frequency.

Principles
==========

Introduction of timer and auxiliary registers
----------------------------------------------
The timers in ARC EM processor

- Two 32-bits programmable timers **Timer0** and **Timer1**
- One 64-bits **RTC**\ (Real-Time Counter)

All the times are configurable, for example, there are four EM processor cores in **ARC EMSK1.1**, the configuration information are as follow.

=========== ===== =========== ===== ===========
 Timer       EM4   EM4_16CR    EM4   EM4_16CR
=========== ===== =========== ===== ===========
HAS_TIMER0    1       1         1        1
HAS_TIMER1    1       0         1        0
RTC_OPTION    0       0         0        0
=========== ===== =========== ===== ===========

The auxiliary register Timer BCR storaged the timer resource information of an EM processor core, the register address of **TIMER_BUILD** is *0x75*.

**TIMER_BUILD**

.. image:: /img/lab3_register_TIMER_BUILD.png
    :alt: register bit

As we know the timer resources the EM processor configured, we can get the timer's configuration information and control the timers by writing and reading the auxiliary register of that timer. For example, there are the related auxiliary registers of the **Timer0**.

==================== ========== ============ =======================
 Auxiliary Register   Name       Permission   Description
==================== ========== ============ =======================
0x21                  COUNT0     RW           Processor timer 0 count value
0x22                  CONTROL0   RW           Processor timer 0 control value
0x23                  LIMIT0     RW           Processor timer 0 limit value
==================== ========== ============ =======================

Program flow chart
------------------

.. image:: /img/lab3_program_flow_chart.png
    :alt: program flow chart

Steps
=====

Makefile configuration
----------------------

There are two ways to do the configuration.

**First**, configured by compile command, for example:

.. code-block:: console

	make BOARD=iotdk BD_VER=10 CUR_CORE=arcem9d -j4 TOOLCHAIN=gnu run

**Second**, configured by modifying the makefile. At here, the compile command will be very simple, for example:

.. code-block:: console

	make -j4 run

Open the folder ``embarc_osp/example/Lab/timer``, and open the ``makefile``, here is the default configuration.

.. code-block:: makefile

	# Application name
	APPL ?= lab3_timer

	##
	# Current Board And Core
	##
	BOARD ?= iotdk
	BD_VER ?= 10
	CUR_CORE ?= arcem9d

	##
	# Set toolchain
	##
	TOOLCHAIN ?= gnu

	#
	# root dir of embARC
	#
	EMBARC_ROOT = ../../..

	MID_SEL = common

	# application source dirs
	APPL_CSRC_DIR = .
	APPL_ASMSRC_DIR = .

	# application include dirs
	APPL_INC_DIR = .

- Reconfigure **BOARD** and **CUR_CORE**, in this lab, we use the launch board *iotdk*

.. code-block:: makefile

	##
	# Current Board And Core
	##
	BOARD ?= iotdk
	BD_VER ?= 10
	CUR_CORE ?= arcem9d

- Reconfigure **TOOLCHAIN**, select the toolchain *gnu* or *metaware* you used

.. code-block:: makefile

	##
	# Set toolchain
	##
	TOOLCHAIN ?= gnu

- Reconfigure **EMBARC_ROOT**, make sure the relative path between *embARC OSP* root folder and the *timer* folder is correct.

.. code-block:: makefile

	#
	# root dir of embARC
	#
	EMBARC_ROOT = ../../..

Main code
---------

Read auxiliary register BCR_BUILD
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
We can use the function ``_arc_aux_read()`` to read the auxiliary register for the timer resource information.

Read auxiliary register **TIMER_BUILD**. In the register **TIMER_BUILD** The lower 8 bits indicate the core version information, the bit 9 indicate the **Timer0**, the bit 10 indicate the **Timer1**, the bit 11 indicate the **RTC**. Here is the code:

.. code-block:: c

	uint32_t bcr = _arc_aux_read(AUX_BCR_TIMERS);
	int timer0_flag=(bcr >> 8) & 1;
	int timer1_flag=(bcr >> 9) & 1;
	int RTC_flag=(bcr >> 10) & 1;

Read timer related auxiliary registers, for example, the **Timer0**. Here is the code:

.. code-block:: c

	EMBARC_PRINTF("Does this timer0 exist?  YES\r\n");
	/*Read auxiliary register configuration information*/
	EMBARC_PRINTF("timer0's operating mode:0x%08x\r\n",_arc_aux_read(AUX_TIMER0_CTRL));
	EMBARC_PRINTF("timer0's limit value :0x%08x\r\n",_arc_aux_read(AUX_TIMER0_LIMIT));
	EMBARC_PRINTF("timer0's current cnt_number:0x%08x\r\n",_arc_aux_read(AUX_TIMER0_CNT));

Stop-Set-Start the Timer0
^^^^^^^^^^^^^^^^^^^^^^^^^
We can use the function ``_arc_aux_write()`` to write the auxiliary register.

To control the **Timer0** with the related auxiliary registers.

- **COUNT0**: write this register to set the initial value of the **Timer0**. It will increase from the set value at anytime you write this register.
- **CONTROL0**: write this register to update the control modes of the **Timer0**.
- **LIMIT0**: write this register to set the limit value of the **Timer0**, the limit value is the value after which an interrupt or a reset must be generated.

In this lab, we should stop timer before setting and starting it, the function ``timer_stop()`` is already encapsulated in embARC OSP, you can  use this function or directly write the register. And then set the timer work mode, enable interrupt or not and set the limit value. At last start the timer. Here is the code:

.. code-block:: c

	/* Stop it first since it might be enabled before */
	_arc_aux_write(AUX_TIMER0_CTRL, 0);
	_arc_aux_write(AUX_TIMER0_LIMIT,0);
	_arc_aux_write(AUX_TIMER0_CNT, 0);
	/* This is a example about timer0's timer function. */
	uint32_t mode = TIMER_CTRL_NH;/*Timing without triggering interruption.*/
	uint32_t val = MAX_COUNT;
	_arc_aux_write(AUX_TIMER0_CNT, 0);
	_arc_aux_write(AUX_TIMER0_LIMIT,val);
        /* start the specific timer */
	_arc_aux_write(AUX_TIMER0_CTRL,mode);

When the timer is running, we can read the count value of the timer,and calculate the execution time of a code block. Here is the code:

.. code-block:: c

    uint32_t start_cnt=_arc_aux_read(AUX_TIMER0_CNT);
    /**
     * code block
     */
    uint32_t end_cnt=_arc_aux_read(AUX_TIMER0_CNT);
    uint32_t time=(end_cnt-start_cnt)/(BOARD_CPU_CLOCK/1000);

Compile and debug
^^^^^^^^^^^^^^^^^
- Compile and download

Open ``cmd`` under the folder *example/Lab/timer*, input the compile command as follow:

.. code-block:: console

    make -j4 run

.. note::
    If your toolchain is meteware, you should use ``gmake``.
    If you don't use core configuration specified in makefile, you need to pass all the make options to trigger make command

- Output

.. code-block:: console

   -----------------------------------------------------------
	 ____                                _ ____
	|  _ \ _____      _____ _ __ ___  __| | __ ) _   _
	| |_) / _ \ \ /\ / / _ \ '__/ _ \/ _` |  _ \| | | |
	|  __/ (_) \ V  V /  __/ | |  __/ (_| | |_) | |_| |
	|_|   \___/ \_/\_/ \___|_|  \___|\__,_|____/ \__, |
	                                             |___/
	                     _       _    ____   ____
	       ___ _ __ ___ | |__   / \  |  _ \ / ___|
	      / _ \ '_ ` _ \| '_ \ / _ \ | |_) | |
	     |  __/ | | | | | |_) / ___ \|  _ <| |___
	      \___|_| |_| |_|_.__/_/   \_\_| \_\\____|
	------------------------------------------------------------

	embARC Build Time: Aug 22 2018, 15:32:54
	Compiler Version: Metaware, 4.2.1 Compatible Clang 4.0.1 (branches/release_40)
	Does this timer0 exist?  YES
	timer0's operating mode:0x00000003
	timer0's limit value :0x00023280
	timer0's current cnt_number:0x0000c236

	Does this timer1 exist?  YES
	timer1's operating mode:0x00000000
	timer1's limit value :0x00000000
	timer1's current cnt_number:0x00000000

	Does this RTC_timer exist?   NO

	The start_cnt number is:2
	/******** TEST MODE START ********/

	This is TEST CODE.

	This is TEST CODE.

	This is TEST CODE.

	/******** TEST MODE END ********/
	The end_cnt number is:16785931
	The board cpu clock is:144000000

	Total time of TEST CODE BLOCK operation:116

- Debug

Open ``cmd`` under the folder *example/Lab/timer*, input the command as follow:

.. code-block:: console

    make gui


.. image:: /img/lab3_debug_view_1.png
    :alt: debug view 1

.. image:: /img/lab3_debug_view_2.png
    :alt: debug view 2


The debug view will pop up automatically, we can watch the variables and registers.


Exercises
=========
In the debug view, observe and understand the contents of the interrupt vector table.

.. note::
     Click the Memory button in the debug view Debugger drop-down menu to see the contents of the memory in real time.
