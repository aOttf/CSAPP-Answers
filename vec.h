/*
 * vec.h
 *
 *  Created on: May 27, 2021
 *      Author: Wang Jingyu
 */

#ifndef VEC_H_
#define VEC_H_

typedef long data_t;
typedef struct {
	long len;
	data_t *data;
} vec_rec, *vec_ptr;


#define OP +
#define IDENT 0
#endif /* VEC_H_ */
