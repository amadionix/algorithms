#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct element {  // elemento di lista
  char ch;
  struct element *next;    // prossimo elemento
};

struct graph {
  int n, m;
  struct element **A; // vettore delle liste di adiacenza
};

typedef struct graph *Graph;

Graph newGraph( int n ); /* alloca una struttura grafo con n nodi */
void addEdge( Graph g, char x, char y); /* inserisce l'arco x -> y */
void printGraph( Graph g ); /* stampa su standard output le liste di adiacenza di g */

Graph read();

void followers(Graph g, char c);
void DFS(Graph g, char c, bool visited[]);

void max(Graph g);

int main( int argc, char *argv[]){
  Graph g = read();
  char c;
  scanf( " %c", &c );
  followers(g,c);
  max(g);
  return 0;
}

void max(Graph g) {
  int *count = calloc(g->n, sizeof(int));
  int max = 0, i;
  struct element *p = NULL;
  for (i = 0; i < g->n; i++) {
    p = g->A[i];
    while (p) {
      if(++count[i] > max) max = count[i];  
      p = p -> next;    
    }
  }
  for (i = 0; i < g->n; i++) 
    if (count[i] == max) printf("%c\n", 'A' + i);
}

void followers(Graph g, char c) {
  bool visited[g->n];
  for (int i = 0; i < g->n; i++) 
    visited[i] = false;
  printf("%c", c);
  DFS(g, c, visited);
  printf("\n");
}

void DFS(Graph g, char c, bool visited[]) {
  struct element *p = g->A[c-'A'];
  visited[c-'A'] = true;
  while (p) {
    if(!visited[p->ch - 'A']) {
      printf("%c", p->ch);
      if(g->A[p->ch-'A']) DFS(g, p->ch, visited);
    }
  p = p -> next;
  }  
}

Graph read() {
  int m;
  char x, y;
  scanf("%d", &m);
  Graph g = newGraph(25); 
  while (m--) {
    scanf( " %c%c", &x, &y );
    addEdge(g, x, y);
  }
  return g;
}

/* crea una struttura grafo con n nodi */
Graph newGraph( int n ){

	Graph g = malloc(sizeof(struct graph));
	if(!g) {
        	fprintf(stderr,"Errore di Allocazione\n");
	        exit(EXIT_FAILURE);
	}
	g -> n = n;
	g -> A = calloc( n, sizeof( struct element* ) ); // vettore delle liste di adiacenza: g -> A [i] e' la lista dell'i-esimo nodo
	return g;
}

// inserimento in liste di adiacenza
struct element *list_insert( struct element *list, char ch ) {
	struct element *new = malloc( sizeof( struct element ) );
	new -> ch = ch;
	new -> next = list;
	return new;

}

// inserisce nel grafo l'arco x -> y
void addEdge( Graph g, char x, char y){
  g->A[x-'A'] = list_insert(g->A[x-'A'],y);
}

/* stampa su standard output le liste di adiacenza di g */
void printGraph( Graph g ){
	printf( "\n************** stampo grafo\n" );
	int n = g -> n;
	struct element **al = g -> A;
	struct element *curr;

	printf( "%d nodi\n%d archi\n", n, g -> m );

	for ( int i = 0; i < n; i++ ) {
		printf( "%c:", 'A'+i );
		for ( curr = al[i]; curr != NULL; curr = curr -> next ) {
			printf( " %c", curr -> ch );
		}
		printf( "\n" );
	}
	printf( "fine stampa grafo *************************\n\n");

}
