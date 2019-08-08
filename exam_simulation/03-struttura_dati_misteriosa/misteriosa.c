/* Di che struttura dati si tratta e come è implementata in questo programma?
INSERITE QUI LA VOSTRA risposta 

e' un grafo implementato con liste di adiacenza
ovvero con un array di dimensione n, dove n numero di nodi e m numero di 
archi
ogni elemento dell'array contiene una lista, che rappresenta i nodi ad esso
adiacenti
il grafo e' non orientato, quindi se due nodi a e b sono collegati,
b sara' presente nella lista di a, e viceversa.
*/



#include <stdio.h>
#include <stdlib.h>

// chiamato node, potevo chiamarlo anche vertex
struct node {
  struct node *next;
  int v;
};

/* Come descrivereste struct x?
INSERITE QUI LA VOSTRA risposta 

nodo di una lista di interi, rappresenta un vertice nel nostro grafo

*/
struct adjacencyList {
  int n, m;
  struct node **A;
};

/* Cosa rappresenta il membro A di dataStructure?
INSERITE QUI LA VOSTRA risposta 

array di liste di interi (lista di adiacenza?)

*/

typedef struct adjacencyList *Ds;

/* creazione della struttura dati */
Ds dataStructure_new( int n );

/* inserimento di archi nella struttura dati */
/* Documentate QUI fa la funzione dataStructure_insert
inserisce un nuovo arco nella lista di adiacenza
prende due interi in input, rappresentanti i due vertici
e aggiunge il secondo alla lista dei vicini del primo,
e fa il viceversa nel caso siano diversi
 */
void dataStructure_insert( Ds s, int v, int w );

/* lettura da standard input */
Ds dataStructure_read( void );

/* stampa su standard output */
void dataStructure_print( Ds s );


// FUNZIONI AUSILIARIE
//***************************************

/* DOCUMENTATE QUI cosa fa la funzione add
inserisce un intero in testa ad una lista di interi 
qui viene unitilizzato nella funzione insert quando vado ad inserire
un vertice in una lista di adiacenza
*/
struct node *add( struct node *l, int v ) {
	struct node *new = malloc( sizeof( struct node ) );
	new -> v = v;
	new -> next = l;
	return new;
}

// MAIN
int main(){
	Ds s = NULL;
	s = dataStructure_read();

	dataStructure_print(s);

	return 0;
}

// IMPLEMENTAZIONE DELLE FUNZIONI DELL'INTERFACCIA 
// **************************************************************

Ds dataStructure_new( int n ){
	Ds s = malloc(sizeof(struct adjacencyList));
	if(!s) {
        	fprintf(stderr,"Errore di Allocazione\n");
	        exit(EXIT_FAILURE);
	}
	s-> n = n;
	s -> A = calloc( n, sizeof( struct node* ) ); // 
	return s; 
}

void dataStructure_insert( Ds s, int v, int w ){
    s->A[v] = add(s->A[v], w); 
    if ( v != w )
  		s->A[w] = add(s->A[w], v);
}

Ds dataStructure_read( void ){
	int n, m, i, v, w;
	Ds s;

	scanf( "%d", &n );
	s = dataStructure_new( n );
	
	scanf( "%d", &m );
	s -> m = m;
	for (i = 0; i < m; i++) {
		scanf( "%d %d", &v, &w );
		dataStructure_insert( s, v, w);
	}

	return s;
}

void dataStructure_print( Ds s ){
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


