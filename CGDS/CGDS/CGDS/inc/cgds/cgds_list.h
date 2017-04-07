#ifndef CGDS_LIST_H_
#define CGDS_LIST_H_

#include "cgds/cgds_tool.h"


#define CGDS_GENERATE_LIST(name ,type) \
typedef type name##Val;\
typedef struct _##name##Entry{\
	name##Val data;\
	struct _##name##Entry *prev;\
	struct _##name##Entry *next;\
}name##Entry, *name##Head;\
int name##_initHead( name##Head *list){\
	*list = ( name##Entry * )(malloc(sizeof(name##Entry)));\
	if (*list == NULL){\
		return 1;\
	}\
	(*list)->data = (name##Val)( 0 );\
	(*list)->next = NULL;\
	(*list)->prev = NULL;\
	return 0;\
}\
\
void name##_clearHead( name##Head *list)\
{\
	if (*list != NULL){\
		free(*list);\
	}\
	*list = NULL;\
}\
\
void name##_free( name##Head list){\
	name##Entry *entry = list->next;\
	name##Entry *next;\
	while (entry != NULL) {\
		next = entry->next; \
		free(entry);\
		entry = next;\
	}\
}\
\
name##Entry *name##_prepend( name##Head list, name##Val data){\
	name##Entry *newentry;\
	name##Entry *secondentry;\
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
name##Entry *name##_append( name##Head list, name##Val data ){\
	name##Entry *newentry = NULL;\
	name##Entry *rover = NULL;\
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
name##Entry *name##_insert( name##Head list, name##Val data , unsigned long pos)\
{\
	name##Entry *entry = list->next;\
	name##Entry *newentry = (name##Entry *)(malloc(sizeof(name##Entry)));\
	unsigned long index;\
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
name##Entry *name##_nth_entry( name##Head list, unsigned long n)\
{\
	name##Entry *entry = list->next;\
	unsigned long index;\
	for (index = 0; index < n; index++){\
		if (!entry)\
			return NULL;\
		entry = entry->next;\
	}\
	return entry; \
}\
\
name##Val name##_nth_data( name##Head list, unsigned long n)\
{\
	name##Entry *entry = list->next;\
	unsigned long index;\
	for (index = 0; index < n; index++){\
		if (!entry)\
			return (name##Val)(0);\
		entry = entry->next;\
	}\
	return entry->data; \
}\
\
unsigned long name##_length(  name##Head list )\
{\
	name##Entry *entry = list->next;\
	unsigned long length;\
	for(length = 0; entry; entry = entry->next, length++);\
	return length;\
}\
//ListEntry *list_nth_entry(ListEntry *list, int n)
//{
//ListEntry *entry;
//int i;
//
///* Negative values are always out of range */
//
//if (n < 0) {
//	return NULL;
//}
//
///* Iterate through n list entries to reach the desired entry.
//* Make sure we do not reach the end of the list. */
//
//entry = list;
//
//for (i = 0; i<n; ++i) {
//
//	if (entry == NULL) {
//		return NULL;
//	}
//	entry = entry->next;
//}
//
//return entry;
#endif



