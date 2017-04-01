#ifndef CGDS_SLIST_H_
#define CGDS_SLIST_H_

#include "cgds/cgds_tool.h"

#define SLIST_NULL ((void *) 0)

#define CGDS_GENERATE_SINGLELIST( name, type )\
typedef type name##Val;\
typedef struct _##name##Entry{\
	name##Val data;\
	struct _##name##Entry *next;\
}name##Entry, *name##Head;\
\
void name##_free( const name##Head *list)\
{\
	name##Entry *entry = (*list)->next;\
	name##Entry *next;\
	while (entry != NULL) {\
		next = entry->next;\
		free(entry);\
		entry = next;\
	}\
	(*list)->next = NULL;\
}\
\
int name##_InitHead( name##Head *list)\
{\
	*list = (name##Entry *)malloc(sizeof(name##Entry));\
	if (*list == NULL){\
		return 1;\
	}\
	(*list)->data = (name##Val)( 0 );\
	(*list)->next = NULL;\
	return 0;\
}\
\
void name##_ClearHead( name##Head *list)\
{\
	if (*list != NULL){\
		free(*list);\
	}\
}\
\
name##Entry * name##_prepend( const name##Head *list, name##Val data)\
{\
	name##Entry *newentry;\
	newentry = (name##Entry *)malloc(sizeof(name##Entry));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	if ((*list)->next == NULL) {\
		newentry->data = data;\
		newentry->next = NULL;\
		(*list)->next = newentry;\
	}else {\
		newentry->data = data;\
		newentry->next = (*list)->next;\
		(*list)->next = newentry;\
		newentry->next->next = NULL;\
	}\
	return newentry;\
}\
\
name##Entry * name##_append( const name##Head *list, name##Val data)\
{\
	name##Entry *rover;\
	name##Entry *newentry;\
	newentry = (name##Entry *)malloc(sizeof(name##Entry));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	newentry->data = data;\
	newentry->next = NULL;\
	for (rover = *list; rover->next != NULL; rover = rover->next);\
	rover->next = newentry;\
	return newentry;\
}\
name##Entry * name##_insert( const name##Head *list, name##Val data, unsigned long index)\
{\
	name##Entry *rover, *tmp;\
	name##Entry *newentry;\
	unsigned long i;\
	newentry = (name##Entry *)malloc(sizeof(name##Entry));\
	if (newentry == NULL) {\
		return NULL;\
	}\
	newentry->data = data;\
	for (rover = *list, i = 0; rover->next != NULL && i < index; ++i, rover = rover->next);\
	tmp = rover->next;\
	rover->next = newentry;\
	newentry->next = tmp;\
	return newentry;\
}\
\
name##Entry * name##_nth_entry( const name##Head *list, unsigned int n)\
{\
	name##Entry *entry;\
	unsigned int i;\
	entry = (*list)->next;\
	for (i = 0; i<n; ++i) {\
		if (entry == NULL) {\
			return NULL;\
		}\
		entry = entry->next;\
	}\
	return entry;\
}\
\
name##Val name##_nth_data( const name##Head *list, unsigned int n)\
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
unsigned long name##_length( const name##Head *list)\
{\
	name##Entry *entry = (*list)->next;;\
	unsigned long length = 0;\
	for (;entry != NULL; ++length, entry = entry->next);\
	return length;\
}\
\
int name##_to_array( const name##Head *list, name##Val *buff, unsigned long buffLen)\
{\
	name##Entry *rover = NULL;\
	unsigned int length = 0;\
	unsigned int i = 0;\
	length = name##_length(list);\
	if (buff == NULL) {\
		return 1;\
	}\
	for (rover = (*list)->next, i = 0; i < length && i < buffLen; ++i) {\
		buff[i] = rover->data;\
		rover = rover->next;\
	}\
	return 0;\
}\
int name##_remove_entry( const name##Head *list, name##Entry *entry)\
{\
	name##Entry *rover;\
	if ((*list)->next == NULL || entry == NULL) {\
		return 0;\
	}\
	if ((*list)->next  == entry) {\
		(*list)->next  = entry->next;\
	}\
	else {\
		rover = (*list)->next ;\
		while (rover != NULL && rover->next != entry) {\
			rover = rover->next;\
		}\
		if (rover == NULL) {\
			return 0;\
		}\
		else {\
			rover->next = entry->next;\
		}\
	}\
	free(entry);\
	return 1;\
}

#endif // CGDS_SLIST_H

