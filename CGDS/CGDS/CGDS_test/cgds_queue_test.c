#include <tool.h>
#include <cgds_queue_test_inc.h>


#ifndef TEST_CGDS_QUEUE

#define  MAN_NUM	42

int main() {
	IntQueue *queue = NULL;
	IntQueue_new(&queue);
	
	for (int index = 1; index < MAN_NUM; index++) {
		IntQueue_en(queue, index);
	}


	for (int cnt = 1; !IntQueue_isEmpty(queue); cnt++) {
		if (cnt % 3 == 0) {
			printf("%d,",IntQueue_de(queue));
		}
		else {
			IntQueue_en(queue, IntQueue_de(queue));
		}
	}

	printf("\n");
	IntQueue_free(&queue);

	return EXIT_SUCCESS;
}

#endif
