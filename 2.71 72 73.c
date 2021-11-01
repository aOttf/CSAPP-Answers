#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <inttypes.h>

/*	2.71	*/
typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
	return (int) (word << ((sizeof(packed_t) - 1 - bytenum) << 3))
			>> ((sizeof(packed_t) - 1) << 3);
}

/*	2.72	*/
void copy_int(int val, void *buf, int maxbytes) {
	if (maxbytes >= sizeof(val))
		memcpy(buf, (void*) &val, sizeof(val));
}

/*	2.73	*/
int saturating_add(int x, int y) {
	int sum = x + y;
	int mask = INT_MIN;

	int pos_of = !(x & mask) && !(y & mask) && (sum & mask);
	int neg_of = (x & mask) && (y & mask) && !(sum & mask);
	(pos_of && (sum = INT_MAX)) || (neg_of && (sum = INT_MIN));

	return sum;
}

