#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>

size_t xlyr(size_t x, size_t y) {
	size_t mask = 0xff;
	return (x | ~mask) & (y | mask);
}
int main() {
	int x = 0x89abcdef;
	int y = 0x76543210;
	assert(xlyr(x, y) == 0x765432ef);
}
