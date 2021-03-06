#ifndef CGDS_TOOL_H
#define CGDS_TOOL_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

#define MF_MALLOC_LEN(_type, _len)	( (_type *)malloc(sizeof(_type) * (_len) ) )
#define MF_MALLOC(_type)			( (_type *)malloc(sizeof(_type) ) ) 
#define MF_ARR_LEN(_arr)			( sizeof((_arr))/sizeof(((_arr)[0])) )

#define FAILURE		1
#define SUCCESS		0

#define YES			1
#define NO			0
#ifdef __cplusplus
}
#endif





#endif