#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef unsigned char *byte_ptr;

void show_bytes(byte_ptr, size_t);
void show_int(int);
void show_float(float);
void show_pointer(void*);
void show_short(short);
void show_long(long);
void show_double(double);

void show_bytes(byte_ptr start, size_t len) {
	size_t i;
	for (i = 0; i < len; i++)
		printf("%.2x", start[i]);
	putc('\n', stdout);
}

void show_int(int x) {
	show_bytes((byte_ptr) &x, sizeof(int));
}

void show_float(float f) {
	show_bytes((byte_ptr) &f, sizeof(float));
}

void show_pointer(void *ptr) {
	show_bytes((byte_ptr) &ptr, sizeof(void*));
}

void test_show_bytes(int val) {
	int ival = val;
	float fval = (float) val;
	void *pval = &val;
	short sval = (short)val;
	long lval = (long)val;
	double dval = (double)val;

	show_int(ival);
	show_float(fval);
	show_pointer(pval);
	show_short(sval);
	show_long(lval);
	show_double(dval);

}

void show_short(short s) {
	show_bytes((byte_ptr) &s, sizeof(short));
}
void show_long(long l) {
	show_bytes((byte_ptr) &l, sizeof(long));
}
void show_double(double d) {
	show_bytes((byte_ptr) &d, sizeof(double));

}
int main() {
	test_show_bytes(20);
	puts("----------------------");
	test_show_bytes(0xffffffff);
	puts("----------------------");
	test_show_bytes(0x12345678);

}
