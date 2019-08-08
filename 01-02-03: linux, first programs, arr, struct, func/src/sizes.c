#include <stdio.h>


int main(){
  int g = sizeof(int);
  int h = sizeof(short int);
  int a = sizeof(long int);
  int b = sizeof(long double);
  int c = sizeof(char);
  int e = sizeof(unsigned);
  int f = sizeof(float);
  printf("int: %d, short int: %d, long int: %d, long double: %d, char: %d, unsigned: %d, float: %d", g, h, a, b, c, e, f);
  return 0;
}
