#include <stdio.h>

void MaxSecondmax(int A[], int n, int *max, int *second_max);
int *Smallest(int A[], int n);

int main(){
  int x = 0, y = 0;
  int *max = &x, *second_max = &y, *min = NULL;
  int A[] = {9,1,2,4,6,5,3,8};
  int n = sizeof(A) / sizeof(int);
  MaxSecondmax(A, n, max, second_max);
  printf("%d %d\n", *max, *second_max);
  min = Smallest(A, n);
  printf("%d\n", *min);
}

int *Smallest(int A[], int n) {
  int *p = NULL, *q = NULL;
  int min = A[0];
  for (p = A, q = A; p < A+n-1; p++) {
	  if (*p < min) {
		  min = *p;
		  q = p;
	  }
  }
  return q;
}

void MaxSecondmax(int A[], int n, int *max, int *second_max) {
  int *i = NULL;
  for (i = A; i < A+n; i++)
	  if (*i > *max) *max = *i;
  for (i = A; i < A+n; i++)
	  if (*i > *second_max && *i < *max) *second_max = *i;
}


