#include <stdio.h>
/******************************************************************************/
// *** data structs ***
// priority queue min-heap
struct Item {
	int key;
};
typedef struct Item Item;
struct Heap {
	Item *h;
	int size, count;
};
typedef struct Heap *Pqueue;
// lists
typedef struct ListNode{
	Item item;
	struct ListNode *next;
	} ListNode;
// max-heap of pointers
struct Heap2 {
	ListNode **h;
	int size, count;
};
typedef struct Heap2 *Pqueue2;
/******************************************************************************/
// *** utilities ***
// general
void *MyMalloc(size_t size);
int GetKey(Item i);
int Father(int i);
int Left(int i);
int Right(int i);
void Swap(Item *h, int x, int y);
void DisplayItemArr(Item a[], int size);
// lists
ListNode *ListInsert(Item new_item, ListNode *old_list);
ListNode *ListAppend(Item new_item, ListNode *old_list);
Item ReadFirst(ListNode *h);
void PrintList(ListNode *h);
ListNode *ArrayToItemList(int int_array[], int arr_size);
/******************************************************************************/
// *** priority queue (min-heap) ***
// utilities
Pqueue PqueueNew(int size);
int PqueueLength(Pqueue pq);
Item PqueueMin(Pqueue pq);
void PqueueDestroy(Pqueue *pq);
void DisplayQueue1(Pqueue pq);
// insert & extract-min
void PqueueInsert(Pqueue pq, Item item);
void MinHeapifyUp(Item *h, int i);
Item PqueueExtractMin(Pqueue pq);
void MinHeapifyDown(Item *h, int i, int count);
// array sorter using (external) priority queues
void PqueueSort(Item a[], int l, int r);
/******************************************************************************/
// *** heapsort algorithm (locally arr to heap, doesn't create a new one) ***
void HeapSort(Item a[], int size);
void BuildMaxHeapFromArr(Item a[], int size); // linear & local
void MaxHeapifyDown(Item *a, int i, int size);
/******************************************************************************/
// *** sorted lists merger (using max-heap of Item's lists) ***
// utilities
void Swap2(ListNode *h[], int x, int y);
Pqueue2 Pqueue2New(int size);
void DisplayQueue2(Pqueue2 pq);
// insert & extract-max
void Pqueue2Insert(Pqueue2 pq, ListNode *item_ptr);
void MaxHeapifyUp2(ListNode *h[], int i);
Item Pqueue2ExtractMax(Pqueue2 pq);
void MaxHeapifyDown2(ListNode *h[], int i, int size);
// merger of lists sorted in decreasing order
ListNode *ListsMerge(ListNode *list_arr[], int k);
/******************************************************************************/
int main() {
	int k = 4;
	int n = 20;
	// arrays
	int arr1[] = {5,3,2,1,0};		
	int arr2[] = {8,6,4,4,3};
	int arr3[] = {10,9,2,1,1};
	int arr4[] = {14,11,9,8,4};
	// lists
	ListNode *list_a = ArrayToItemList(arr1, 5);
	ListNode *list_b = ArrayToItemList(arr2, 5);
	ListNode *list_c = ArrayToItemList(arr3, 5);
	ListNode *list_d = ArrayToItemList(arr4, 5);
	// array of lists
	ListNode *list_arr[k];
	list_arr[0] = list_a;
	list_arr[1] = list_b;
	list_arr[2] = list_c;
	list_arr[3] = list_d;
        
	ListNode *out_list = ListsMerge(list_arr, k);
	PrintList(out_list);
}

/******************************************************************************/
// *** utilities ***

// general

void *MyMalloc(size_t size) {
	void *q = malloc(size);
	if (q == NULL)
		return NULL;
	return q;
}

int GetKey(Item i) {
	return i.key;
}

int Father(int i) {
	return i/2;
}

int Left(int i) {
	return i*2;
}	

int Right(int i) {
	return i*2+1;
}

void Swap(Item *h, int x, int y) {
  Item temp = h[x]; 
  h[x] = h[y]; 
	h[y] = temp; 
}

void DisplayItemArr(Item a[], int size) {
	for (int i = 0; i < size; i++)
			printf("%d ", GetKey(a[i]));
	printf("\n");
}

// lists

ListNode *ListInsert(Item new_item, ListNode *old_list) {
	ListNode *new_list = MyMalloc(sizeof(ListNode));
	new_list->item = new_item;
	new_list->next = old_list;
	return new_list;
}

ListNode *ListAppend(Item new_item, ListNode *old_list) {
	ListNode *p = old_list;
	ListNode *new_node = MyMalloc(sizeof(ListNode));
	new_node->item = new_item;
	new_node->next = NULL;
	if (old_list == NULL) 
		old_list = new_node;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = new_node;
		}
	return old_list;
}

Item ReadFirst(ListNode *h) {
	return h->item;
}

void PrintList(ListNode *h) {
	for (; h!= NULL; h = h->next)
		printf("%d ", GetKey(h->item));
	printf("\n");
}

ListNode *ArrayToItemList(int int_array[], int arr_size) {
	ListNode *list = NULL;
	for (int i = 0; i < arr_size; i++) {
		Item item;
		item.key = int_array[i];
		list = ListAppend(item, list);
	}
	return list;
}

/******************************************************************************/
// *** priority queue (min-heap) ***

// utilities

Pqueue PqueueNew(int size) {
	Pqueue pq = malloc(sizeof(struct Heap));
	pq->count = 0;
	pq->size = size;
	pq->h = malloc(size*sizeof(Item));
	return pq;
}

int PqueueLength(Pqueue pq) {
	if (!pq) {
		printf("there's no heap\n");
		return -1;
	}

	return pq->count;
}

Item PqueueMin(Pqueue pq) {
	if (!pq) {
		printf("there's no heap\n");
		Item i;
		i.key = -1;
		return i;
	}

	return (pq->h)[1];
}

void PqueueDestroy(Pqueue *pq) {
	free((*pq)->h);
	free(*pq);
	*pq = NULL;
}

void DisplayQueue1(Pqueue pq) {
	if (!pq) {
		printf("there's no heap\n");
		return;
	}
		
	for (int i = 1; i < pq->count + 1; i++)
		printf("%d ", (pq->h[i]).key);
		
	printf("\n");
}

// insert & extract-min

void PqueueInsert(Pqueue pq, Item item) {
	if (!pq) {
		printf("there's no heap\n");
		return;
	}
	
	if (pq->count >= pq->size) {
		printf("non c'e' piu' spazio\n");
		return;
	}
	
	pq->h[++(pq->count)] = item;
	MinHeapifyUp(pq->h, pq->count);
}

void MinHeapifyUp(Item *h, int i) {
	if (i>1) {
		int j = Father(i);
		if (GetKey(h[i]) < GetKey(h[j])) {
			Swap(h, i, j);
			MinHeapifyUp(h, j);
		}
	}
}

Item PqueueExtractMin(Pqueue pq) {
	if (!pq) {
		printf("there's no heap\n");
		Item i;
		i.key = -1;
		return i;
	}
	
	Item min = pq->h[1];
	pq->h[1] = pq->h[pq->count--];
	MinHeapifyDown(pq->h, 1, pq->count);
	return min;
}

void MinHeapifyDown(Item *h, int i, int count) {
	if (Left(i) < count) {       // has at least a child
		int smaller_child;
		if (count == 2*i)
			smaller_child = count; // only child
		smaller_child = i*2 < i*2+1 ? i*2 : i*2+1;
		if (GetKey(h[i]) > GetKey(h[smaller_child])) {
			Swap(h, i, smaller_child);
			MinHeapifyDown(h, smaller_child, count);
		}
	}
}

// array sorter using (external) priority queues

void PqueueSort(Item a[], int l, int r) {
	Pqueue pq = PqueueNew(r-l+1);
	for (int i = l; i <= r; i++) 
		PqueueInsert(pq, a[i]);
	for (int i = l; i <= r; i++)  
		a[i] = PqueueExtractMin(pq);		
	PqueueDestroy(&pq);
}

/******************************************************************************/
// *** heapsort algorithm (locally arr to heap, doesn't create a new one) ***

void HeapSort(Item a[], int size) {
	BuildMaxHeapFromArr(a, size);	
	while (size-- > 1) {
		Swap(a, 0, size);
		MaxHeapifyDown(a, 0, size);
	}
}

void BuildMaxHeapFromArr(Item a[], int size) {
	for (int i = size/2-1; i >= 0; i--) 
		MaxHeapifyDown(a, i, size);
}

void MaxHeapifyDown(Item *a, int i, int size) {
	int largest = i;
	int l = 2*i+1;
	int r = 2*i+2;
	
	if (l < size && GetKey(a[l]) > GetKey(a[largest]))
		largest = l;
	
	if (r < size && GetKey(a[r]) > GetKey(a[largest]))
		largest = r;

	if (largest != i) {
		Swap(a, i, largest);
		MaxHeapifyDown(a, largest, size);
	}
}

/******************************************************************************/
// *** sorted lists merger (using max-heap of Item's lists) ***

// utilities

void Swap2(ListNode *h[], int x, int y) {
  ListNode *temp = h[x]; 
  h[x] = h[y]; 
	h[y] = temp; 
}

Pqueue2 Pqueue2New(int size) {
	Pqueue2 pq = malloc(sizeof(struct Heap2));
	pq->count = 0;
	pq->size = size;
	pq->h = malloc(size*sizeof(ListNode*));
	return pq;
}

void DisplayQueue2(Pqueue2 pq) {
	if (!pq) {
		printf("there's no heap\n");
		return;
	}
		
	for (int i = 1; i < pq->count + 1; i++)
		printf("%d ", pq->h[i]->item.key);
		
	printf("\n");
}

// insert & extract-max

void Pqueue2Insert(Pqueue2 pq, ListNode *list_ptr) {
	if (!pq) {
		printf("there's no heap\n");
		return;
	}
	if (pq->count >= pq->size) {
		printf("non c'e' piu' spazio\n");
		return;
	}
	
	pq->h[++(pq->count)] = list_ptr;
	MaxHeapifyUp2(pq->h, pq->count); 
}

void MaxHeapifyUp2(ListNode *h[], int i) {
	if (i>1) {
		int j = Father(i);
		if (GetKey(ReadFirst(h[i])) > GetKey(ReadFirst(h[j]))) {
			Swap2(h, i, j);
			MaxHeapifyUp2(h, j);
		}
	}
}

Item Pqueue2ExtractMax(Pqueue2 pq) {
	if (!pq) {
		printf("there's no heap\n");
		Item i;
		i.key = -1;
		return i;
	}
	if (pq->h[1] == NULL) {
		printf("the heap is empty\n");
		Item i;
		i.key = -1;
		return i;
	}
	
	Item max = pq->h[1]->item;
	
	if (pq->h[1]->next == NULL) { 
		free(pq->h[1]);
		pq->h[1] = NULL;
		while (pq->h[pq->count] == NULL && pq->count > 1) {
			pq->count--;
		}
		if (pq->count != 1) {
			Swap2(pq->h, 1, pq->count--);
		}
	}
	else {
		ListNode *aux = pq->h[1];
		pq->h[1] = pq->h[1]->next;
		free(aux);
	} 
	MaxHeapifyDown2(pq->h, 1, pq->count);
	
	return max;
}

void MaxHeapifyDown2(ListNode *h[], int i, int size) { 
	int largest = i;
	int l = 2*i;
	int r = 2*i+1;
	
	if (l <= size && GetKey(ReadFirst(h[l])) > GetKey(ReadFirst(h[largest])))
		largest = l;
	if (r <= size && GetKey(ReadFirst(h[r])) > GetKey(ReadFirst(h[largest])))
		largest = r;
	if (largest != i) {
		Swap2(h, i, largest);
		MaxHeapifyDown2(h, largest, size);
	}
}

// merger of lists sorted in decreasing order

ListNode *ListsMerge(ListNode *list_arr[], int k) {
	Pqueue2 pq = Pqueue2New(k);
	ListNode *out_list = NULL;
	
	for (int i = 0; i < k; i++) {
		Pqueue2Insert(pq, list_arr[i]);
	}

	while (pq->h[1] != NULL) {
		out_list = ListAppend(Pqueue2ExtractMax(pq), out_list);
	}
	return out_list;
}


