#include <stdio.h>
#include <stdlib.h>

void *MyMalloc(size_t size);
void *MyRealloc(void *p, size_t size);

int main(){
  int *p;
  p = MyMalloc(120 * sizeof(int));
  for (int k = 0; k < 120; k++) p[k] = 0;
  if (p != NULL) 
	  p = MyRealloc(p, 200 * sizeof(int));
  for (int k = 120; k < 200; k++) p[k] = 0;
}

void *MyMalloc(size_t size){
  void *q = malloc(size);
  if(q == NULL) {
	  printf("err\n");
	  exit;
  }
  return q;
}

void *MyRealloc(void *p, size_t size) {
  p = realloc(p, size);
  if (p == NULL) {
	  printf("err\n");
	  exit;
  }
  return p;
}
