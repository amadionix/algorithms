#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 100
 
char cifra( char c, int k );
 
int main( int argc, char *argv[] ) {
 
  int k, i = 0;
  char op = argv[1][0];
  char testo[N];
  char *modificato;

  while ( ( testo[i] = getchar() ) != '\n' ) {
    i++;
  }
 
  scanf( "%d", &k );
  if ( op == 'D' )
    k = k * -1;
  i = 0;
  while ( testo[i]  != '\0' ) {
    modificato[i] = cifra( testo[i], k );
    i++;
  }
 
  printf ( "Testo inserito: %s\n", testo );
  if ( op == 'C')
    printf ( "Testo cifrato:" );
  else
    printf ( "Testo decifrato:");
  printf ( " %s\n", modificato );
  return 0;
}
 
 
char cifra( char c, int k) {
  if ( isalpha( c ) ) {
    if ( k > 0) {
      for (int j=1; j<=k; j++) {
        if ( c != 'z' )
          c++;
        else
          c = 'a';
      }  
    } else {
      for (int j=-1; j>=k; j--) {
        if ( c != 'a' )
          c--;
        else
          c = 'z';
      }
    }
  }
  return c;
}
