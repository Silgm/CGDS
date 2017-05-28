#ifndef CGDS_LIST_H_
#define CGDS_LIST_H_

#include "cgds_tool.h"


#define CGDS_GENERATE_LIST_INC(name ,type) \
typedef type name##Val;\
typedef struct _##name##Entry{\
	name##Val data;\
	struct _##name##Entry *prev;\
	struct _##name##Entry *next;\
}name##Entry, *name##Head;\
\
int name##_initHead( name##Head *list);\
void name##_clearHead( name##Head *list);\
void name##_free( name##Head list);\
name##Entry *name##_prepend( name##Head list, name##Val data);\
name##Entry *name##_append( name##Head list, name##Val data );\
name##Entry *name##_insert( name##Head list, name##Val data , long pos);\
name##Entry *name##_nth_entry( name##Head list, long n);\
name##Val name##_nth_data( name##Head list, long n);\
long name##_length(  name##Head list );\
int name##_remove_nth(name##Head list, long index);\
int name##_remove_entry(name##Head list, name##Entry *entry);\
int name##_rev(name##Head list);\
void name##_sort( name##Head list, int pfun_comparefunction( name##Val, name##Val ) );



#define CGDS_GENERATE_LIST_SRC(name ,type) \
int name##_initHead( name##Head *list) {\
	*list = ( name##Entry * )(malloc(sizeof(name##Entry)));\
	name##Val errorVal;\
	memset(&errorVal, 0, sizeof(errorVal));\
	if (*list == NULL){\
		return 1;\
	}\
	(*list)->data = errorVal;\
	(*list)->next = NULL;\
	(*list)->prev = NULL;\
	return 0;\
}\
\
void name##_clearHead( name##Head *list) {\
	if (*list != NULL){\
		free(*list);\
	}\
	*list = NULL;\
}\
\
void name##_free( name##Head list) {\
	name##Entry *entry = list->next;\
	name##Entry *next;\
	while (entry != NULL) {\
		next = entry->next; \
		free(entry);\
		entry = next;\
	}\
}\
\
name##Entry *name##_prepend( name##Head list, name##Val data) {\
	name##Entry *newentry;\
	name##Entry *secondentry;\
	if (list == NULL){\
		return NULL;\
	}\
	newentry = (name##Entry * )(malloc( sizeof(name##Entry) ));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	newentry->data = data;\
	newentry->prev = NULL;\
	newentry->next = NULL;\
	if (list->next != NULL) {\
		secondentry = list->next;\
		list->next = newentry;\
		newentry->next = secondentry;\
		secondentry->prev = newentry;\
	}\
	else{\
		list->next = newentry;\
	}\
	return newentry;\
}\
\
name##Entry *name##_append( name##Head list, name##Val data ) {\
	name##Entry *newentry = NULL;\
	name##Entry *rover = NULL;\
	if (list == NULL){\
		return NULL;\
	}\
	newentry = (name##Entry * )(malloc( sizeof(name##Entry) ));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	newentry->data = data;\
	newentry->prev = NULL;\
	newentry->next = NULL;\
	for (rover = list; rover->next; rover = rover->next);\
	if (list->next != NULL)\
		newentry->prev = rover;\
	rover->next = newentry;\
	return newentry;\
}\
\
name##Entry *name##_insert( name##Head list, name##Val data , long pos)\
{\
	name##Entry *entry = list->next;\
	name##Entry *newentry = (name##Entry *)(malloc(sizeof(name##Entry)));\
	long index;\
	if (list == NULL){\
		return NULL;\
	}\
	newentry->data = data;\
	for (index = 0; index < pos && entry->next; index++, entry = entry->next);\
	if( pos - index == 1){\
		newentry->next = NULL;\
		entry->next = newentry;\
		newentry->prev = entry;\
		return newentry;\
	}\
	else if (index == pos){\
		newentry->prev = entry->prev;\
		newentry->next = entry;\
		if(entry->prev)\
			entry->prev->next = newentry;\
		else\
			list->next = newentry;\
		entry->prev = newentry;\
	}\
	else {\
		free(newentry);\
		return NULL;\
	}\
	return newentry;\
}\
\
name##Entry *name##_nth_entry( name##Head list, long n)\
{\
	name##Entry *entry = list->next;\
	long index;\
	if (list == NULL){\
		return NULL;\
	}\
	for (index = 0; index < n; index++){\
		if (!entry)\
			return NULL;\
		entry = entry->next;\
	}\
	return entry; \
}\
\
name##Val name##_nth_data( name##Head list, long n)\
{\
	name##Entry *entry = list->next;\
	name##Val errorVal;\
	memset(&errorVal, 0, sizeof(errorVal));\
	long index;\
	for (index = 0; index < n; index++){\
		if (!entry)\
			return errorVal;\
		entry = entry->next;\
	}\
	return entry->data; \
}\
\
long name##_length( name##Head list )\
{\
	name##Entry *entry = list->next;\
	long length;\
	for(length = 0; entry; entry = entry->next, length++);\
	return length;\
}\
\
int name##_remove_nth(name##Head list, long index) {\
	name##Entry *entry = name##_nth_entry(list, index);\
	if (entry == NULL){\
		return FAILURE;\
	}\
	if (entry->prev != NULL){\
		entry->prev->next = entry->next;\
		if (entry->next != NULL)\
			entry->next->prev = entry->prev;\
	}\
	else {\
		list->next = entry->next;\
		list->next->prev = NULL;\
	}\
	free(entry); \
	return SUCCESS;\
}\
\
int name##_remove_entry( name##Head list, name##Entry *entry ){\
	if (list == NULL || entry == NULL){\
		return FAILURE;\
	}\
	if (entry->prev != NULL){\
		entry->prev->next = entry->next;\
		if (entry->next != NULL)\
			entry->next->prev = entry->prev;\
	}\
	else {\
		list->next = entry->next;\
		list->next->prev = NULL;\
	}\
	free(entry);\
	return SUCCESS;\
}\
\
int name##_rev( name##Head list) {\
	name##Entry *it, *itNext, *exChangeTemp;\
	if (list == NULL){\
		return FAILURE;\
	}\
	if (list->next == NULL){\
		return SUCCESS;\
	}\
	it = list->next;\
	itNext = it->next;\
	while (itNext != NULL){\
		exChangeTemp = it->next;\
		it->next = it->prev;\
		it->prev = exChangeTemp;\
		it = itNext;\
		itNext = itNext->next;\
	}\
	exChangeTemp = it->next;\
	it->next = it->prev;\
	it->prev = exChangeTemp;\
	list->next = it;\
	return SUCCESS;\
}\
\
static name##Entry * name##_sort_internal( name##Entry **list, int pfun_comparefunction( name##Val, name##Val) ) {\
	name##Entry *pivot;\
	name##Entry *rover;\
	name##Entry *less_list, *more_list;\
	name##Entry *less_list_end, *more_list_end;\
	name##Entry *next;\
	if (list == NULL || pfun_comparefunction == NULL) {\
		return NULL;\
	}\
	if (*list == NULL || (*list)->next == NULL) {\
		return *list;\
	}\
	pivot = *list;\
	less_list = NULL;\
	more_list = NULL;\
	rover = (*list)->next;\
	while (rover != NULL) {\
		next = rover->next;\
		if (pfun_comparefunction(rover->data, pivot->data) < 0) {\
			rover->prev = NULL;\
			rover->next = less_list;\
			if (less_list != NULL) {\
				less_list->prev = rover;\
			}\
			less_list = rover;\
		}\
		else {\
			rover->prev = NULL;\
			rover->next = more_list;\
			if (more_list != NULL) {\
				more_list->prev = rover;\
			}\
			more_list = rover;\
		}\
		rover = next;\
	}\
	less_list_end = name##_sort_internal(&less_list, pfun_comparefunction);\
	more_list_end = name##_sort_internal(&more_list, pfun_comparefunction);\
	*list = less_list;\
	if (less_list == NULL) {\
		pivot->prev = NULL;\
		*list = pivot;\
	}\
	else {\
		pivot->prev = less_list_end;\
		less_list_end->next = pivot;\
	}\
	pivot->next = more_list;\
	if (more_list != NULL) {\
		more_list->prev = pivot;\
	}\
	if (more_list == NULL) {\
		return pivot;\
	}\
	else {\
		return more_list_end;\
	}\
}\
void name##_sort( name##Head list, int pfun_comparefunction( name##Val, name##Val ) )\
{\
	name##_sort_internal( &(list->next), pfun_comparefunction);\
}

#endif



