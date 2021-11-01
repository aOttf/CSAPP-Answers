#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

int bad_int_size_is_32() {
	int set_msb = 1 << 15 << 15 << 1;
	int beyond_msb = set_msb << 1;

	return set_msb && !beyond_msb;
}

int lower_one_mask(int n) {
	int x = -1;
	//Consider n = w
	x <<= 1;
	x <<= n - 1;

	return ~x;

}

unsigned rotate_left(unsigned x, int n) {

	return x << n | x >> ((sizeof(int) << 3) - n);

}

int fits_bits(int x, int n) {
	//Consider the case where n = w
	int mask = -1 << (n - 1);
	int prefix = mask & x;

	return !(prefix && (prefix ^ mask));

	/*Another Solution is to check equalness directly */
	//int w = sizeof(int} << 3;
	//int offset = w - n;
	//return x << offset >> offset == x;
}

void test_bad_int_size_is_32() {
	assert(1 == bad_int_size_is_32());
}

void test_lower_one_mask() {
	assert(0x3f == lower_one_mask(6));
	assert(0x1ffff == lower_one_mask(17));
	assert(0x1 == lower_one_mask(1));
	assert(-1 == lower_one_mask(sizeof(int) << 3));
}

void test_rotate_left() {
	int x = 0x12345678;
	assert(0x23456781 == rotate_left(x, 4));
	assert(0x67812345 == rotate_left(x, 20));
	assert(x == rotate_left(x, 0));
	assert(0x81234567 == rotate_left(x, 28));
	assert(x == rotate_left(x, sizeof(int) << 3));
}

void test_fits_bits() {
	assert(!fits_bits(0xFF, 8));
	assert(!fits_bits(~0xFF, 8));

	assert(fits_bits(0b0010, 3));
	assert(!fits_bits(0b1010, 3));
	assert(!fits_bits(0b0110, 3));

	assert(fits_bits(~0b11, 3));
	assert(!fits_bits(~0b01000011, 3));
	assert(!fits_bits(~0b111, 3));
}

int main() {
	test_bad_int_size_is_32();
	test_lower_one_mask();
	test_rotate_left();
	test_fits_bits();
}
