#include "tool.h"
#include "cgds/cgds_slist.h"


#ifndef TEST_CGSD_SLIST


CGDS_GENERATE_SINGLELIST(SListInt, int)



int main()
{
	SListIntHead slisthead;
	SListIntEntry *it;
	int arr[16] = {0};
	SListInt_InitHead(&slisthead);
	SListInt_append(&slisthead, 10);
	SListInt_append(&slisthead, 20);
	SListInt_append(&slisthead, 30);
	SListInt_append(&slisthead, 40);
	SListInt_append(&slisthead, 50);
	SListInt_insert(&slisthead, 50000, 2);
	for (it = slisthead->next; it; it = it->next)
	{
		printf("%d->", it->data);
	}
	puts("");

	it = SListInt_nth_entry(&slisthead, 1);
	SListInt_remove_entry(&slisthead, it);
	for (it = slisthead->next; it; it = it->next)
	{
		printf("%d->", it->data);
	}
	puts("");
	printf("%d\n", SListInt_nth_data(&slisthead, 1));
	printf("Len:%d\n", SListInt_length(&slisthead));

	SListInt_to_array(&slisthead, arr, ( sizeof(arr)/sizeof(arr[0]) ) );

	SListInt_free(&slisthead);
	SListInt_ClearHead(&slisthead);
	return EXIT_SUCCESS;
}



#endif

