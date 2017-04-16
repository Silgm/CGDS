
#ifndef CGDS_ARRAYLIST_H
#define CGDS_ARRAYLIST_H




#include <cgds/cgds_tool.h>

#define CGDS_ARRAYLIST_DEFAULT_LEN		(16)
#define CGDS_GENERATE_ARRAYLIST_INC( name, type )\
typedef type name##Val;	\
typedef struct{\
	name##Val *data;\
	int length;\
	int _alloced;\
}name;\
\
int name##_new( name ** arraylist,int length );\
void name##_free( name *arraylist );\
int name##_insert( name *arraylist, int index, name##Val data);\
int name##_append( name *arraylist, name##Val data);\
int name##_prepend( name *arraylist, name##Val data);\
void name##_remove_range( name *arraylist, int index, int length);\
void name##_remove( name *arraylist, int index);\
void name##_clear(name *arraylist);\
name##Val name##_nth_data( name *arraylist, int index);\
int name##_index_of( name *arraylist, int (*PtFuncCompare)( name##Val, name##Val ) , name##Val data);\
void name##_sort( name *arraylist, int (*PtFuncCompare)( name##Val, name##Val ) );





	/*name of data , and type of data*/
#define CGDS_GENERATE_ARRAYLIST_SRC( name, type )\
int name##_new( name ** arraylist,int length )\
{\
	name *new_arraylist;\
	if(length <= 0) {\
		length = CGDS_ARRAYLIST_DEFAULT_LEN;\
	}\
	new_arraylist = (name *)malloc(sizeof(name));\
	if (!new_arraylist) {\
		return FAILURE;\
	}\
	new_arraylist->_alloced = length;\
	new_arraylist->length = 0;\
	new_arraylist->data = (name##Val *)malloc(sizeof(name##Val)*length);\
	if (new_arraylist->data == NULL) {\
		free(new_arraylist);\
		return FAILURE;\
	}\
	*arraylist = new_arraylist;\
	return SUCCESS;\
}\
\
void name##_free( name *arraylist )	\
{\
	if (arraylist != NULL) {\
		free(arraylist->data);\
		free(arraylist);\
	}\
}\
\
static int name##_enlarge( name *arraylist )\
{\
	name##Val *data;\
	int newsize;\
	newsize = arraylist->_alloced * 2;\
	data = realloc(arraylist->data, sizeof(name##Val) * newsize);\
	if (data == NULL) {\
		return FAILURE;\
	} else {\
		arraylist->data = data;\
		arraylist->_alloced = newsize;\
		return SUCCESS;\
	}\
}\
\
int name##_insert( name *arraylist, int index, name##Val data)\
{\
	if ( index < 0 || index > arraylist->length ) {\
		return FAILURE;\
	}\
	if ( arraylist->length + 1 > arraylist->_alloced && name##_enlarge(arraylist) ) {\
			return FAILURE; \
	}\
	memmove( &arraylist->data[index + 1], &arraylist->data[index], (arraylist->length - index) * sizeof(name##Val) ); \
	arraylist->data[index] = data;\
	++(arraylist->length);\
	return SUCCESS;\
}\
name##Val name##_nth_data( name *arraylist, int index)\
{\
	if ( index < 0 || index > arraylist->length ) {\
		return ((name##Val)(0));\
	}\
	return arraylist->data[index];\
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
int name##_index_of( name *arraylist, int (*PtFuncCompare)( name##Val, name##Val ) , name##Val data){\
	int i;\
	for (i = 0; i < arraylist->length; ++i) {\
		if ( !PtFuncCompare(arraylist->data[i], data))\
			return i;\
	}\
	return -1;\
}\
\
static void name##_sort_internal( name##Val *list_data, int list_length, int (*PtFuncCompare)( name##Val, name##Val ) ){\
	name##Val pivot, tmp;\
	int i, list1_length, list2_length;\
	if (list_length <= 1) {\
		return;\
	}\
	pivot = list_data[list_length-1];\
	list1_length = 0;\
	for (i=0; i<list_length-1; ++i) {\
		if (PtFuncCompare(list_data[i], pivot) < 0) {\
			tmp = list_data[i];\
			list_data[i] = list_data[list1_length];\
			list_data[list1_length] = tmp;\
			++list1_length; \
		}\
	}\
	list2_length = list_length - list1_length - 1;\
	list_data[list_length-1] = list_data[list1_length];\
	list_data[list1_length] = pivot;\
	name##_sort_internal(list_data, list1_length, PtFuncCompare);\
	name##_sort_internal(list_data + list1_length + 1 , list2_length, PtFuncCompare);\
}\
\
void name##_sort( name *arraylist, int (*PtFuncCompare)( name##Val, name##Val ) )\
{\
	name##_sort_internal(arraylist->data, arraylist->length, PtFuncCompare);\
}\

#endif

