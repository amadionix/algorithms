#include <stdio.h>
#include <string.h>

int SmallestWordIndex(char *s[], int n);

int main(void) {
  char *dict[] = {" ciao ", " mondo ", " come ", " funziona ", " zene ", " questo ", " programma "};
  int len = 7, pos;
  pos = SmallestWordIndex(dict, len);
  printf("La parola minima si trova in posizione %d.\n", pos);
  return 0;
}

int SmallestWordIndex(char *s[], int n) {
  char **p = NULL;
  int i = 0, k = 0;
  char min[100];
  strcpy(min, s[0]);
  for (p = s; p < s + n - 1; p++) {
	  if (strcmp(min, *p) > 0) {
		  strcpy(min, *p);
		  i = p - s;
		}
	}
  return i;
}
