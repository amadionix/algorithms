#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORDSIZE 15

struct Occurrence{
	char word[WORDSIZE];
	int n;
	};
typedef struct Occurrence *Item;

struct bitNode{
	Item item;
	struct bitNode *l, *r;
	};
typedef struct bitNode *BitNode;

typedef char *Key;

char *GetKey(Item i);
BitNode BitNew(Key k);
Item CreateOccurrence(char *word);
int GetWordFromFile(FILE *fp, char *dst);

void BistInsert(BitNode *tree, Item item);
int BistSearchParent(BitNode r, Key k, BitNode *parent, BitNode *p);

void BistInOrderPrint(BitNode p);
void BistOutOrderPrint(BitNode p);
void BistPrintNode(BitNode p);

void PrintOccNum(BitNode tree, Key k);
int BistSearch(BitNode p, Key k);

void *MyMalloc(size_t size);
void *MyRealloc(void *p, size_t size);

int main(){

  Item item;
  FILE *fptr;
  char word[WORDSIZE];
  BitNode tree = NULL;

  fptr = fopen("file.txt","r");
  if(fptr == NULL){
	  printf("Error!");   
          exit(1);             
  }
    
  while (GetWordFromFile(fptr, word) > 0) { 
	  item = CreateOccurrence(word);
	  BistInsert(&tree, word);
  }

  fclose(fptr);

  BistInOrderPrint(tree);
  printf("\n");
  BistOutOrderPrint(tree);
  printf("\n");

  // Occurence number from Input word
  while (1) {
	  scanf("%s", word);
	  if (strcmp(word,"f") == 0)
		  break;
	  PrintOccNum(tree, word);
	}
}

void PrintOccNum(BitNode tree, Key k) {
	printf("%d\n", BistSearch(tree, k));
}

int BistSearch(BitNode p, Key k) {	
	if (!p)
		return 0;
	int res = strcmp(k, GetKey(p->item));
	if (res == 0) {
		return p->item->n;
	}
	if (res < 0) {
		return BistSearch(p->l, k);
	} 
	else {
	return BistSearch(p->r, k);
	}
}

void BistInsert(BitNode *tree, Item item) {
	BitNode parent, q = *tree, new = BitNew(item); 
	Key k = GetKey(item); 
	/* se l'albero e' vuoto: */
	if (q == NULL) {
		*tree = new; 
		return;
	}
	/* se la chiave c'e' gia', non inserisco niente: */
	if (BistSearchParent(*tree, k, &parent, &q) == 0) {  
		(q->item->n)++; 
		return;
	}
	/* altrimenti inserisco il nuovo nodo come figlio di parent: */
	if (strcmp(k, GetKey(parent->item)) < 0)
		parent->l = new;
	else
		parent->r = new;
}

int BistSearchParent(BitNode r, Key k, BitNode *parent, BitNode *p) {
	int res;
	*parent = NULL;
	*p = r;
	
	while (*p && (res = strcmp(k, GetKey((*p)->item))) != 0) {
		*parent = *p;
		*p = (res < 0 ? (*p)->l : (*p)->r);
	}
	if (*p == NULL) /* non ci sono nodi con chiave k */
		return -1;
	return 0;
}

char *GetKey(Item i) {
	return i->word;
}

Item CreateOccurrence(char *word) {
	Item item = MyMalloc(sizeof(struct Occurrence));
	item->n = 1;
	strcpy(item->word, word);
	return item;
}

BitNode BitNew(Key k) {
	BitNode node = MyMalloc(sizeof(struct bitNode));
	node->item = CreateOccurrence(k);
	node->l = NULL;
	node->r = NULL;
	return node;
}
	
void BistInOrderPrint(BitNode p) {
	if (p) {
		BistInOrderPrint(p->l);
		BistPrintNode(p);
		BistInOrderPrint(p->r);
	}
}

void BistOutOrderPrint(BitNode p) {
	if (p) {
		BistOutOrderPrint(p->r);
		BistPrintNode(p);
		BistOutOrderPrint(p->l);
	}
}
	
void BistPrintNode(BitNode p) {
	printf("%s %d\n", p->item->word, p->item->n);
}
	
int GetWordFromFile(FILE *fp, char *dst) {
	char word[WORDSIZE];
	int ch, i = 0;
	while (EOF != (ch=fgetc(fp)) && !isalpha(ch))
	;//skip
	if (ch == EOF)
		return -1;
	do {
		word[i++] = ch;
	} while (EOF!=(ch=fgetc(fp)) && isalpha(ch));
	word[i]='\0';
	strcpy(dst, word);
	return 1;
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
