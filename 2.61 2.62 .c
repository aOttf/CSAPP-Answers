#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

/*Get most significant byte from x */
unsigned get_msb(unsigned x) {
	unsigned shift = (sizeof(unsigned) - 1) << 3;
	return (x >> shift) & 0xff;
}

unsigned get_lsb(unsigned x) {
	return x & 0xff;
}

/*2.61 */
bool two_sixone(int x) {
	/*Condition A */
	bool condA = !~x;
	bool condB = !x;
	bool condC = !(get_lsb(x) ^ 0xff);
	bool condD = !get_msb(x);

	return condA || condB || condC || condD;
}

/* 2.62 */
bool int_shifts_are_arithmetic() {
	/* 0x1111111111...11 */
	int i = -1;
	return !((i >> 1) ^ i);
}

void test_two_sixone() {
	assert(two_sixone(0x0));
	assert(two_sixone(-1));
	assert(two_sixone(0xff));

	/* INT_MIN = 0x10000000...00 */
	assert(!two_sixone(INT_MIN));
	assert(!two_sixone(INT_MIN + 0xf));
}

void test_int_shifts_are_arithmetic() {
	assert(int_shifts_are_arithmetic());
}

int main() {
	test_two_sixone();
	test_int_shifts_are_arithmetic();
}
