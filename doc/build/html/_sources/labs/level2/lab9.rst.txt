.. _lab9:

How to use FreeRTOS
#####################

Purpose
=======
- To learn how to implement tasks in FreeRTOS operating system
- To learn how to register tasks in FreeRTOS
- To get familiar with inter-task communication of FreeRTOS

Equipment
=========
The following hardware and tools are required:

* PC host
* |arcgnu| / |mwdt|
* ARC board (|emsk| / |iotdk|)
* |embarc| package
* ``embarc_osp/arc_labs/labs/lab9_freertos``

Content
========
This lab utilizes FreeRTOS v9.0.0, and creates 3 tasks based on |embarc|. You should apply inter-task communicating methods such as semaphore and message queue in order to get running LEDs result. You should know the basic functions of FreeRTOS.

Principles
==========

Background
----------

Operating System is software that controls basic hardware and software resources and provides access to them as a service for applications. In this sense applications that are sued by users are said to be run on top of or inside operating system.

There are different kind of operating systems and many definitions of OSes depending on the available features. One of the main features of every OS is how it organizes several tasks (programs) to work together. Some OSes execute only one task at the time (these are called single-tasking) other allow multiple programs to work together (multi-tasking). Most common desktop operating systems are multi-tasking (Linux, Windows, etc.).

As processors on which programs are executed are sequential devices, technically only single program can be run at a time on a processor. However, multi-tasking does periodical switching between several tasks creating an illusion that these tasks work in parallel. The part of operating system that does this work is called scheduler. Scheduler is a routine that decides the order of execution of several tasks running on OS.

Depending on scheduler multi-tasking algorithm OSes are classified on real-time and non-real-time. In desktop operating systems (Linux, Windows) the usual approach of scheduler is to try to distribute processor time evenly between running application, so that each uses fair amount of resources. However, this approach has significant drawback which is unpredictable times when specific task will be running. On the other hand, some applications (especially embedded) are time constrained and thus require deterministic execution of tasks. For example, if embedded system is controlling industrial machinery then software application is controlling some operation in the machine, which should be done at specific times disregarding of what other operations are pending. For this purpose, schedulers in some operating systems are made in a way to start tasks and predefined times. Such operating systems are called real-time operating systems (RTOS), because each task (application) running in RTOS can specify specific time (in milliseconds or other real time unit) at which it should be started. To organize this for several tasks scheduler uses priorities set for tasks, so that if two applications requested to be called at the same time, the one with higher priority gets the resources.


As resources becoming abundant for modern micro processors, the cost to run RTOS is become increasingly insignificant. RTOS also provides event-driven mode for better utilization of CPU with efficiency.

FreeRTOS is an implementation of RTOS specially designed to be compact, easy to use and freely available (under GPL license with several exceptions). FreeRTOS source code is available for download at http://freertos.org and for different processor it should be ported (architecture specific code needs to be changed) so that it can operate on the specific processor. |embarc| includes FreeRTOS port for |arc| that can be used to run applications using RTOS. FreeRTOS contains all the basic features of RTOS: tasks, scheduler, notifications, semaphores, mutexes, etc.


Design
------
This lab implements a running LED light with 3 tasks on FreeRTOS. Despite using 3 tasks overkill for a running LED, but it is beneficial for the understanding of FreeRTOS itself and inter-task communication as well.

The following is the flow chart of the program:

.. image:: /img/lab9_program_flow_chart.png
    :alt: program flow chart

Realization
-----------
The following is the example code of system , including various initialization and task time delay.

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

Build and run the uncompleted code
----------------------------------
The code is at ``embarc_osp/arc_labs/labs/lab9_freertos``, uses an UART terminal console and run the code, the following message from program is displayed:

.. code-block:: console

	embARC Build Time: Mar  9 2018, 17:57:50
	Compiler Version: Metaware, 4.2.1 Compatible Clang 4.0.1 (branches/release_40)
	Create task1 Successfully
	Create task2 Successfully
	Create task3 Successfully

This message implies that three tasks are working correctly.

Implement task 3
----------------
It is required for task 3 to retrieve new value from the queue and assign the value to led_val. The LED controls are already implemented in previous labs, the new function to learn is ``xQueueReceive()``. This is a FreeRTOS API to pop and read an item from queue. See FreeRTOS documentation and complete the code for this task. (An example is in 'complete' folder)

Implement task 1
----------------
It is required for task 1 to check if value from queue is legal. If not, a reset signal is needed to be sent.

Two new functions might be helpful for this task: ``xSemaphoreGive()`` for release a signal and ``xQueuePeek()`` for read item but not pop from a queue. See FreeRTOS documentation and complete the code for this task. (An example is in 'complete' folder)

Do notice the difference between ``xQueueReceive()`` and ``xQueuePeek()``.

Implement task 2
----------------
There are two different works for task 2 to complete: to shift led_val and queue it, and to reset both led_val and queue when illegal led_val is detected.

Three functions can be helpful: ``xQueueSend()``, ``xSemaphoreTake()``, ``xQueueReset()``. See FreeRTOS documentation and complete the code for this task. (An example is in 'complete' folder)

Build and run the completed code
--------------------------------

BUild the completed program and debug it to fulfill all requirements. (8-digit running LEDs are used in example code)

Exercises
=========
The problem of philosophers having meal:

Five philosophers sitting at a round dining table. Suppose they are either thinking or eating, but they cannot do these two things at same time. So each time when they are having food, they stop thinking and vice versa. There are five forks on the table for eating noddle, each fork is placed between two adjacent philosophers  It is hard to eat noddle with one fork, so all philosophers need two forks in order to eat.

Write a program with proper console output to simulate this process.
