#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct element {  // definizione di un elemento della lista
  char ch;
  struct element *next;    // prossimo elemento
};

typedef struct queue {
  struct element *head;
  struct element *tail;
  int count;
} *Queue;

char stra[8] = {'w', 'y', 'j', 'k', 'W', 'Y', 'J', 'K'};
char voc[10] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};

Queue init();
void enqueue(char ch, Queue q);
char dequeue(Queue q); // assume che la coda non sia vuota
void extract(Queue q);
bool isempty(Queue q);

int main(int argc, char *argv[]){
  Queue q, v, c, s;
  char ch;
//  char o = argv[1][0]; printf("%c",o);
  q = init();
  s = init();
  c = init();
  v = init();
  int i = 0;
  
// lettura delle lettere e inserimento nella coda q
  do {
    ch = getchar();  
    enqueue(ch, q);
  } while (ch != '\n');

  // estrazione dalla coda e distribuzione delle lettere nelle code v,c,s
  while (!isempty(q)) {
    ch = dequeue(q);
    for (i = 0; i < 8; i++) 
      if ( ch == stra[i] ) {
        enqueue(ch, s);
        continue;
      }  
    for (i = 0; i < 10; i++) 
      if ( ch == voc[i] ) {
        enqueue(ch, v);
        continue;
      }  
    enqueue(ch, c);
  }
  // stampa della coda opportuna
  switch( argv[1][0] ) {
    case 'V': extract(v);
      break;
    case 'C': extract(c);
      break;
    case 'S': extract(s);
  }

  return 0;
}

void extract(Queue q) {
  while (!isempty(q)) printf("%c", dequeue(q));
  printf("\n");  
}

bool isempty(Queue q) {
  if(!q || !q->head) return true;
  else return false;
}

Queue init(){
  Queue q = malloc(sizeof(struct queue));
  q->head = NULL;
  q->count = 0;
  return q;
}

void enqueue(char ch, Queue q){//printf("%c\n",ch);
  struct element *new = malloc(sizeof(struct element));
  new->ch = ch;
  new->next = NULL;
  if (q->head == NULL)
    q->head = new; // la coda era vuota
  else {
    q->tail->next = new; // attacco in coda
  }
  q->tail = new;
  q->count++;
}

// assumo che la coda non sia vuota
char dequeue(Queue q){
  char ch;
  struct element *testa = q->head;
  ch = testa->ch;
  q->head = q->head->next;
  free(testa);
  q->count--;
  return ch;
}
