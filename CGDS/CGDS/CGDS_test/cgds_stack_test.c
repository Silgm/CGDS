#include <tool.h>
#include "cgds_stack_test_inc.h"


#ifndef TEST_CGDS_STACK

int main() {
	DoubleStack *myStack;
	
	DoubleStack_new(&myStack, 30);
	DoubleStack_push(myStack, 1);
	DoubleStack_push(myStack, 2);
	DoubleStack_push(myStack, 3);
	DoubleStack_push(myStack, 4);
	DoubleStack_push(myStack, 5);
	DoubleStack_push(myStack, 6);

	while (DoubleStack_length(myStack))
		printf("%f\t", DoubleStack_pop(myStack));
	puts("");

	DoubleStack_free(myStack);
	
	return EXIT_SUCCESS;
}



#endif


