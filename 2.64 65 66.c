#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

int any_odd_one(unsigned x) {
	int mask = 0xaaaaaaaa;
	return !!(x & mask);
}

int odd_ones(unsigned x) {
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;

	return x & 1;
}

int leftmost_one(unsigned x) {
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	return ((x + 1) >> 1) | (!~x << 31);
}

void test_any_odd_one() {

}

void test_odd_ones() {

}

void test_leftmost_one() {
	assert(INT_MIN == leftmost_one(-1));
	assert(0x8000 == leftmost_one(0xff00));
	assert(0 == leftmost_one(0));
}

int main() {
	test_any_odd_one();
	test_odd_ones();
	test_leftmost_one();
}
