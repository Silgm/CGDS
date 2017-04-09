#ifndef CGDS_MDARRAY_H_
#define CGDS_MDARRAY_H_

#include <stdlib.h>

#define CGDS_GENERATE_MALLOC_2D_ARR(type)\
typedef type __type;\
__type **malloc_2d_arr_##type( size_t row, size_t col){\
	__type **arr = NULL;\
	__type *buf = NULL;\
	arr = (type **)malloc(sizeof(type *) * row);\
	buf = (type *)malloc(sizeof(type) * row * col);\
	for ( size_t i = 0; i < row; ++i) {\
		arr[i] = &(buf[col * i]);\
	}\
	return arr;\
}\
void free_2d_arr_##type( __type ** arr ){\
	free(*arr);\
	free(arr);\
}



#endif
