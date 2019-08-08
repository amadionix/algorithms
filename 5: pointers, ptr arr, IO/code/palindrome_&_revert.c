#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool IsPalindrome(char * word, int len);
void Revert(char * word, int len);

int main(){
  char word[] = "aladina";
  int n = strlen(word);
  bool x = IsPalindrome(word, n);
  printf("%s", x ? "it is\n" : "it's not\n");
  Revert(word, n);
  printf("%s", word);
}

void Revert(char *word, int len) {
  char newWord[len];
  char *i = word + len - 1;
  char *j = newWord;
  while (i > word) {
	  *j = *i;
	  j++;
	  i--;
	}
  *j = *i;
  strcpy(word, newWord);
}

bool IsPalindrome(char * word, int len) {
  char *r = word + len - 1;
  char *l = word;
  while (l < r) {
	  if (*l != *r) return false; 
	  l++;
	  r--;
	}
  return true;	
}

