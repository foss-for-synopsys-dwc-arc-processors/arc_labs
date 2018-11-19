/*************************************************************************/
/*************************************************************************/
/**                                                                     **/
/** Copyright (C) 1989-2015 Synopsys, Inc.                              **/
/** All Rights Reserved.                                                **/
/**                                                                     **/
/** SYNOPSYS CONFIDENTIAL                                               **/
/**                                                                     **/
/** This is an unpublished proprietary work of Synopsys, Inc., and is   **/
/** fully protected under copyright and trade secret laws. You may not  **/
/** view, use, disclose, copy, or distribute this file or any           **/
/** information contained herein except pursuant to a valid written     **/
/** license from Synopsys.                                              **/
/**                                                                     **/
/** For more information, contact                                       **/
/** est-adm@synopsys.com or call (650) 584-1631                         **/
/**                                                                     **/
/*************************************************************************/
/*************************************************************************/
#include <stdio.h>

#include "starter.h"
#include "board.h"

/*
 *   This program calculates dot product of 2 square matrices to measure
 *   speed of operations with and without processor DSP extension.
 *
 *   For the sake of speed test, matrix multiplication is done for number of times (LOOPs).
 *   Total number of multiplications is divided into 8 parts. After each part of
 *   multiplications is done, a led on the EMSK board is switched on. This
 * 	 process is repeated 8 times until all leds are on. The led strip in this way
 * 	 stands as a "progress bar" of operations.
 *
 * 	 Matrix multiplication is done with naive O(n^3) algorithm.
 * 	 Thus in total LOOP*(MATRIX_SIZE^3) multiplications are done.
 *
 * 	 When program starts, two input matrices are initialized with random numbers
 * 	 and then multiplied.
 *	 ------------------------------------------------------------------------
 *
 * 	 The program should be compiled in two variants:
 * 	  - with -O2 and -Xdsp1 options
 * 	  - with -O2 option only
 *
 *	and compared in speed.
 *
 *
 *	Note: The program was tested on EMSK 2.1 board, with EM5D configuration.
 *
 */


 /*
  *     Program configuration (constants)
  *
  * 	LOOP 		- Total number of multiplications
  * 	MATRIX_SIZE - Square matrix size
  * 	MAX_NUM     - Max  with value up to  constant.
  *
  */
#define MATRIX_SIZE 20
#define MAX_NUM 1000
#define LOOPS 1000

/* ********************************************* */

/* Matrix manipulation functions */

/* randomize matrix with values up to 'max_value */
void rand_sq_mat(short x[][MATRIX_SIZE], int SIZE, int max_value) ;

/* multiply two square matrices of same size*/
void mul_sq_mat(short x[][MATRIX_SIZE], short y[][MATRIX_SIZE], short z[][MATRIX_SIZE], int size) ;

/* print square matrix through UART*/
void print_sq_mat(short x[][MATRIX_SIZE], int SIZE, DWCREG_PTR uart);

/* ********************************************* */

int main(int argc, char *argv[]) {
	
	DWCREG_PTR pctr = (DWCREG_PTR) (DWC_GPIO_0 | PERIPHERAL_BASE);
	DWCREG_PTR uart = (DWCREG_PTR) (DWC_UART_CONSOLE | PERIPHERAL_BASE);

	gpio_init(pctr);
	uart_initDevice(uart, UART_CFG_BAUDRATE_115200, UART_CFG_DATA_8BITS, UART_CFG_1STOP, UART_CFG_PARITY_NONE);

	short a[MATRIX_SIZE][MATRIX_SIZE];
	short b[MATRIX_SIZE][MATRIX_SIZE];
	short c[MATRIX_SIZE][MATRIX_SIZE];
	int n =MATRIX_SIZE;

	rand_sq_mat(a,n, MAX_NUM);
	rand_sq_mat(b,n, MAX_NUM);

	print_sq_mat(a,n,uart);
	print_sq_mat(b,n,uart);

	unsigned int led_status = 0x40 ;
	led_status = 0x7F;

	uart_print(uart, "*** Start ***\n\r");

	for (int i =0; i< 8; i++) {
		gpio_set_leds(pctr, led_status);

		for (int j = 1; j < LOOPS/8; j++ ) {
			mul_sq_mat(a,b,c,n);
		};


		led_status = led_status >> 1;
	}

	print_sq_mat(c,n,uart);
	gpio_set_leds(pctr, 0x01ff);

	uart_print(uart, "*** Exit ***\n\r");

	return 0;
}



void rand_sq_mat(short x[][MATRIX_SIZE], int SIZE, int max_value) {
	for (int i=0;i<SIZE;i++) {
		for(int j=0;j<SIZE;j++) {
			x[i][j] = 1 + (rand() % max_value); //plus 1 to avoid zeros
		}
	}
}

void mul_sq_mat(short x[][MATRIX_SIZE],short y[][MATRIX_SIZE], short z[][MATRIX_SIZE], int size) {
	for (int i=0; i<size; i++) {
		for(int j=0;j<size;j++) {
			z[i][j]=0;
			for(int k=0;k<size;k++) {
				z[i][j] += x[i][k]*y[k][j];
			}
		}
	}
}

void print_sq_mat(short x[MATRIX_SIZE][MATRIX_SIZE], int SIZE, DWCREG_PTR uart){

	char buffer[60];

	uart_print(uart, "------\n\r");

	for(int j = 0; j < SIZE; j++ ){
        for(int i = 0; i < SIZE; i ++){
            sprintf(buffer, "%d \t", x[j][i] );
            uart_print(uart,buffer);
        }
        uart_print(uart, "\n\r" );
    }

    uart_print(uart, "------\n\r");
}
