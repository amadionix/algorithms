#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

typedef char *String;
typedef struct elenco{
  int size;
  int count;
  String *content;
} *Elenco;


int main( void ) {
  Elenco b = NULL;
  int size = 4, i = 0;
  char name[N+1] = "";

  b = malloc( sizeof(struct elenco) );   // stavo allocando lo spazio per un puntatore ma mi serve lo spazio per la struct intera
  b -> size = 4;
  b -> count = 0;
  b -> content = calloc( size, sizeof(char *) ); 

  while( strcmp( name, "FINE" ) != 0 ) {
    scanf( "%s", name );

    if ( b -> count == b -> size ) {
      b -> size *= 2;
      b-> content = realloc (b-> content, size * sizeof(char *));
    }
    b -> content[i] = malloc(sizeof(name));
    strcpy(b -> content[i], name); // correct strings assignment
    i++;
    b -> count++; // have to increment this too otherwise I never know when it's full
  }

  for ( int k = 0; k < b -> size; k++ )
      printf( "%s\n", b -> content[k] );

  return 0;
}
