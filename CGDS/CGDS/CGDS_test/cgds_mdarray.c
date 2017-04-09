#include "cgds/cgds_mdarray.h"
#include "tool.h"

#ifndef TEST_CGSD_MDARRAY

CGDS_GENERATE_MALLOC_2D_ARR(char)

#define ROW		200
#define COL		200
int main() {
	int arr2d[ROW][COL];
	char indexI, indexJ, cnt = 0;
	for (indexI = 0; indexI < ROW; indexI++) {
		for (indexJ = 0; indexJ < COL; indexJ++) {
			arr2d[indexI][indexJ] = 'A';
		}
	}

	return EXIT_SUCCESS;
}




#endif



