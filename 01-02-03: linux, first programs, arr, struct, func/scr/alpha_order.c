#include <stdio.h>

int main(){
  char a = 'A';
  char b = 'B';

  scanf("%c %c", &a, &b);

  if (a - 'A' >= 0 && a - 'Z' <= 0 && b - 'A' >= 0 && b - 'Z' <= 0) 
    printf("distance is: %d.\n", b-a);
  else printf("Words were not capital.\n");
  return 0;
}
