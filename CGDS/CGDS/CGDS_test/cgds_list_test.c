#include "cgds/cgds_list.h"
#include "tool.h"

#ifndef TEST_CGSD_LIST

int main

//CGDS_GENERATE_LIST(ListString, char*)

//int main() {
//	ListIntHead list1 = NULL;
//	ListInt_initHead(&list1);
//
//	ListInt_prepend(list1, 10);
//	ListInt_prepend(list1, 20);
//	ListInt_prepend(list1, 30);
//	ListInt_prepend(list1, 40);
//	ListInt_prepend(list1, 50);
//
//	for (ListIntEntry *it = list1->next; it; it = it->next) {
//		printf("%d<=>", it->data);
//	}
//	puts("");
//	ListInt_insert(list1, 5000, 5);
//
//	for (ListIntEntry *it = list1->next; it; it = it->next) {
//		printf("%d<=>", it->data);
//	}
//	printf("\n>>Length:%d.\n", ListInt_length(list1));
//
//	ListInt_free(list1);
//	ListInt_clearHead(&list1);
//}

//int main() {
//	ListIntHead list1 = NULL;
//	ListStringHead listStr1 = NULL;
//
//	ListString_initHead(&listStr1);
//	ListInt_initHead(&list1);
//	
//	ListString_prepend(listStr1, "Good");
//	ListString_prepend(listStr1, "Hello");
//	ListString_prepend(listStr1, "world");
//
//	ListInt_append(list1, 10);
//	ListInt_append(list1, 20);
//	ListInt_append(list1, 30);
//
//	printf("%d<=>", list1->next->data);
//	printf("%d<=>", list1->next->next->data);
//	printf("%d<=>", list1->next->next->next->data);
//
//	printf("\n");
//
//	printf("%d<=>", list1->next->next->next->prev->prev->data);
//	printf("%d<=>", list1->next->next->next->prev->data);
//	printf("%d<=>", list1->next->next->next->data);
//
//	printf("\n");
//	printf("%p", list1->next->next->next->prev->prev->prev);
//
//	printf("\n\n");
//
//	printf("%s<=>", listStr1->next->data);
//	printf("%s<=>", listStr1->next->next->data);
//	printf("%s<=>", listStr1->next->next->next->data);
//
//	printf("\n");
//
//	printf("%s<=>", listStr1->next->next->next->prev->prev->data);
//	printf("%s<=>", listStr1->next->next->next->prev->data);
//	printf("%s<=>", listStr1->next->next->next->data);
//
//	printf("\n");
//	printf("%p", listStr1->next->next->next->prev->prev->prev);
//
//	printf("\n");
//
//	ListInt_free(list1);
//	ListString_free(listStr1);
//
//	ListString_clearHead(&listStr1);
//	ListInt_clearHead(&list1);
//
//	return EXIT_SUCCESS;
//}
#endif
