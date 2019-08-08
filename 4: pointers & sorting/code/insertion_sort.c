#include <stdio.h>
void InsertionSort(int A[], int n);

int main() {
	int A[] = {1,3,4,7,2,3,5};
	int n = sizeof(A) / sizeof(int);
	InsertionSort(A, n);
	for (int k = 0; k < n; k++) printf("%d ", A[k]);
	printf("\n");
}

void InsertionSort(int A[], int n) {
  int key = 0;
  int j = 0;
  for(int k = 1; k < n; k++){
	  key = A[k];
	  j = k - 1;
	  while(j >= 0 && A[j] > key) {
		  A[j+1] = A[j];
		  j--;
	  }
	  A[j+1] = key;
	}
}	
