#include<stdio.h>
#include<stdlib.h>

struct element {
	int val;
	int row;
	int col;
	struct element *right;
	struct element *down;
};

typedef struct element *Element;

typedef struct {
	Element head;
	int rows;
	int cols;
} linkedMatrix;


linkedMatrix leggiMatrice( void );
linkedMatrix trasponiMatrice ( linkedMatrix m );
void stampaMatrice ( linkedMatrix m );
void stampaMatriceTrasposta ( linkedMatrix m );



int main () {
	linkedMatrix m = leggiMatrice();
	stampaMatrice(m);
	printf( "\n" );
	stampaMatriceTrasposta(m);
	return 0;

}


linkedMatrix leggiMatrice( void ){

	int r,c;
	scanf( "%d%d", &r,&c );
	int t = r*c;
	Element curr; // puntatore all'elemento corrente della matrice
	Element first = NULL; // puntatore al primo elemento della riga corrente
	Element top = NULL; // puntatore all'elemento sopra a quello corrente (oppure NULL)

	linkedMatrix m;
	curr = malloc( sizeof (struct element) );
	m.head = curr;
	m.rows = r;
	m.cols = c;
	first = curr;

	int i=0, j=0, n;
	while ( --t >= 0 ) {
		scanf( "%d", &n );
		curr -> val = n;
		curr -> row = i;
		curr -> col = j;
		curr -> down = NULL;
	
		// collego l'elemento top all'elemento corrente
		if( top ) {
			top -> down = curr;
		}

		if ( t == 0 ) {
			curr -> right = NULL;
			break;	
		}
 	
		// creo spazio per il prossimo elemento
		Element new = malloc( sizeof (struct element) ); 
		
		// posiziono new
		// a destra dell'elemento corrente oppure all'inizio della prossima riga,
		// aggiorno first e top di conseguenza
		if ( j % c == c-1 ) {
			curr -> right = NULL;
			j = 0;

			first -> down = new;
			top = first;
			first = new;
			i++;
		}
		else {
			curr -> right = new;
			j++;
			if ( top )
				top = top->right;
		}
		
		// sposto curr sulla prossima posizione
//		printElement( curr );	
		curr = new; 
	}
	

return m;
}

void stampaMatrice ( linkedMatrix m ) {
  int r = m.rows;
  int i = 0;
  struct element *q = m.head, *p = NULL;  

  while ( q ) {
    p = q;
    while ( p ) {
      printf( "%d ", p -> val );
      p = p -> right;
    }
    printf( "\n" );
    q = q -> down;   
  }
}

void stampaMatriceTrasposta ( linkedMatrix m ) {
  int r = m.rows;
  int i = 0;
  struct element *q = m.head, *p = NULL;  

  while ( q ) {
    p = q;
    while ( p ) {
      printf( "%d ", p -> val );
      p = p -> down;
    }
    printf( "\n" );
    q = q -> right;   
  }
}






