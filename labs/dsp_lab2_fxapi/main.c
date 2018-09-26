//#include <fxarc.h>
#include "embARC.h"
#include "embARC_debug.h"
#include "fxarc.h"

typedef struct { short real; short imag; } complex_short;

cq15_t fx_complex_array_mult (cq15_t *a, cq15_t *b, int size);
complex_short short_complex_array_mult (complex_short *a, complex_short *b, int size);

#define LOOPS 10000000
	//__xy cq15_t  cq15_a[20] = {{0x2000,10},{0x100,20},{4,30}};
	//__xy cq15_t  cq15_b[20] = {{0x2000,11},{0x100,21},{5,31}};
	//__xy cq15_t res;

	volatile complex_short  cq15_a[20] = {{0x2000,10},{0x100,20},{4,30}};
	volatile complex_short  cq15_b[20] = {{0x2000,11},{0x100,21},{5,31}};
	volatile complex_short res;

int main(int argc, char *argv[]) {
	unsigned int led_status = 0x40 ;



	EMBARC_PRINTF("LAB 2\r\n");
	led_status = 0x7F;

	for (int i =0; i< 8; i++) {
		for (int j = 1; j < LOOPS/8; j++ ) {
			//res = fx_complex_array_mult(cq15_a, cq15_b, 20);
			res = short_complex_array_mult(cq15_a, cq15_b, 20);
		};
		led_write(led_status, BOARD_LED_MASK);
		led_status = led_status >> 1;
	}
	//	EMBARC_PRINTF("res.real=%d \r\n", res[0]);
		EMBARC_PRINTF("res.real=%d \r\n", res.real);
	return 0;
}
complex_short short_complex_array_mult (complex_short *a, complex_short *b, int size) {
	complex_short result = {0,0};
	int acci=0;
	int accr=0;

	for (int i=0; i < size; i++) {
		accr  += (int) ( a[i].real * b[i].real );
		accr  -= (int) ( a[i].imag * b[i].imag );

		acci  += (int) ( a[i].real * b[i].imag );
		acci  += (int) ( a[i].imag * b[i].real );
	}

	result.real = (short) accr;
	result.imag = (short) acci;

	return result;
}

cq15_t fx_complex_array_mult(cq15_t *a, cq15_t *b, int size) {
	v2accum40_t acc = { 0, 0 };

	for (int i=0; i < size; i++) {
	   acc = fx_v2a40_cmac_cq15(acc, *a++, *b++);
	}

	return fx_cq15_cast_v2a40( acc );
}

/** @} */
