#include <stdio.h>
#include <stdlib.h>

void *MyMalloc(size_t size);
void *MyRealloc(void *p, size_t size);
void Revert1();
void Revert2();

int main(){
//Revert1();
Revert2();
}

void Revert2(){
int len = 2;
int *a = MyMalloc(len*sizeof(int));
for (int k=0; k<len; k++) a[k] = 0;
int i = 0;
//riempio il vettore
while(1){
	if(i == len){
		len += 15;
		a = MyRealloc(a, len * sizeof(int));
		}
	scanf("%d", &a[i]);
	if(a[i] == 0) break;
	i++;
	}
//stampo al rovescio
while(i >= 0)
	printf("%d\n", a[i--]);
}

void Revert1(){
  int len = 2;
  int *a = MyMalloc(len * sizeof(int));
  for (int k = 0; k < len; k++) a[k] = 0;
  int i = 0;
  //riempio il vettore
  while (1) {
	  if (i == len) {
		  len *= 2;
		  a = MyRealloc(a, len * sizeof(int));
		  }
	  scanf("%d", &a[i]);
	  if (a[i] == 0) break;
	  i++;
	}
  //stampo al rovescio
  while (i >= 0)
	  printf("%d\n", a[i--]);
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
