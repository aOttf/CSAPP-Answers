#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
	if (i < 0) {
		puts("i should be non negative.");
		return x;
	}

	if (i >= sizeof(unsigned)) {
		puts("i too big.");
		return x;
	}

	//i << 3 = i * 8
	unsigned shift = i << 3;
	return (b << shift) | (x & ~(0xff << shift));
}

int main() {

	assert(replace_byte(0x12345678, 2, 0xAB) == 0x12ab5678);
	assert(replace_byte(0x12345678, 0, 0xab) == 0x123456ab);

}
