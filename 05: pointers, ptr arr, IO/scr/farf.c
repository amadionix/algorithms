#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void Farf(char **sentence);
bool IsInString(char a, char *arr);

int main(int argc , char **argv) {
  Farf(argv);
}

void Farf(char **sentence) {
  char vocals[] = {'a', 'e', 'i', 'o', 'u', '\0'}, word2[100];
  char *p, **q;
  int i, j;
  for (i = 0, q = &sentence[1]; *q != NULL; q++, i++) {
	  for (j = 0, p = *q; *p != '\0'; p++, j++) {
		  word2[j] = *p;
		  if (IsInString(*p, vocals)) {
			  word2[++j] = 'f';
			  word2[++j] = *p;
		  }
	  }
	  word2[j] = '\0';
	  printf("%s ", word2);
	}
	printf("\n");
}

bool IsInString(char a, char *arr) {
  for (char *p = arr; *p != '\0'; p++)
	  if (a == *p) return true;
  return false;
}
	 


