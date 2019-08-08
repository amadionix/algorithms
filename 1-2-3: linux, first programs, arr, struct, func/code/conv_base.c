#include <stdio.h>
#include <string.h>

int main() {
	int n, b, i;
	n = b = i = 0;
	int number_to_convert[100] = {0};

	scanf("%d%d", &b, &n);

	for (i = 0; n > 0; i++) {
		number_to_convert[i] = n % b;
		n = n / b;
	}

	i--;
	while (i >= 0) {
	  printf("%d", number_to_convert[i]);
	  i--;
	}
	printf("\n");
	
	return 0;
}
