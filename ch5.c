#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include "vec.h"

/*
 * Create Vector of specified length
 */
vec_ptr new_vec(long len) {
	vec_ptr result;
	data_t *data = NULL;

	result = (vec_ptr) malloc(sizeof(vec_rec));
	if (!result) {
		return NULL; /*Couldnt Alloc Storage. */
	}

	result->len = len;
	if (len > 0) {
		data = (data_t*) malloc(sizeof(data_t) * len);
		if (!data) {
			free(result);
			return NULL; /*Couldnt Alloc Storage. */
		}
	}
	result->data = data;

	return result;
}

int get_vec_element(vec_ptr v, long index, data_t *dest) {

	if (!v || index < 0 || index >= v->len)
		return 0;

	*dest = v->data[index];
	return 1;
}

data_t* get_vec_start(vec_ptr v) {
	return v->data;
}

long vec_len(vec_ptr v) {
	if (!v)
		return -1;

	return v->len;
}

void combine1(vec_ptr v, data_t *dest) {
	long i;

	*dest = IDENT;
	for (i = 0; i < vec_len(v); i++) {
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}

void combine2(vec_ptr v, data_t *dest) {
	long i, max_len;
	max_len = vec_len(v);

	*dest = IDENT;
	for (i = 0; i < max_len; i++) {
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}

}

void combine3(vec_ptr v, data_t *dest) {
	long i, max_len;
	data_t *data;
	data = get_vec_start(v);
	max_len = vec_len(v);

	for (i = 0; i < max_len; i++) {
		*dest = *dest OP data[i];
	}
}

/*
 * Ex 5.4 Optimized Version of combine3
 */
void combine3_X(vec_ptr v, data_t *dest) {
	long i, max_len;
	data_t *data, acc;
	data = get_vec_start(v);
	max_len = vec_len(v);
	acc = IDENT;

	/*Case length of vector <= 0 */
	*dest = acc;

	for (i = 0; i < max_len; i++) {
		acc = acc OP data[i];
		*dest = acc;
	}
}

void combine4(vec_ptr v, data_t *dest) {
	long i, max_len;
	data_t acc, *data;

	max_len = vec_len(v);
	data = get_vec_start(v);
	acc = IDENT;

	for (i = 0; i < max_len; i++) {
		acc = acc OP data[i];
	}

	*dest = acc;
}
int main() {

}
