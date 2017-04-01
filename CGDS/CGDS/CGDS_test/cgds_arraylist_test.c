#include <tool.h>

#include "cgds/cgds_arraylist.h"

CGDS_GENERATE_ARRAYLIST(ArrayListInt, int)

int main()
{
	ArrayListInt *aln = ArrayListInt_new(20);
	int index = 0;
	
	for (index = 0; index < 20; index++)
	{
		ArrayListInt_append(aln, index);
	}
	for (index = 0; index < 20; index++)
	{
		printf("%d\t",aln->data[index]);
	}

	ArrayListInt_free(aln);
	return EXIT_SUCCESS;
}

