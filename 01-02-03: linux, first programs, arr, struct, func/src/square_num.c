#include <stdio.h>
#define TRESH 10

// printf the first TRESH square num
void main() {
	int i = 0;
	int j = 0;

	while (i < TRESH) {
		for (int k = 0; k < j; k++) {
			if (k*k == j) {
				printf("%d\n", j);
				i++;
			}
		}
		j++;
	}
}		
		
                        							
	
