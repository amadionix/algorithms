#include <stdio.h>
#include <stdlib.h>



char *readline() {
	char *s, *tmp;
	char c;
	int size = 2;
	int i = 0;
	s = malloc ( size ); // alloco 2 byte. forse casting explicit?

	while ( ( c = getchar() ) != '\n') {
		if ( i > size) {
			size *= 2;
			tmp = realloc ( s, size );
			if ( tmp == NULL )
				exit(EXIT_FAILURE);
			s = tmp;
		}
		s[i++] = c++;
	
	}
	return s;
}

int main() {
	int n, i, left, right, mid;
	char *x[100], *y;
	scanf("%d ",&n);

	for (i=0;i<n;i++) 
		x[i] = readline();

	y = readline();

	left=0; right=n-1;
	while (left<=right) {
		mid=(left+right)/2;
		if ( strcmp( x[mid], y) == 0 ) {
			printf("= %s\n",x[mid]);
			return 0;
		} else if (strcmp(x[mid],y)< 0 ) {
			printf("> %s\n",x[mid]);
			left=mid+1;
		} else {
			printf("< %s\n",x[mid]);
			right=mid-1;
		}
	}
}
