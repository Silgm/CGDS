#include <tool.h>
#include <cgds/cgds_arraylist.h>

CGDS_GENERATE_ARRAYLIST(ArrayListInt, int)

int main()
{
	ArrayListInt *aln;
	
	aln = ArrayListInt_new(20);
	
	for (int index = 0; index < 10; index++)
	{
		ArrayListInt_append(aln, index);
	}

	ArrayListInt_remove(aln, 2);

	for (int index = 0; index < aln->length; index++)
	{
		printf("%d,", aln->data[index]);
	}
	puts("");

	ArrayListInt_free(aln);
	
	return EXIT_SUCCESS;
}

