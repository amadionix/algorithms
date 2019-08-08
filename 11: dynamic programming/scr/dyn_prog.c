#include <stdio.h>

struct Interval {
  int nums[3];
  struct Interval *next;
};
enum interval {start, finish, value};
// preprocessing
struct Interval *ReadIntervals(FILE *fp);
struct Interval *ListInsert(int nums[3], struct Interval *old_list);
void PrintList(struct Interval *h);
int GetListSize(struct Interval *list);
void ListToMatrix(struct Interval *list, int size, int pool[][3]);
void PrintMatrix(int size, int pool[][3]);
void MergeSort(int A[][3], int low, int high);
void Merge(int A[][3], int l, int m, int r);
// core
void FindSolution(int j, int pool[][3], int M[], int p[], FILE *fout, int*max);

int main() {
  // file read
  FILE *fptr = fopen("file.txt","r");
  if(fptr == NULL){
	  printf("Error!");   
    exit(1);             
  }
  int max = 0;
  // preprocessing: create matrix pool containing the intervals
  struct Interval *intervals_list = ReadIntervals(fptr);
  int list_size = GetListSize(intervals_list); 
  int pool[list_size][3];
  ListToMatrix(intervals_list, list_size, pool);
  // sort the pool
  MergeSort(pool, 0, list_size);
  PrintMatrix(list_size, pool);
  // build vector p[]
  int i, j;
  int p[list_size];
  for (i = 0; i < list_size; i++) 
    p[i] = -1;
  for (i = 1; i < list_size; i++) 
    for (j = i-1; j >= 0; j--) 
      if (pool[j][finish] < pool[i][start]) { 
        p[i] = j;
        j = 0;
      }
  // build memoization vector (i.e. value of the solution at each step)
  int M[list_size];
  int val;
  M[0] = pool[0][value];
  for (i = 1; i < list_size; i++) {
    if (p[i] < 0) val = 0;
    else val = pool[p[i]][value];
    if (pool[i][value] + val > pool[i-1][value])
      M[i] = pool[i][value] + val;
    else
      M[i] = pool[i-1][value];
  }
  for (i = 0; i < list_size; i++) printf("%d ", M[i]);
  // build a list of the intervals belonging to the solution
  FILE *fout = fopen("file_out.txt","w");
  fprintf(fout, "OUTPUT\n");
  FindSolution(list_size-1, pool, M, p, fout, &max);
  fprintf(fout, "\n%d", max);
}

void FindSolution(int j, int pool[][3], int M[], int p[], FILE *out, int *max) {
  if (j >= 0) {
    int val, prev;
    if (p[j] < 0) val = 0;  
    else val = M[p[j]]; 
    if (j > 0) prev = M[j-1];
    else prev = 0;
    if (pool[j][value] + val >= prev) {
      fprintf(out, "%d ", j);   
      *max += pool[j][value]; 
      if (p[j] >= 0) FindSolution(p[j], pool, M, p, out, max);
    } else {
      FindSolution(j-1, pool, M, p, out, max);
    }
  }
}

// preprocessing funcs
struct Interval *ReadIntervals(FILE *fp) {  
  char input_str[6];	
  int buff[3];
  if (strcmp(fgets(input_str, 6, fp), "INPUT") != 0) {
    printf("problem reading a non-INPUT file");
    return NULL;
  }
  struct Interval *intervals_list = NULL;
	while (EOF != fscanf(fp, "%d-%d %d\n", &buff[0], &buff[1], &buff[2])) 
	  intervals_list = ListInsert(buff, intervals_list);
	return intervals_list;
}

struct Interval *ListInsert(int nums[3], struct Interval *old_list) {
  struct Interval *node = malloc(sizeof(struct Interval));
  for(int i = 0; i < 3; i++) 
    node->nums[i] = nums[i];  
  node->next = NULL;
  struct Interval *new_list = node;
	new_list->next = old_list;
	return new_list;
}
   
void PrintList(struct Interval *h) {
	for (; h; h = h->next) 
		printf("\n%d-%d %d", h->nums[0], h->nums[1], h->nums[2]);
	printf("\n");
}

int GetListSize(struct Interval *list) {
  int i = 0;
  while (list) {
    i++;
    list = list->next;
  }
  return i;
}

void ListToMatrix(struct Interval *list, int size, int pool[][3]) {
  int j;
  for (int i = 0; i < size; i++, list = list->next) {
    for (j = 0; j < 3; j++) 
      pool[i][j] = list->nums[j];
  }
}

void PrintMatrix(int size, int pool[][3]) {
  int j;
  for (int i = 0; i < size; i++) {
    for (j = 0; j < 3; j++) 
      printf("%d ", pool[i][j]);
    printf("\n");
  }
    printf("\n");  
}

void MergeSort(int A[][3], int low, int high) {
  if(high <= low) return;
  int mid = (low + high)/2;
  MergeSort(A, low, mid);
  MergeSort(A, mid+1, high);
  Merge(A, low, mid, high);
}

void Merge(int A[][3], int l, int m, int r) { 
  int i, j, k, p; 
  int n1 = m - l + 1; 
  int n2 =  r - m; 

  int L[n1][3], R[n2][3]; 

  for (i = 0; i < n1; i++)
    for (p = 0; p < 3; p++) 
      L[i][p] = A[l+i][p]; 
  for (j = 0; j < n2; j++) 
    for (p = 0; p < 3; p++) 
      R[j][p] = A[m+1+j][p]; 

  i = j = 0;                  // Initial index of subarrays 
  k = l;                      // Initial index of merged subarray 
  while (i < n1 && j < n2) { 
    if (L[i][1] <= R[j][1]) { 
      for (p = 0; p < 3; p++) 
        A[k][p] = L[i][p]; 
      i++; 
    } else {
      for (p = 0; p < 3; p++)  
        A[k][p] = R[j][p]; 
      j++; 
    } 
    k++; 
  } 

  while (i < n1) { 
    for (p = 0; p < 3; p++)    
      A[k][p] = L[i][p]; 
    i++; 
    k++; 
  } 

  while (j < n2) { 
    for (p = 0; p < 3; p++)  
      A[k][p] = R[j][p]; 
    j++; 
    k++; 
  } 
} 


