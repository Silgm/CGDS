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
name##Entry *name##_append( name##Head list, name##Val data){\
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

#endif



