.. _lab_dsp3:

ARC DSP: Using DSP Library
===============================

Purpose
----------------------------
- To understand what is ARC DSP library 
- To learn how to use DSP library to optimize DSP programs

Requirements
-----------------------------
The following hardware and tools are required:

* PC host
* |mwdt|
* ARC board (|emsk| / |iotdk|)
* ``embarc_osp/arc_labs/labs/dsp_lab_dsp_lib``

Content
-------------------------------------

This lab uses matrix multiplication as an example where DSP library helps to efficiently use DSP extensions with shorter code.
To use DSP Library and compare the execution speed of the programs with and without DSP library.

Principle
-------------------------------------

In this lab two implementations of matrix multiplication are shown:
One manual implementation and the other using the DSP library.

Matrix multiplication
^^^^^^^^^^^^^^^^^^^^^^^^^^

Multiplication of two matrices A and B of sizes [M*N] and [N*K] respectively is implemented using the following formula:

|dsp_icon_3.1|

Where i= 0...(M-1) and j = 0..(K-1) are row and column indexes of output matrix, with size [M*K].

Implementation without DSP
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The following example shows the implementation of matrix multiplication of two matrices containing "short" values. By convention, matrices here are implemented as 1D arrays with row-first indexing, where element a_ik is indexed as
|dsp_icon_3.2|

.. code-block:: c

    #include "embARC.h"
    #include "embARC_debug.h"
    #include <stdlib.h>

    #define MATRIX_SIZE 20
    #define MAX_NUM 1000
    #define LOOPS 100000

    /* ********************************************* */

    /* Matrix manipulation functions */

    /* randomize matrix with values up to 'max_value */
    void rand_sq_mat(short x[][MATRIX_SIZE], int SIZE, int max_value) ;

    /* multiply two square matrices of same size*/
    void mul_sq_mat(short x[][MATRIX_SIZE], short y[][MATRIX_SIZE], short z[][MATRIX_SIZE], int size) ;

    /* print square matrix through UART*/
    void print_sq_mat(short x[][MATRIX_SIZE], int SIZE);

    /* ********************************************* */

    int main(int argc, char *argv[]) {

    	short a[MATRIX_SIZE][MATRIX_SIZE];
    	short b[MATRIX_SIZE][MATRIX_SIZE];
    	short c[MATRIX_SIZE][MATRIX_SIZE];
    	int n =MATRIX_SIZE;

    	rand_sq_mat(a,n, MAX_NUM);
    	rand_sq_mat(b,n, MAX_NUM);

    	print_sq_mat(a,n);
    	print_sq_mat(b,n);

    	unsigned int led_status = 0x40 ;
    	led_status = 0x7F;

    	EMBARC_PRINTF("*** Start ***\n\r");

    	for (int i =0; i< 8; i++) {
    		for (int j = 1; j < LOOPS/8; j++ ) {
    			mul_sq_mat(a,b,c,n);
    		};
    		led_write(led_status, BOARD_LED_MASK);
    		led_status = led_status >> 1;
    	}

    	print_sq_mat(c,n);

    	EMBARC_PRINTF("*** Exit ***\n\r");

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

    void print_sq_mat(short x[MATRIX_SIZE][MATRIX_SIZE], int SIZE){

    	EMBARC_PRINTF("------\n\r");

    	for(int j = 0; j < SIZE; j++ ){
            for(int i = 0; i < SIZE; i ++){
                EMBARC_PRINTF("%d\t", x[j][i]);
            }
            EMBARC_PRINTF("\n\r" );
        }

        EMBARC_PRINTF("------\n\r");
    }

Implementation with DSPLIB
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

DSP library contains matrix multiplication function, implementing matrix multiplication using DSP library requires initialization of matrix arrays (1D) and call to ``dsp_mat_mult_q15``. The overall code is 4 lines, as highlighted in the following code. Note that dsplib.h must be included, and matrix a, b, and c must be declared as global variable. As the numbers are in q15 type, it is better to make elements of a and b between 32767 (~0.99) and 16384 (0.5), or 32768(-1) and 49152 (-0.5) that the result in c is not rounded to zero. Note as IOTDK is configured to have small AGU, the DSP library routine is not significantly faster.

.. code-block:: c

    #include "embARC.h"
    #include "embARC_debug.h"
    #include <stdlib.h>
    #include "dsplib.h"

    #define MATRIX_SIZE 20
    #define MAX_NUM 1000
    #define LOOPS 100000

    /* ********************************************* */

    /* Matrix manipulation functions */

    /* randomize matrix with values up to 'max_value */
    //void rand_sq_mat(short x[][MATRIX_SIZE], int SIZE, int max_value) ;

    /* multiply two square matrices of same size*/
    void mul_sq_mat(short x[][MATRIX_SIZE], short y[][MATRIX_SIZE], short z[][MATRIX_SIZE], int size) ;

    /* print square matrix through UART*/
    void print_sq_mat(short* x, int SIZE);

    /* ********************************************* */
    	__xy q15_t a[MATRIX_SIZE*MATRIX_SIZE];
    	__xy q15_t b[MATRIX_SIZE*MATRIX_SIZE];
    	__xy q15_t c[MATRIX_SIZE*MATRIX_SIZE];

    int main(int argc, char *argv[]) {

    	int n =MATRIX_SIZE;
    matrix_q15_t matA, matB, matC;

    	//rand_sq_mat(a,n, MAX_NUM);
    	//rand_sq_mat(b,n, MAX_NUM);
    	for (int i =0; i< MATRIX_SIZE*MATRIX_SIZE; i++) { a[i]=16384; }
    	for (int i =0; i< MATRIX_SIZE*MATRIX_SIZE; i++) { b[i]=16383; }


    	print_sq_mat(a,n);
    	print_sq_mat(b,n);

    dsp_mat_init_q15(&matA,  MATRIX_SIZE, MATRIX_SIZE, a);
    dsp_mat_init_q15(&matB,  MATRIX_SIZE, MATRIX_SIZE, b);
    dsp_mat_init_q15(&matC,  MATRIX_SIZE, MATRIX_SIZE, c);
    dsp_status status;

    	unsigned int led_status = 0x40 ;
    	led_status = 0x7F;

    	EMBARC_PRINTF("*** Start ***\n\r");

    	for (int i =0; i< 8; i++) {
    		for (int j = 1; j < LOOPS/8; j++ ) {
    			status = dsp_mat_mult_q15(&matA, &matB, &matC);
    		};
    		led_write(led_status, BOARD_LED_MASK);
    		led_status = led_status >> 1;
    	}

    	if ( status == DSP_ERR_OK ) EMBARC_PRINTF("done\n");
    	else EMBARC_PRINTF("something wrong");
    	print_sq_mat(c,n);

    	EMBARC_PRINTF("*** Exit ***\n\r");

    	return 0;
    }



    //void rand_sq_mat(short x[][MATRIX_SIZE], int SIZE, int max_value) {
    //	for (int i=0;i<SIZE;i++) {
    //		for(int j=0;j<SIZE;j++) {
    //			x[i][j] = 1 + (rand() % max_value); //plus 1 to avoid zeros
    //		}
    //	}
    //}
    //
    //void mul_sq_mat(short x[][MATRIX_SIZE],short y[][MATRIX_SIZE], short z[][MATRIX_SIZE], int size) {
    //	for (int i=0; i<size; i++) {
    //		for(int j=0;j<size;j++) {
    //			z[i][j]=0;
    //			for(int k=0;k<size;k++) {
    //				z[i][j] += x[i][k]*y[k][j];
    //			}
    //		}
    //	}
    //}

    void print_sq_mat(short* x, int SIZE){

    	EMBARC_PRINTF("------\n\r");

    	for(int j = 0; j < SIZE; j++ ){
            for(int i = 0; i < SIZE; i ++){
                EMBARC_PRINTF("%d\t", x[i+j*SIZE]);
            }
            EMBARC_PRINTF("\n\r" );
        }

        EMBARC_PRINTF("------\n\r");
    }

Using |iotdk| board for performance comparison
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. note::

    Create an |iotdk| application that uses LED strip as progress bar for large number of matrix multiplications with and without DSP library, adjust number of loops made to achieve measurable delay. Run the example and compare computational delay with and without DSPLIB.

Steps
-----------------

Both examples are to be compiled with DSP extensions, with the following options set:

``-O2  -arcv2em -core1 -Xlib -Xtimer0 -Xtimer1 -Xdsp1 -Hdsplib``

Step 1. Run program without DSP library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Build with the command:

``gmake BOARD=iotdk BD_VER=10 CUR_CORE=arcem9d TOOLCHAIN=mw gui ADT_COPT="-Hdsplib -Xdsp2 -tcf=./arcem9d.tcf``

  ``-Xdsp_complex" ADT_LOPT="-Hdsplib -Xdsp2 -tcf=./arcem9d.tcf -Hlib=./my_dsp"``

Step 2. Run program with DSP library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Rename main.c.dsplib to main.c, then execute the command:

``gmake BOARD=iotdk BD_VER=10 CUR_CORE=arcem9d TOOLCHAIN=mw gui ADT_COPT="-Hdsplib -Xdsp2 -tcf=./arcem9d.tcf``

  ``-Xdsp_complex" ADT_LOPT="-Hdsplib -Xdsp2 -tcf=./arcem9d.tcf -Hlib=./my_dsp"``

Note that DSPLIB is statically linked with the project when -Hdsplib is set, and as the DSPLIB itself is pre-compiled with high level of optimization, changing optimization option for example program does not affect DSPLIB performance. On the other hand, even with highest optimization level a function utilizing simple instructions on "short" type (even converted to MACs if possible) is less efficient that direct use of DSPLIB.

.. |dsp_icon_3.1| image:: /img/dsp_icon_3.1.png
.. |dsp_icon_3.2| image:: /img/dsp_icon_3.2.png
