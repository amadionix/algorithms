#include <stdio.h>
#include <string.h>

void Sillaba(char **sentence);


int main(int argc , char **argv){
Sillaba(argv);
}

void Sillaba(char **sentence){
char word[100], *inputWord = sentence[1];
int i = 0;
for(char *p = inputWord; *p != '\0'; p++){
	word[i++] = *p;
	if(*p > *(p+1) && *(p+1) != '\0')
		word[i++] = '-';
	}
word[i] = '\0';	
printf("%s", word);
}



