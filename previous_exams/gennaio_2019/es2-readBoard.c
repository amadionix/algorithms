#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *createJumps( int, int );


int main() {
	int r, c; 
	scanf( "%d%d", &r, &c);
	
	int *jump = createJumps( r, c );

	int n = r*c ;
	printf( "%d\n", n );
	for ( int i = 1; i <= n; i++ )	
		printf( "%d ", jump[i] );
	printf( "\n" );
	
	return 0;
}

int *createJumps( int r, int c ){
	int n = r * c;
	int *jump = calloc( n + 1, sizeof(int) ); // e' un array di interi, non c'e' 
	                                       // motivo di avere puntatori a int
	
	int s, m, t;
	scanf( "%d", &s );
	while ( s-- > 0) {	        // deve decrementare altrimenti il loop non va
		scanf( "%d %d", &m, &t );
		jump[m] = t;              // il serpente sposta dalla mouth m alla tail t
		                          // se all'elemento i-esimo c'e' scritto dove si 
		                          // deve andare dopo... mouth -> tail
	}

	
	// lettura delle scale
	int l, start, len;
	scanf( "%d", &l );
	for (int i = 0; i < l; i++ ) {	
		scanf( "%d%d", &start, &len );

		int row, col, end;
		row = r - 1 - (start-1)/c;
		col = (start-1) % c;
		printf("\ncol,row: %d %d\n", col, row);
		if ( ( row + r ) % 2 == 0 ) // casella su riga crescente verso xx
			col = c - 1 - col; // BACO: off-by-one

		row = row - len + 1;
		end = c * ( r - row );
		if ( ( row + r ) % 2 == 0  )
			end -= col;
		else 
			end += col - c + 1;
		
		jump[start] = end;
	}
	return jump;
}








