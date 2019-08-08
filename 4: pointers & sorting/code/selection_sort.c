#include <stdio.h>

void SelectionSortIt(int A[], int n);
void SelectionSortRic(int A[], int n);
void Swap(int *p, int *q);
void PrintArr(int A[], int n);

int main(){
	int A[] = {1,3,4,7,2,3,5};
	int n = sizeof(A) / sizeof(int);
	SelectionSortRic(A, n);
	PrintArr(A, n);
}

void SelectionSortRic(int A[], int n){
  int min = 0;
  int j = 0;
  if(n == 1) return;
  for(j = 1; j < n; j++){
	  if(A[j] < A[min]) min = j;
	}
  Swap(&A[0], &A[min]);
  SelectionSortRic(&A[1], n-1);
}

void SelectionSortIt(int A[], int n) {
  int min = 0;
  int j = 0;
  for(int k = 0; k < n-1; k++) {
	  min = k;
	  for(j = k+1; j < n; j++) {
		  if(A[j] < A[min]) min = j;
	  }
	  Swap(&A[k], &A[min]);
  }
}

void Swap(int *p, int *q) {
  int i;
  i = *p;
  *p = *q;
  *q = i;
}

void PrintArr(int A[], int n) {
	for(int k = 0; k < n; k++) printf("%d ", A[k]);
	printf("\n");
}
	
