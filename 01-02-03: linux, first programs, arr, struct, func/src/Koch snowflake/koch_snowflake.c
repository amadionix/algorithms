#include "libpsgraph.h"
#define LENGTH 110
#define ORDER 7

void KochCurve(double length, int order);

int main() {
  start("prova.ps");
  KochCurve(LENGTH, ORDER);
  end();
  return 0;
}

void KochCurve(double length, int order){
	if (order == 0) 
		draw(length);
	else if (order > 0){
		KochCurve(length / 3, order - 1);
		turn(-60);
		KochCurve(length / 3, order - 1);
		turn(120);
		KochCurve(length / 3, order - 1);
		turn(-60);
		KochCurve(length / 3, order - 1);
	}
}
