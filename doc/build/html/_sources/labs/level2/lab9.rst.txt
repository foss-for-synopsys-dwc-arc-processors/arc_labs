.. _lab9:

How to use FreeRTOS
###################

Purpose
=======
- To learn how to implement tasks in FreeRTOS operating system
- To learn how to register tasks in FreeRTOS
- To get familiar with inter-task communication of FreeRTOS

Equipment
=========
The following hardware and software tools are required:

* PC host
* ARC GNU toolchain/MetaWare Development Toolkit
* ARC board (EM Starter kit/IoT Development Kit)
* |embarc| package
* ``embarc_osp/labs/lab9_freertos``

Content
========
This lab utilizes FreeRTOS v9.0.0, and will create 3 tasks based on embARC_osp. You should apply inter-task communicating methods such as semaphore and message queue in order to get running LEDs result. We should go though basic functions of FreeRTOS first.

Principles
==========

Background
----------
A Real Time Operating System (RTOS) is an operating system intended to serve real-time applications that process data in limited time as it comes in. Being within time bound and highly reliable are two important characters of RTOS.

As resources becoming abundant for modern micro processors, the cost to run RTOS is become increasingly neglectable. RTOS also provides event-driven mode for better utilization of CPU with efficiency. Among RTOSs for micro processors, FreeRTOS stands out as a free for use, opensourced RTOS with complete documents. These are the reasons of why we choose to learn FreeRTOS in this lab.

Design
------
This lab implements a running LED light with 3 tasks on FreeRTOS. Despite using 3 tasks is an overkill for a running LED, but it's beneficial for the understanding of FreeRTOS itself and inter-task communication as well.

The flow chat of the program is shown below:

.. image:: /img/lab9_program_flow_chart.png
    :alt: program flow chart

Realization
-----------
The code of system is shown below, including various Initialization and task time delay.

.. code-block:: c

	#include "embARC.h"
	#include "embARC_debug.h"
	#include <stdlib.h>

	static void task1(void *par);
	static void task2(void *par);
	static void task3(void *par);

	#define TSK_PRIOR_1		(configMAX_PRIORITIES-1)
	#define TSK_PRIOR_2		(configMAX_PRIORITIES-2)
	#define TSK_PRIOR_3		(configMAX_PRIORITIES-3)

	// Semaphores
	static SemaphoreHandle_t sem1_id;

	// Queues
	static QueueHandle_t dtq1_id;

	// Task IDs
	static TaskHandle_t task1_handle = NULL;
	static TaskHandle_t task2_handle = NULL;
	static TaskHandle_t task3_handle = NULL;

	int main(void)
	{
		vTaskSuspendAll();

		// Create Tasks
		if (xTaskCreate(task1, "task1", 128, (void *)1, TSK_PRIOR_1, &task1_handle)	!= pdPASS){
			/*!< FreeRTOS xTaskCreate() API function */
			EMBARC_PRINTF("Create task1 Failed\r\n");
			return -1;
		} else {
			EMBARC_PRINTF("Create task1 Successfully\r\n");
		}

		if (xTaskCreate(task2, "task2", 128, (void *)2, TSK_PRIOR_2, &task2_handle)	!= pdPASS){
			/*!< FreeRTOS xTaskCreate() API function */
			EMBARC_PRINTF("Create task2 Failed\r\n");
			return -1;
		} else {
			EMBARC_PRINTF("Create task2 Successfully\r\n");
		}

		if (xTaskCreate(task3, "task3", 128, (void *)3, TSK_PRIOR_3, &task3_handle)	!= pdPASS){
			/*!< FreeRTOS xTaskCreate() API function */
			EMBARC_PRINTF("Create task3 Failed\r\n");
			return -1;
		} else {
			EMBARC_PRINTF("Create task3 Successfully\r\n");
		}

		// Create Semaphores
		sem1_id = xSemaphoreCreateBinary();
		xSemaphoreGive(sem1_id);

		// Create Queues
		dtq1_id = xQueueCreate(8, sizeof(uint32_t));

		xTaskResumeAll();
		vTaskSuspend(NULL);

		return 0;
	}

	static void task1(void *par)
	{
		uint32_t led_val = 0;

		static portTickType xLastWakeTime;
		const portTickType xFrequency = pdMS_TO_TICKS(10);

		// Use current time to init xLastWakeTime, mind the difference with vTaskDelay()
		xLastWakeTime = xTaskGetTickCount();

		while (1) {
			/* call Freertos system function for 10ms delay */
			vTaskDelayUntil( &xLastWakeTime,xFrequency );

			//####Insert code here###
		}
	}

	static void task2(void *par)
	{
		uint32_t led_val = 0x0001;

		static portTickType xLastWakeTime;
		const portTickType xFrequency = pdMS_TO_TICKS(100);

		// Use current time to init xLastWakeTime, mind the difference with vTaskDelay()
		xLastWakeTime = xTaskGetTickCount();

		while (1) {
			/* call Freertos system function for 100ms delay */
			vTaskDelayUntil( &xLastWakeTime,xFrequency );

			//####Insert code here###
		}
	}

	static void task3(void *par)
	{
		uint32_t led_val = 0;

		static portTickType xLastWakeTime;
		const portTickType xFrequency = pdMS_TO_TICKS(200);

		// Use current time to init xLastWakeTime, mind the difference with vTaskDelay()
		xLastWakeTime = xTaskGetTickCount();

		while (1) {
			/* call Freertos system function for 100ms delay */
			vTaskDelayUntil( &xLastWakeTime,xFrequency );

			//####Insert code here###
		}
	}


Steps
=====

Build and run the incompleted code
----------------------------------
the code is at ``embarc_osp/labs/lab9_freertos``, use an uart terminal console and run the code, you will see a message from program like the one shown below:

.. code-block:: console

	embARC Build Time: Mar  9 2018, 17:57:50
	Compiler Version: Metaware, 4.2.1 Compatible Clang 4.0.1 (branches/release_40)
	Create task1 Successfully
	Create task2 Successfully
	Create task3 Successfully

This message implys that three tasks are working correctly.

Implement task 3
----------------
It is required for task 3 to retrieve new value from the queue and assign the value to led_val. The LED controls are already implemented in previous labs, so the only new function to learn is ``xQueueReceive()``. This is a FreeRTOS API to pop and read an item from queue. Please take reference from FreeRTOS documents and complete the code for this task. (An example is in 'complete' folder)

Implement task 1
----------------
It is required for task 1 to check if value from queue is legal. If not, a reset signal is needed to be sent.

Two new functions might be helpful for this task: ``xSemaphoreGive()`` for release a signal and ``xQueuePeek()`` for read item but not pop from a queue. Please take reference from FreeRTOS documents and complete the code for this task. (An example is in 'complete' folder)

Do notice the difference between ``xQueueReceive()`` and ``xQueuePeek()``.

Implement task 2
----------------
There are two different works for task 2 to complete: to shift led_val and queue it, and to reset both led_val and queue when illegal led_val is detected.

Three functions can be helpful: ``xQueueSend()``, ``xSemaphoreTake()``, ``xQueueReset()``. Please take reference from FreeRTOS documents and complete the code for this task. (An example is in 'complete' folder)

Build and run the completed code
--------------------------------
BUild the completed program and debug it to fulfill all requirements. (8-digit running LEDs are used in example code)

Exercises
=========
The problem of philosophers having meal:

Five philosophers sitting at a round dining table. Suppose they are either thinking or eating, but they can't do these two things at same time. So each time when they are having food, they stop thinking and vice versa. There are five forks on the table for eating noddle, each fork is placed between two adjacent philosophers  It's hard to eat noddle with one fork, so all philosophers need two forks in order to eat.

Please write a program with proper console output to simulate this process.
