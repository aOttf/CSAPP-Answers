#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

unsigned srl(unsigned x, int k) {
	int w = sizeof(int) << 3;
	if (k < 0 || k >= w) {
		puts("the range of k is not correct.");
		return x;
	}

	unsigned xsra = (int) x >> k;
	/* Two shift-left operation considering the case k = 0 */
	int mask = ~((~0x0) << (w - k - 1) << 1);
	return xsra & mask;

}

int sra(int x, int k) {
	int w = sizeof(int) << 3;
	if (k < 0 || k >= w) {
		puts("the range of k is not correct.");
		return x;
	}

	/* Get Sign of x */
	int xsrl = (unsigned) x >> k;

	/* Two shift-left operation considering the case k = 0 */
	int sign = !((1 << (w - 1)) & x) - 1;
	int mask = sign << (w - k - 1) << 1;
	return xsrl ^ mask;
}

void test_srl() {
	unsigned x, k;
	x = 0;
	k = 0;
	assert(srl(x, k) == x >> k);
	x = 0xff;
	k = 12;
	assert(srl(x, k) == (x >> k));

	x = rand();
	k = rand() % 32 + 1;
	assert(srl(x, k) == x >> k);
	x = INT_MAX;
	k = 31;
	assert(srl(x, k) == (x >> 31));
	x = INT_MIN;
	assert(srl(x, k) == (x >> 31));

}

void test_sra() {
	int x, k;
	x = 0;
	k = 0;
	assert(sra(x, k) == x >> k);
	x = 0xff;
	k = 12;
	assert(sra(x, k) == (x >> k));

	x = rand();
	k = rand() % 32 + 1;
	assert(sra(x, k) == x >> k);
	x = INT_MAX;
	k = 31;
	assert(sra(x, k) == (x >> 31));
	x = INT_MIN;
	assert(sra(x, k) == (x >> 31));
}

int main() {
	test_srl();
	test_sra();
}
