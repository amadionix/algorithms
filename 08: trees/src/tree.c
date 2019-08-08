#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *MyMalloc(size_t size);
void *MyRealloc(void *p, size_t size);

#define ARRSIZE 10
typedef int Item;
struct bitNode {
	Item item;
	struct bitNode *l, *r;
};
typedef struct bitNode *BitNode;

BitNode BitNew(Item i);
void BitPreorder(BitNode p);
void BitPostorder(BitNode p);
void BitInorder(BitNode p);
void BitPrintNode(BitNode p);
void BitPrintAsSummary(BitNode p, int spaces);
void BitPrintAsSummaryNode(BitNode p, int spaces);
BitNode BitArr2Tree(Item a[], int size, int i);

int main() {
	int a[ARRSIZE];
	for (int i = 0; i < ARRSIZE; i++)
		a[i] = i;//rand();
	BitNode p = NULL;	
	p = BitArr2Tree(a, ARRSIZE, 0);
	BitPrintAsSummary(p, 0);
}

BitNode BitArr2Tree(Item a[], int size, int i) {
	BitNode p = BitNew(a[i]);
		if (i*2+1 < size) {
			p->l = BitArr2Tree(a, size, i*2 +1);
			if (i*2+2 < size)
				p->r = BitArr2Tree(a, size, i*2 +2);	
		}
	return p;
}

void BitPrintAsSummary(BitNode p, int spaces) {
	if (p) {
		BitPrintAsSummaryNode(p, spaces);
		BitPrintAsSummary(p->l, spaces+1);
		BitPrintAsSummary(p->r, spaces+1);
	}
}

void BitPrintAsSummaryNode(BitNode p, int spaces) {
	for (int i = 0; i < spaces; i++)
		printf(" ");
	if (p)
		printf("*%d\n", p->item);
	else
		printf("*\n");
}

BitNode BitNew(Item i) {
	BitNode node = MyMalloc(sizeof(struct bitNode));
	node->item = i;
	node->l = NULL;
	node->r = NULL;
	return node;
}

void BitPreorder(BitNode p) {
	if (p) {
		BitPrintNode(p);
		BitInorder(p->l);
		BitInorder(p->r);
	}
}

void BitPostorder(BitNode p) {
	if (p) {
		BitInorder(p->l);
		BitInorder(p->r);
		BitPrintNode(p);
	}
}

void BitInorder(BitNode p) {
	if (p) {
		BitInorder(p->l);
		BitPrintNode(p);
		BitInorder(p->r);
  }
}
  
void BitPrintNode(BitNode p) {
	printf("%d\n", p->item);
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

