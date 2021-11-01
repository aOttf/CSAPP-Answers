#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <inttypes.h>
#include <assert.h>

typedef unsigned float_bits;
#define FMASK	0xff000000
#define EMASK	0x00ffffff

#define BIAS	0x7f

float u2f(unsigned u) {
	return *(float*) &u;
}
/*	2.92	*/
float_bits float_negate(float_bits f) {
	/*	NaN Case	*/
	float_bits nsf = f << 1; /*	float bits without sign bit	*/
	if (!((nsf & FMASK) ^ FMASK) && (nsf & EMASK))
		return f;

	return f ^ 0x80000000;
}

void test_float_negate() {

}
/*	2.93	*/
float_bits float_absval(float_bits f) {
	/*	NaN Case	*/
	float_bits nsf = f << 1; /*	float bits without sign bit	*/
	if (!((nsf & FMASK) ^ FMASK) && (nsf & EMASK))
		return f;

	return f | INT_MIN;
}

void test_float_absval() {

}
/*	2.94	*/
float_bits float_twice(float_bits f) {
	/*	Decompose float bits	*/
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xff;
	unsigned frac = f & 0x7fffff;

	/*	NaN Case and Infinity Case	*/
	if (!(exp ^ 0xff))
		return f;

	/*	SubNormal Case	*/
	if (!exp)
		return (sign << 31) | (frac << 1);

	/*	OverFlow	*/
	if (!(exp ^ 0xfe))
		return (sign << 31) | (++exp << 23);

	/*	Normal Case	*/
	return (sign << 31) | (++exp << 23) | frac;
}

void test_float_twice() {

}
/*	2.95	*/
float_bits float_half(float_bits f) {
	/*	Decompose float bits	*/
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xff;
	unsigned frac = f & 0x7fffff;

	/*	NaN Case and Infinity Case	*/
	if (!(exp ^ 0xff))
		return f;

	/*	SubNormal Case	*/
	if (!exp)
		return (sign << 31) | (frac >> 1);

	/*	exp = 1 */
	if (exp == 1)
		return (sign << 31) | (f >> 1);

	/*	Other Normal Case	*/
	return (sign << 31) | (--exp << 23) | frac;
}

void test_float_half() {

}

/*	2.96	*/
int float_f2i(float_bits f) {
	/*	Decompose float bits	*/
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xff;
	unsigned frac = f & 0x7fffff;

	unsigned absval;
	unsigned round_p; /*	Round Part	*/
	unsigned round_m; /*	Round Middle	*/

	int expn = exp - BIAS;

	/*	NaN or Infinity	or OverFlow*/
	if (expn > 31)
		return 0x80000000;

	/*	subnormal or expn < -1*/
	if (!exp || expn < -1)
		return 0;

	/*	normal without rounding */
	if (expn >= 23) {
		absval = ((1 << 23) | frac) << (expn - 23);
		return (sign) ? -absval : absval;
	}

	/*	normal with rounding	*/
	if (expn == -1) {
		round_p = (1 << 23) | frac;
		round_m = (1 << 23) & frac;
		absval = 0;
	} else if (expn == 0) {
		round_p = frac;
		round_m = (1 << 22) & frac;
		absval = 1;
	} else {
		/*	1 <= expn <= 22	*/
		round_p = ((unsigned) -1 >> (expn + 9)) & frac;
		round_m = (1 << (22 - expn)) & frac;
		absval = frac >> (23 - expn);
	}

	/*	Rounding	*/
	(round_p > round_m || ((round_p == round_m) && (0x1 & frac))) && absval++;

	return (sign) ? -absval : absval;
}

void test_float_f2i() {

}

/*	2.97	*/
float_bits float_i2f(int i) {
	unsigned isign = i >> 31;
	unsigned absval = (isign) ? -i : i;
	unsigned fbits; /*	Fraction Bits */
	unsigned frac;
	unsigned round_part, round_mid;
	int exp;
	unsigned mask;
	unsigned offset;

	/*	i = zero	*/
	if (!absval)
		return 0;

	/*	Set fraction bits and exponent */
	for (fbits = 31, mask = INT_MIN; !(absval & mask) && fbits;
			mask >>= 1, fbits--)
		;
	exp = fbits + BIAS;

	/*	Set fraction	*/
	mask = -1;
	frac = (fbits > 23) ?
			((absval << (32 - fbits)) & 0xfffffe00) >> 9/* 32  - 23 */:
			(absval & (mask >> (32 - fbits)));

	/*	Set Round */
	if (fbits > 23) {
		offset = fbits - 23;
		round_part = absval & (mask >> (32 - offset));
		round_mid = 1 << offset;

		/*	round_partition > round_mid ==> rounding up
		 * round_partition == round_mid AND the rightmost bit of fraction is odd ==> rounding up
		 */
		(round_part > round_mid || ((round_part == round_mid) && (0x1 & frac)))
				&& frac++;

		/*	Cehck if there's a carry bit in fraction after rounding up */
		(frac & 0x800000) && exp++;
	}

	return (isign << 31) | (exp << 23) | frac;

}

void test_float_i2f() {

}

int main() {
	test_float_negate();
	test_float_absval();
	test_float_twice();
	test_float_half();
	test_float_f2i();
	test_float_i2f();

	return 0;
}
