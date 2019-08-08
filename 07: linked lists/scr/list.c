#include <stdio.h>
#include <stdlib.h>

void *MyMalloc(size_t size);
void *MyRealloc(void *p, size_t size);
typedef struct Element{
	int info;
	struct Element *next;
} Element;
	
Element *Insert(int n, Element *h);
void PrintList(Element *h);
int IsMember(int n, Element *h);
Element *Delete(int n, Element *h);
void Destroy(Element **h);
int *ListToArray(Element *h, int n);
void PrintInv(Element * h);
	
int main(){
  int el, count = 0;
  char *c = NULL;
  int *a = NULL;
  Element *head = NULL;
  while ((c = getchar()) != 'f') {
	  switch ((int)c) {
		  case '+':
			  scanf("%d", &el);
			  if(!IsMember(el, head)){
				  head = Insert(el, head);
				  count++;
				}
			  break;
		  case 'p':
			  PrintList(head);
			  break;
		  case '?':
			  scanf("%d", &el);
			  if (IsMember(el, head))
				  printf("appartiene");
			  else printf("non appartiene");
			  break;
		  case '-':
			  scanf("%d", &el);
			  if (IsMember(el, head)) {
				  head = Delete(el, head);
				  count--;	
				}
			  break;
		  case 'd':
			  Destroy(&head);
			  count = 0;
			  break;
		  case 'r':
			  PrintInv(head);
			  /*oppure 
			  a = listToArray(head, count);
			  for(int i = count-1; i > -1; i--)
				  printf("%d ", a[i]);*/
			  break;
		} 
	} 
}
	
void PrintInv(Element * h){
	if (h == NULL)
		return;
	if (h->next == NULL) 
		printf("%d ", h->info);
	else{
		PrintInv(h->next);
		printf("%d ", h->info);
	}
}	
	
int *ListToArray(Element *h, int n) {
	int *a = MyMalloc(n * sizeof(int));
	for (int i = 0; h != NULL; h = h->next, i++)
		a[i] = h->info;
	return a;
}	
		
void Destroy(Element **h) {
	Element *cur = NULL;
	while (*h != NULL) {
		cur = *h;
		*h = (*h)->next;
		free(cur);
	}
}	
	
Element *Delete(int n, Element *h) {
	Element *cur = h;
	Element *prev = NULL;
	for (; cur != NULL && cur->info != n; prev = cur, cur = cur->next);
	if (cur == NULL) 
		return h;                             
	if (prev == NULL)
		h = h->next;			               
	else
		prev->next = cur->next;
	free(cur);
	return h;	
}
	
int IsMember(int n, Element *h) {
	for (; h!= NULL; h = h->next)
		if (h->info == n) return 1;
	return 0;		
}

void PrintList(Element *h) {
	for (; h!= NULL; h = h->next)
		printf("%d ", h->info);
	printf("\n");
}

Element *Insert(int n, Element *h) {
	Element *p = MyMalloc(sizeof(Element));
	p->info = n;
	p->next = h;
	return p;
}

void *MyMalloc(size_t size) {
	void *q = malloc(size);
	if (q == NULL)
		return NULL;
	return q;
}

void *MyRealloc(void *p, size_t size) {
	p = realloc(p, size);
	if (p == NULL)
		return NULL;
	return p;
}

