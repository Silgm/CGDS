#include "tool.h"
#include "cgds/cgds_slist.h"


#ifndef TEST_CGSD_SLIST


CGDS_GENERATE_SINGLELIST(SListInt, int)


int isIntersection(SListIntHead list1, SListIntHead list2)
{
	SListIntEntry *it1 = list1->next, *it2 = list2->next;
	int nCount = 0;
	while (it1 || it2)
	{
		(it1) && (it1 = it1->next, nCount++);
		(it2) && (it2 = it2->next, nCount--);
	}

	it1 = list1->next;
	it2 = list2->next;

	if (nCount > 0)
	{	//list1³¤,list2¶Ì
		for (; nCount > 0; nCount--, it1 = it1->next);
		for (; it1 && it2 && it1 != it2; it1 = it1->next, it2 = it2->next);
		if (it1 != NULL && it2 != NULL)
			return 1;
	}
	else
	{	//list1¶Ì,list2³¤
		for (; nCount < 0; nCount++, it2 = it2->next);
		for (; it1 && it2 && it1 != it2; it1 = it1->next, it2 = it2->next);
		if (it1 != NULL && it2 != NULL)
			return 1;
	}
	return 0;
}

int main()
{
	SListIntHead slist1 = NULL;
	SListIntHead slist2 = NULL;
	SListIntEntry *it;
	SListInt_initHead(&slist1);
	SListInt_initHead(&slist2);

	SListInt_prepend(slist1, 10);
	SListInt_prepend(slist1, 20);
	SListInt_prepend(slist1, 30);
	SListInt_prepend(slist1, 40);
	SListInt_prepend(slist1, 50);

	SListInt_prepend(slist2, 1);
	SListInt_prepend(slist2, 2);
	SListInt_prepend(slist2, 3);
	SListInt_prepend(slist2, 4);
	SListInt_prepend(slist2, 5);

	printf("list1:");
	for (it = slist1->next; it; it = it->next)
	{
		printf("%d->", it->data);
	}
	puts("");

	printf("list2:");

	for (it = slist2->next; it && it->next; it = it->next);

	(it) && (it->next = SListInt_nth_entry(slist1, 0));

	for (it = slist2->next; it; it = it->next)
	{
		printf("%d->", it->data);
	}
	puts("");

	printf(">>Has:%d\n", isIntersection(slist1, slist2));
	
	SListInt_free(slist1);
	SListInt_free(slist2);

	SListInt_clearHead(&slist1);
	SListInt_clearHead(&slist2);

	return EXIT_SUCCESS;
}

//int main()
//{
//	SListIntHead slisthead;
//	SListIntEntry *it;
//	int arr[16] = {0};
//	SListInt_InitHead(&slisthead);
//	SListInt_append(&slisthead, 10);
//	SListInt_append(&slisthead, 20);
//	SListInt_append(&slisthead, 30);
//	SListInt_append(&slisthead, 40);
//	SListInt_append(&slisthead, 50);
//	SListInt_insert(&slisthead, 50000, 2);
//	for (it = slisthead->next; it; it = it->next)
//	{
//		printf("%d->", it->data);
//	}
//	puts("");
//
//	it = SListInt_nth_entry(&slisthead, 1);
//	SListInt_remove_entry(&slisthead, it);
//	for (it = slisthead->next; it; it = it->next)
//	{
//		printf("%d->", it->data);
//	}
//	puts("");
//	printf("%d\n", SListInt_nth_data(&slisthead, 1));
//	printf("Len:%d\n", SListInt_length(&slisthead));
//
//	SListInt_to_array(&slisthead, arr, ( sizeof(arr)/sizeof(arr[0]) ) );
//
//	SListInt_free(&slisthead);
//	SListInt_ClearHead(&slisthead);
//	return EXIT_SUCCESS;
//}



#endif

