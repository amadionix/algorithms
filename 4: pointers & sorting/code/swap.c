#include <stdio.h>

void Swap( int *p, int *q);

int main() {
  int a=2, b=3;
  printf("%d %d\n", a, b);
  Swap(&a, &b);
  printf("%d %d", a, b);
  return 0;
}

void Swap(int *p, int *q) {
  int i;
  i = *p;
  *p = *q;
  *q = i;
}
