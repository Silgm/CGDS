#include <tool.h>

#include "cgds_arraylist_test_inc.h"

#ifndef TEST_CGSD_ARRAYLIST

int compare(int a, int b) {
	return a - b;
}

double random() {
	static char isFirstTime = 1;
	if (isFirstTime) {
		isFirstTime = 0;
		srand((unsigned int)time(NULL));
		rand();
	}
	return ((double)(rand())) / (RAND_MAX + 1.0f);
}

int main() {
	ArrayListInt *alist;
	ArrayListInt_new(&alist, 20);
	int temp = 0;

	for (int loop = 0; loop < 10000000; loop++) {
		ArrayListInt_append(alist, (int)(random() * 10000000));
	}
	//for (int nIndex = 0; nIndex < alist->length; nIndex++) {
	//	printf("%d, ", ArrayListInt_nth_data(alist, nIndex));
	//}
	//puts("");

	printf("\n:%d\n", ArrayListInt_index_of(alist, compare, 5));

	ArrayListInt_sort(alist, compare);

	//for (int nIndex = 0; nIndex < alist->length; nIndex++) {
	//	printf("%d, ", ArrayListInt_nth_data(alist, nIndex));
	//}
	//puts("");

	ArrayListInt_free(alist);

	return EXIT_SUCCESS;
}



#endif



