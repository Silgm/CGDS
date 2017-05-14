#ifndef CGDS_STACK_H_
#define CGDS_STACK_H_

#include <cgds/cgds_tool.h>

#define CGDS_STACK_DEFAULT_LEN	16

#define CGDS_GENERATE_STACK_INC(name, type)\
typedef type name##Val;\
typedef struct \
{\
	name##Val *data;\
	int length;\
	int _alloced;\
}name;\
int name##_new( name ** stack, int length);\
void name##_free( name *stack );\
int name##_push( name * stack, name##Val val );\
name##Val name##_pop( name * stack );\
name##Val name##_top( name * stack);\
int name##_length( name * stack );


#define CGDS_GENERATE_STACK_SRC(name, type)\
int name##_new( name ** stack, int length){\
	name *new_stack;\
	if (length <= 0){\
		length = CGDS_STACK_DEFAULT_LEN;\
	}\
	new_stack = (name *)malloc(sizeof(name));\
	if (!new_stack) {\
		return FAILURE;\
	}\
	new_stack->_alloced = length;\
	new_stack->length = 0;\
	new_stack->data = (name##Val *)malloc(sizeof(name##Val)*length);\
	*stack = new_stack;\
	return SUCCESS;\
}\
\
void name##_free( name *stack )	\
{\
	if (stack != NULL) {\
		free(stack->data);\
		free(stack);\
	}\
}\
static int name##_enlarge( name * stack )\
{\
	name##Val *data;\
	int newsize;\
	newsize = stack->_alloced * 2;\
	data = realloc(stack->data, sizeof(name##Val) * newsize);\
	if (data == NULL) {\
		return FAILURE;\
	} else {\
		stack->data = data;\
		stack->_alloced = newsize;\
		return SUCCESS;\
	}\
}\
int name##_push( name * stack, name##Val val ){\
	if ( stack->length + 1 > stack->_alloced && name##_enlarge(stack) ){\
		return FAILURE;\
	}\
	stack->data[stack->length] = val;\
	++(stack->length);\
	return SUCCESS;\
}\
\
name##Val name##_pop( name * stack ){\
	if (stack->length)\
		return stack->data[--(stack->length)];\
	return ((name##Val)(0));\
}\
\
name##Val name##_top( name * stack){\
	if (stack->length)\
		return stack->data[stack->length - 1];\
	return ((name##Val)(0));\
}\
\
int name##_length( name * stack ){\
	return stack->length;\
}

#endif

