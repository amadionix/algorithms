/*
Hydrocomp puo' essere facilmente modellato con un grafo, in cui i vertici
sono i punti di erogazione dell'infrastruttura e gli archi sono le tubature.
Utilizzeremo una lista di adiacenza per rappresentare in C il grafo,
utilizzando il codice dell'esercizio precedente.

Compiti da svolgere:
1) un punto sara' isolato quando non ha piu' nodi adiacenti (eliminando 
dalla lista di adiacenza il nodo, automaticamente andra' cancellata la sua 
presenza nelle liste di adiacenza degli altri nodi).
2) equivale a calcolare il numero di componenti fortemente connesse del
grafo: mi basta calcolare il numero di nodi da cui sara' necessario lanciare
una visita del grafo in modo tale da aver visitato tutti i nodi
3) mi basta vedere quali sono i nodi visitati da uno spanning tree che 
parte dal nodo sorgente
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  struct node *next;
  int v;
};
struct adjacencyList {
  int n, m;
  struct node **A;
};
typedef struct adjacencyList * Graph;

Graph graph_new( int n );
void graph_insert( Graph s, int v, int w );
Graph graph_read( void );
void graph_print( Graph s );
void delete( Graph s, int i);
struct node * deleteList(struct node * l);
struct node * Remove ( Graph s, int j, int i );
void DFS ( struct node **A, int i, bool visited[] );
void DFS2 ( struct node **A, int i, bool visited[] );
// FUNZIONI AUSILIARIE
struct node *add( struct node *l, int v ) {
	struct node *new = malloc( sizeof( struct node ) );
	new -> v = v;
	new -> next = l;
	return new;
}

// MAIN
int main(){
	Graph s = graph_read();
	graph_print(s);
  int index = 0, i, C, tox[s -> n], tresh = 0;
  bool visited[s -> n];
  for ( i = 0; i < s -> n; i++ ) visited[i] = false;

  scanf("%d", &tresh);
	for (i = 0; i < s -> n; i++) {
	  scanf("%d", &tox[i]);
	}
	scanf("%d", &C);
	
  for ( i = 0; i < s -> n; i++ ) 
    if ( tox[i] > tresh ) delete(s, i);      
      
	graph_print(s);
  // calcolo indice separazione
  for ( i = 0; i < s -> n; i++ ) {
    if ( s -> A[i] && ! visited[i] ) {
      DFS ( s -> A, i, visited );
      index++;
    }
  }  
  printf("\n\n%d\n", index);

  for ( i = 0; i < s -> n; i++ ) visited[i] = false;
  DFS2 ( s -> A, C, visited );
	return 0;
}

void delete( Graph s, int i) {
  struct node *p = s -> A[i];
  while ( p ) {
    s -> A[p -> v] = Remove ( s, p -> v, i );
    p = p -> next;
  }
  s -> A[i] = deleteList(s -> A[i]);
}

struct node * deleteList(struct node * l) {
  if ( !l ) deleteList (l -> next);
  free (l -> next);
}

// rimuovi dalla lista j-esima le occorrenze di i
struct node * Remove ( Graph s, int j, int i ) { 
  struct node * p = s -> A[j], * q = NULL;
  for(; p && p->v != i; q = p, p = p->next);
	if( ! p )
		return s -> A[j];                             
	if( ! q )
		s -> A[j] = s -> A[j] -> next;			
  else
    q -> next = p -> next;               
	free(p);
	if ( ! s -> A[j] ) 	graph_insert(s, j, j); // tolgo l'archo ma non il nodo
	return s -> A[j];	  
}

// IMPLEMENTAZIONE DELLE FUNZIONI DELL'INTERFACCIA 
// **************************************************************

Graph graph_new( int n ){
	Graph s = malloc(sizeof(struct adjacencyList));
	if(!s) {
        	fprintf(stderr,"Errore di Allocazione\n");
	        exit(EXIT_FAILURE);
	}
	s-> n = n;
	s -> A = calloc( n, sizeof( struct node* ) ); // 
	return s; 
}

void graph_insert( Graph s, int v, int w ){
    s->A[v] = add(s->A[v], w); 
    if ( v != w )
  		s->A[w] = add(s->A[w], v);
}

Graph graph_read( void ){
	int n, m, i, v, w;
	Graph s;
	
	scanf( "%d", &n );
	s = graph_new( n );

	scanf( "%d", &m );
	s -> m = m;
	for (i = 0; i < m; i++) {
		scanf( "%d %d", &v, &w );
		graph_insert( s, v, w);
	}
	
	return s;
}

void graph_print( Graph s ){
	int n = s -> n;
	struct node **al = s -> A;
	struct node *curr; 	
	
	printf( "n = %d\nm = %d\n", n, s -> m );

	for ( int i = 0; i < n; i++ ) {
		printf( "%d:", i );
		for ( curr = al[i]; curr != NULL; curr = curr -> next ) {
			printf( " %d", curr -> v );
		}
		printf( "\n" );
	}
}

int separationIndex ( Graph s ){ // questo in realta' mi conta solo i nodi singoli
  struct node * p = NULL;
  int j, index = 0;
  for ( int i = 0; i < s -> n; i++) {
    for (p = s -> A[i], j = 0; p; p = p -> next ) j++;
    if ( j == 1 ) index++;
  }
}

void DFS ( struct node **A, int i, bool visited[] ) {
  struct node *p = A[i];
  visited[i] = true;  
  while ( p ) {
    if ( ! visited[p -> v] ) {
      DFS( A, p -> v, visited );
    }
    p = p -> next;
  }
}

void DFS2 ( struct node **A, int i, bool visited[] ) {
  struct node *p = A[i];
  visited[i] = true;  
  printf(" %d ", p->v);
  while ( p ) {
    if ( ! visited[p -> v] ) {
      DFS( A, p -> v, visited );
    }
    p = p -> next;
  }
}




