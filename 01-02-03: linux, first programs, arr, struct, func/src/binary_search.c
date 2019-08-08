#include <stdio.h>

void main() {
	int a, b, c; 
	a = 0;
	b = 1000;
	char ans = '0';

	while (risp != '=' && b - a > 1) {
		c = (a + b) / 2;
		printf("is %d the right value?", c);
		scanf("%c", &ans);
		switch (ans) {
		  case '>': 
			  a = c + 1;
			  break;		
		  case '<':
			  b = c - 1;
			  break;		
		  case '=': 
			  printf("correct\n");
			  break;
		}
	}

	if (b == 1000) printf("is %d the right value?", b);
	else if (b == 1) printf("is %d the right value?", a);
	scanf(" %c", &ans);	
	if (ans == '=') printf("correct\n");
	else printf("wrong");
}
