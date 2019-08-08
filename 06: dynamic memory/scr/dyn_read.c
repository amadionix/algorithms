#include <stdio.h>
#include <stdlib.h>

// dynamically read lines and strings
char *ReadLine(void);
char *ReadWord(void);
void *MyMalloc(size_t size);
void *MyRealloc(void *p, size_t size);

int main() {
  char *line = ReadWord();
  printf("%s", line);
}

char *ReadWord(void){
  int len = 5, i = 0;
  char *a = MyMalloc(len * sizeof(char));
  while (1) {
	  if (i == len) {
		  len += 15;
		  a = MyRealloc(a, len * sizeof(char));
		}
	  scanf("%c", &a[i]);
	  if (a[i] == '\n') break;
	  if (!isalnum(a[i])) {
		  printf("not alphanum\n");
		  return NULL;
	  }
	  i++;
	}
  return a;
}

char *ReadLine(void) {
  int len = 5, i = 0;
  char *a = MyMalloc(len * sizeof(char));
  while(1) {
	  if (i == len) {
		  len += 15;
		  a = MyRealloc(a, len * sizeof(char));
		}
	  if (!scanf("%c", &a[i])) return NULL;
	  if (a[i] == '\n') break;
	  i++;
	}
  return a;
}

void *MyMalloc(size_t size) {
  void *q = malloc(size);
  if (q == NULL)
	  return NULL;
  return q;
}

void *MyRealloc(void *p, size_t size){
  p = realloc(p, size);
  if (p == NULL)
	  return NULL;
  return p;
}
