#include <stdio.h>
#include <stdlib.h>
#include "cgds/cgds_arraylist.h"

CGDS_GENERATE_ARRAYLIST_INC(ArrayListInt, int)

int main() {
	ArrayListInt *ali;
	ArrayListInt_new(&ali, 16);

	for (int loop = 0; loop < 100; loop++) {
		ArrayListInt_append(ali, loop);
	}

	for (int loop = 0; loop < ali->length; loop++) {
		printf("%d\t", ArrayListInt_nth_data(ali, loop));
	}


	ArrayListInt_free(ali);
	return EXIT_SUCCESS;
}


CGDS_GENERATE_ARRAYLIST_SRC(ArrayListInt, int)
