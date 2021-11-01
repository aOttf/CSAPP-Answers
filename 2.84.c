#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <inttypes.h>
#include <assert.h>

/*	Return an unsigned integer of same bits representation of float x	*/
unsigned f2u(float x) {
	return *((unsigned*) &x);
}

/*	2.84	*/
int float_le(float x, float y) {
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);

	/*	Get the sign bits	*/
	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;

	return (sx && !sy) || (sx && sy && (ux >= uy)) || (!sx && !sy && (ux <= uy))
			|| (!(ux << 1) && !(uy << 1));
}

int main() {
	assert(float_le(-0, +0));
	assert(float_le(+0, -0));
	assert(float_le(0, 3));
	assert(float_le(-4, -0));
	assert(float_le(-4, 4));
	return 0;

}
