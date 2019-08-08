#include <stdio.h>
#define N 100

int main(){

  typedef struct {
	  int day;
	  int month;
	  int year;
	} Date;
	  
  Date cal[N];
  Date nul = {00, 00, 0000};
  Date in = {00, 00, 0000};

  int i = 0;
  scanf("%d/%d/%d", &in.day, &in.month, &in.year);
  while(in.day != nul.day && in.month != nul.month && in.year != nul.year){
	  cal[i].day = in.day;
	  cal[i].month = in.month;
	  cal[i].year = in.year;
	  i++;
	  scanf("%d/%d/%d", &in.day, &in.month, &in.year);
  }
  cal[i] = nul;

  for(int j = 0; j < i; j++) 
	  printf("%02d/%02d/%04d\n", cal[j].day, cal[j].month, cal[j].year);

  return 0;
}
