#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//FORMATO: title TAB author TAB publisher TAB mm/dd/yyyy TAB Fiction
typedef struct bestseller {
  char *titolo;
  char *autore;
  char *editore;
  char *data;         //mese/giorno/anno
  char *genere;        
} *Bs;

Bs read_bs(); // legge una riga con i dati di un bestseller
void print_bs( Bs b); // stampa i dettagli di un bestseller
char *read_tab( void );

int main(){
  char comando = '\0';
  short int d, m, y;
  int size = 3;
  Bs *bs = calloc(size, sizeof(Bs));
  Bs bs_arr[size];

  while( (comando = getchar()) != 'f' ) {
    switch( comando ) {

    case '+': // seguito da riga con dettagli su un bestseller
      if (bs_arr[size-1]) {
      // need to reallocate array
        size *= 2;
        bs = realloc(bs_arr, size * sizeof(struct bestseller *));
        for (int i = size/2; i < size; i++) bs[i] = NULL;
      }  
      bs = read_bs();     // leggo e aggiungo UN bestseller
      break;

    case '?': // seguito da una data. stampa il libro bestseller in quella data
      scanf( "%hd/%hd/%hd", &d, &m, &y);
      //....
      break;

    }
  }

  return 0;
}

// legge una riga con i dati di un bestseller e la memorizza in una struttura di cui restituisce l'indirizzo
Bs read_bs(){
  Bs bs = malloc(sizeof(struct bestseller));
  bs -> titolo = read_tab();
  bs -> autore = read_tab();
  bs -> editore = read_tab();
  bs -> data = read_tab();
  bs -> genere = read_tab();
  return bs;
}

// legge da standard input fino a quando non trova un carattere di tabulazione (e ignorando gli spazi iniziali)
char *read_tab( void ) {
  char *p, c;
  int size = 2;
  int n = 0;

  p = malloc( size );
  while ( isspace( c = getchar() ) )
      ;

  while ( c != EOF ) {
    /* se ho terminato lo spazio, raddoppio l'allocazione */
    if ( n >= size ) {
      size *=2;
      //printf( "\nnew size = %d\n", size );
      p = realloc( p, size * sizeof(char) );
    }
    /* memorizzo l'n-esimo elemento */
    if ( c == '\t' ) { /* se leggo '\t', memorizzo '\0' e interrompo */
      p[n] = '\0';
      break;
    }
    p[n++] = c;
    c = getchar();
  }

  printf( "%s\n", p );
  return p;
}


// stampa i dettagli di un bestseller
void print_bs( Bs b)
{
//....
}
