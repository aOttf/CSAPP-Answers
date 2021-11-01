#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <inttypes.h>

int tadd_overf(int x, int y) {
	int sum = x + y;
	int mask = INT_MIN;
	int ssign = ~(x ^ y) & mask; /* 1 if x and y have the same sign, 0 otherwise	*/

	return ssign && ((sum ^ x) & mask);

}
/*	2.74	*/
int tsub_ok(int x, int y) {
	int mask = INT_MIN;
	int minok = (-y == y) && (x & mask);
	int nminok = (-y != y) && !tadd_overf(x, -y);
	return minok || nminok;
}

int signed_high_prod(int x, int y) {
	size_t w;
	w = sizeof(int) << 3;
	return (int) (((int64_t) x * y) >> w);
}

/*	2.75	*/
unsigned unsigned_high_prod(unsigned x, unsigned y) {
	size_t w;
	w = sizeof(unsigned) << 3;

	return (unsigned) (((int64_t) x * y) >> w);
}

/*	2.76	*/
void* calloc1(size_t nmemb, size_t size) {
	if (!nmemb || !size)
		return NULL;

	/*	nmemb * size > 0	*/
	size_t mem;
	if ((mem = nmemb * size) / nmemb != size)
		/*	OverFlow Occured	*/
		return NULL;

	void *ptr = malloc(mem);
	return memset(ptr, 0, mem);
}

/*	2.78	*/
int divide_power2(int x, int k) {
	return ((x & INT_MIN) ? (x + (1 << k) - 1) : x) << k;
}

/*	2.79	*/
int mul3div4(int x) {
	return divide_power2(x + (x << 1), 2);
}

/*	2.80	*/
int threefourths(int x) {
	int xd4 = divide_power2(x, 2);
	return xd4 + (xd4 << 1);
}
