#include <stdio.h>

// calcolo divisori di input
int main(){

int input = 0;
scanf( "%d", &input );

for( int i = input; i > 0; i--)
	if( input % i == 0 ) printf( "%d", i );
	
return 0;
}	

// input e' primo?
int main(){

int input = 0;
int j = 0;
scanf( "%d", &input );

for( int i = input / 2; i > 1; i--)
	if( input % i == 0 ) j++;
	
if( j == 0 ) printf("e' primo\n");

return 0;
}
