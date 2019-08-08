#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void PalindromeBash(int argc, char **sentence, int *res);
bool IsPalindrome(char * word, int len);

int main(int argc, char **argv) {
  int res[argc-2];
  int wordsNum = argc - 1;
  for (int k = 0; k < wordsNum; k++) res[k] = 0;
  PalindromeBash(wordsNum, argv, res);
  for (int k = 0; k < wordsNum; k++)
	  printf("%d", res[k]);
}

void PalindromeBash(int argc, char **sentence, int *res) {
  int slen = 0, i = 0;
  for (char **q = &sentence[1]; *q != NULL; q++, i++) { 
	  slen = strlen(*q);
	  if(IsPalindrome(*q, slen))
		  res[i] = 1;
	}
}

bool IsPalindrome(char *word, int len){
  char *r = word + len - 1;
  char *l = word;
  while(l < r){
	  if(*l != *r) return false; 
	  l++;
	  r--;
	}
  return true;	
}
