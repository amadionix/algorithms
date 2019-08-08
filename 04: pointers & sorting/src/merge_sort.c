#include <stdio.h>

void MergeSort(int A[], int low, int high);
void Merge(int arr[], int l, int m, int r);
void PrintArr(int A[], int n);

int main() {
	int A[] = {1,3,4,7,2,3,5};
	int n = sizeof(A) / sizeof(int);
	MergeSort(A, 0, n-1);
	PrintArr(A, n);
}

void MergeSort(int A[], int low, int high) {
  if(high <= low) return;
  int mid = (low + high) / 2;
  MergeSort(A, low, mid);
  MergeSort(A, mid+1, high);
  Merge(A, low, mid, high);
}

void Merge(int arr[], int l, int m, int r) { 
  int i, j, k; 
  int n1 = m - l + 1; 
  int n2 =  r - m; 
  /* create temp arrays */
  int L[n1], R[n2]; 
  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++) 
    L[i] = arr[l+i]; 
  for (j = 0; j < n2; j++) 
    R[j] = arr[m+1+j]; 
  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray 
  j = 0; // Initial index of second subarray 
  k = l; // Initial index of merged subarray 
  while (i < n1 && j < n2) { 
    if (L[i] <= R[j]) { 
      arr[k] = L[i]; 
      i++; 
    } else { 
      arr[k] = R[j]; 
      j++; 
    } 
    k++; 
  } 
  /* Copy the remaining elements of L[], if there 
     are any */
  while (i < n1) { 
    arr[k] = L[i]; 
    i++; 
    k++; 
  } 
  /* Copy the remaining elements of R[], if there 
     are any */
  while (j < n2) { 
    arr[k] = R[j]; 
    j++; 
    k++; 
  } 
} 

void PrintArr(int A[], int n) {
	for(int k = 0; k < n; k++) printf("%d ", A[k]);
	printf("\n");
}
	
