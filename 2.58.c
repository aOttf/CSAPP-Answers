#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define LITTLE_ENDIAN 1
#define BIG_ENDIAN 0

typedef unsigned char *byte_ptr;
/*
 * Is_little_endian Procedure
 * returns 1 on a little_endian machine; 0 otherwise
 */
int main() {
	int i = 0x01;
	byte_ptr bptr = (byte_ptr) &i;

	return (*bptr == 1) ? BIG_ENDIAN : LITTLE_ENDIAN;
}
