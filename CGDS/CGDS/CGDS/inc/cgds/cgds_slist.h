#ifndef CGDS_SLIST_H_
#define CGDS_SLIST_H_

#include "cgds/cgds_tool.h"
#include <limits.h>

#define SLIST_NULL ((void *) 0)

#define CGDS_GENERATE_SINGLELIST_INC( name, type )\
typedef type name##Val;\
typedef struct _##name##Entry{\
	name##Val data;\
	struct _##name##Entry *next;\
}name##Entry, * name##Head;\
\
void name##_free( name##Head list );\
int name##_initHead( name##Head *list );\
void name##_clearHead( name##Head *list);\
name##Entry * name##_prepend( name##Head list, name##Val data );\
name##Entry * name##_append( name##Head list, name##Val data );\
name##Entry * name##_insert( name##Head list, name##Val data, unsigned long index);\
name##Entry * name##_nth_entry( name##Head list, unsigned long n );\
name##Val name##_nth_data( name##Head list, unsigned long n);\
unsigned long name##_length( name##Head list);\
int name##_to_array( name##Head list, name##Val *buff, unsigned long buffLen);\
int name##_remove_entry( name##Head list, name##Entry *entry);\
int name##_remove_nth( name##Head list, unsigned long index);\
void name##_rev( name##Head list );\
int name##_remove_data( name##Head list, int (*PtFuncCompare)( name##Val, name##Val ), name##Val data);\
name##Entry *name##_find_entry_with_data( name##Head list, int (*PtFuncCompare)( name##Val, name##Val ), name##Val data );\
unsigned long name##_find_index_with_data( name##Head list, int (*PtFuncCompare)( name##Val, name##Val ), name##Val data );\
void name##_sort(name##Head list, int(*PtFuncCompare)(name##Val, name##Val));\


#define CGDS_GENERATE_SINGLELIST_SRC( name, type )\
void name##_free( name##Head list )\
{\
	name##Entry *entry = list->next;\
	name##Entry *next;\
	while (entry != NULL) {\
		next = entry->next;\
		free(entry);\
		entry = next;\
	}\
	list->next = NULL;\
}\
\
int name##_initHead( name##Head *list )\
{\
	*list = (name##Entry *)malloc(sizeof(name##Entry));\
	if (*list == NULL){\
		return EXIT_FAILURE;\
	}\
	(*list)->data = (name##Val)( 0 );\
	(*list)->next = NULL;\
	return EXIT_SUCCESS;\
}\
\
void name##_clearHead( name##Head *list)\
{\
	if (*list != NULL){\
		free(*list);\
	}\
}\
\
name##Entry * name##_prepend( name##Head list, name##Val data )\
{\
	name##Entry *newentry;\
	newentry = (name##Entry *)malloc(sizeof(name##Entry));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	newentry->data = data;\
	newentry->next = list->next;\
	list->next = newentry;\
	return newentry;\
}\
\
name##Entry * name##_append( name##Head list, name##Val data )\
{\
	name##Entry *rover;\
	name##Entry *newentry;\
	newentry = (name##Entry *)malloc(sizeof(name##Entry));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	newentry->data = data;\
	newentry->next = NULL;\
	for (rover = list; rover->next != NULL; rover = rover->next);\
	rover->next = newentry;\
	return newentry;\
}\
name##Entry * name##_insert( name##Head list, name##Val data, unsigned long index)\
{\
	name##Entry *rover, *tmp;\
	name##Entry *newentry;\
	unsigned long i;\
	newentry = (name##Entry *)malloc(sizeof(name##Entry));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	newentry->data = data;\
	for (rover = list, i = 0; rover->next != NULL && i < index; ++i, rover = rover->next);\
	tmp = rover->next;\
	rover->next = newentry;\
	newentry->next = tmp;\
	return newentry;\
}\
\
name##Entry * name##_nth_entry( name##Head list, unsigned long n )\
{\
	name##Entry *entry;\
	unsigned long i;\
	entry = list->next;\
	for (i = 0; i < n; ++i) {\
		if (entry == NULL) {\
			return NULL;\
		}\
		entry = entry->next;\
	}\
	return entry;\
}\
\
name##Val name##_nth_data( name##Head list, unsigned long n)\
{\
	name##Entry *entry;\
	entry = name##_nth_entry(list, n);\
	if (entry == NULL) {\
		return ((name##Val) 0 );\
	}\
	else {\
		return entry->data;\
	}\
}\
\
unsigned long name##_length( name##Head list)\
{\
	name##Entry *entry = list->next;;\
	unsigned long length = 0;\
	for (;entry != NULL; ++length, entry = entry->next);\
	return length;\
}\
\
int name##_to_array( name##Head list, name##Val *buff, unsigned long buffLen)\
{\
	name##Entry *rover = NULL;\
	unsigned int length = 0;\
	unsigned int i = 0;\
	if (buff == NULL) {\
		return EXIT_FAILURE;\
	}\
	for (rover = list, i = 0; rover->next && i < buffLen; ++i) {\
		buff[i] = rover->next->data;\
		rover = rover->next;\
	}\
	return EXIT_SUCCESS;\
}\
int name##_remove_entry( name##Head list, name##Entry *entry)\
{\
	name##Entry *rover;\
	if (list->next == NULL || entry == NULL) {\
		return EXIT_FAILURE;\
	}\
	for(rover = list; rover->next != entry; rover = rover->next);\
	rover->next = rover->next->next;\
	free(entry);\
	return EXIT_SUCCESS;\
}\
\
int name##_remove_nth( name##Head list, unsigned long index)\
{\
	return name##_remove_entry( list , name##_nth_entry( list, index ));\
}\
\
void name##_rev( name##Head list )\
{\
	name##Entry *thisNode = list->next, *nextNode = NULL;\
	if (thisNode) {\
		nextNode = list->next->next;\
		list->next = NULL;\
	}\
	else {\
		return;\
	}\
	for (; nextNode; thisNode = nextNode, nextNode = nextNode->next) {\
		thisNode->next = list->next;\
		list->next = thisNode;\
	}\
	thisNode->next = list->next;\
	list->next = thisNode; \
}\
\
int name##_remove_data( name##Head list, int (*PtFuncCompare)( name##Val, name##Val ), name##Val data){\
	name##Entry *it = list, *delEntry = NULL;\
	int counter = 0;\
	while (it->next){\
		if (!PtFuncCompare(it->next->data, data)){\
			delEntry = it->next;\
			it->next = it->next->next;\
			free(delEntry);\
			counter++;\
		}\
		else{\
			it = it->next;\
		}\
	}\
	return counter;\
}\
\
name##Entry *name##_find_entry_with_data( name##Head list, int (*PtFuncCompare)( name##Val, name##Val ), name##Val data ){\
	name##Entry *it;\
	for (it = list; it->next; it = it->next) {\
		if (!PtFuncCompare(it->next->data, data)) {\
			return it->next;\
		}\
	}\
	return NULL;\
}\
\
unsigned long name##_find_index_with_data( name##Head list, int (*PtFuncCompare)( name##Val, name##Val ), name##Val data ){\
	name##Entry *it;\
	unsigned long index = 0;\
	for (it = list; it->next; it = it->next, index++) {\
		if (!PtFuncCompare(it->next->data, data)) {\
			return index;\
		}\
	}\
	return ULONG_MAX;\
}\
\
static name##Entry *name##_sort_internal_noHead( name##Entry **list, int (*PtFuncCompare)( name##Val, name##Val ) ) {\
	name##Entry *pivot;\
	name##Entry *rover;\
	name##Entry *less_list, *more_list;\
	name##Entry *less_list_end, *more_list_end;\
	if (*list == NULL || (*list)->next == NULL) {\
		return *list;\
	}\
	pivot = *list;\
	less_list = NULL;\
	more_list = NULL;\
	rover = (*list)->next;\
	while (rover != NULL) {\
		name##Entry *next = rover->next;\
		if (PtFuncCompare(rover->data, pivot->data) < 0) {\
			rover->next = less_list;\
			less_list = rover;\
		}\
		else {\
			rover->next = more_list;\
			more_list = rover;\
		}\
		rover = next;\
	}\
	less_list_end = name##_sort_internal_noHead(&less_list, PtFuncCompare);\
	more_list_end = name##_sort_internal_noHead(&more_list, PtFuncCompare);\
	*list = less_list;\
	if (less_list == NULL) {\
		*list = pivot;\
	}\
	else {\
		less_list_end->next = pivot;\
	}\
	pivot->next = more_list;\
	if (more_list == NULL) {\
		return pivot;\
	}\
	else {\
		return more_list_end;\
	}\
}\
\
void name##_sort( name##Head list, int (*PtFuncCompare)( name##Val, name##Val ))\
{\
	name##Entry **nlist = &(list->next);\
	name##_sort_internal_noHead( nlist, PtFuncCompare);\
	list->next = *nlist;\
}\


#endif // CGDS_SLIST_H

