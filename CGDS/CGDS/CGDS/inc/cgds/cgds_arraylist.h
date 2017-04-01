
#ifndef CGDS_ARRAYLIST_H
#define CGDS_ARRAYLIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include <cgds/cgds_tool.h>

#define CGDS_ARRAYLIST_DEFAULT_LEN		(16)


	/*name of data , and type of data*/
#define CGDS_GENERATE_ARRAYLIST( name, type )								\
typedef type name##Val;														\
typedef struct{																\
	name##Val *data;														\
	int length;																\
	int _alloced;															\
}name;																		\
																			\
name * name##_new( int length )												\
{																			\
	name *new_arraylist;													\
	if(length <= 0) {														\
		length = CGDS_ARRAYLIST_DEFAULT_LEN;								\
	}																		\
	new_arraylist = MF_MALLOC(name);										\
	if (!new_arraylist) {													\
		return NULL;														\
	}																		\
	new_arraylist->_alloced = length;										\
	new_arraylist->length = 0;												\
																			\
	new_arraylist->data = MF_MALLOC_LEN(name##Val, length);					\
																			\
	if (new_arraylist->data == NULL) {										\
		free(new_arraylist);												\
		return NULL;														\
	}																		\
																			\
	return new_arraylist;													\
}																			\
																			\
void name##_free( name *arraylist )											\
{																			\
	if (arraylist != NULL) {												\
		free(arraylist->data);												\
		free(arraylist);													\
	}																		\
}																			\
																			\
static int name##_enlarge( name *arraylist )\
{\
	name##Val *data;\
	int newsize;\
	newsize = arraylist->_alloced * 2;\
	data = realloc(arraylist->data, sizeof(name##Val) * newsize);\
	if (data == NULL) {\
		return 0;\
	} else {\
		arraylist->data = data;\
		arraylist->_alloced = newsize;\
		return 1;\
	}\
}\
\
int name##_insert( name *arraylist, int index, name##Val data)\
{\
	if ( index < 0 || index > arraylist->length ) {\
		return 0;\
	}\
	if ( arraylist->length + 1 > arraylist->_alloced && !(name##_enlarge)(arraylist) ) {\
			return 0; \
	}\
	memmove( &arraylist->data[index + 1], &arraylist->data[index], (arraylist->length - index) * sizeof(name##Val) ); \
	arraylist->data[index] = data;\
	++(arraylist->length);\
	return 1;\
}\
\
int name##_append( name *arraylist, name##Val data)\
{\
	return name##_insert(arraylist, arraylist->length, data);\
}\
\
int name##_prepend( name *arraylist, name##Val data)\
{\
	return name##_insert(arraylist, 0, data);\
}\
\
void name##_remove_range( name *arraylist, int index, int length)\
{\
	if (index < 0 || length < 0 || index + length > arraylist->length) {\
		return;\
	}\
	memmove(&arraylist->data[index], &arraylist->data[index + length], (arraylist->length - (index + length)) * sizeof(name##Val));\
	arraylist->length -= length;\
}\
\
void name##_remove( name *arraylist, int index)\
{\
	name##_remove_range( arraylist, index, 1);\
}\
\
void name##_clear(name *arraylist)\
{\
	arraylist->length = 0;\
}\



#ifdef __cplusplus
}
#endif





#endif
