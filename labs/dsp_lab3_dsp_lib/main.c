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
