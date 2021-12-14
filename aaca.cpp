#include <iostream>

#include "algo.h"
#include <cstdlib>

int main(int argc, char* argv[]) {
	srand(NULL);
	Graham g,h;
	time_t time1, time2, time3, time4;
	std::vector<Point> data1;
	std::vector<Point> data2;
	for (int i = 0; i < 2500000; i++) {
		Point p;
		p.x = rand() % 1000;
		p.y = rand() % 1000;
		data1.push_back(p);
		data2.push_back(p);
	}
	g.BuildVector(data1);
	time1 = clock();
	g.QuickHullPrint();
	time2 = clock();
	printf("time : %d\n\n", time2 - time1);
	h.BuildVector(data2);
	time3 = clock();
	h.HeapHullPrint();
	time4 = clock();
	printf("time : %d\n\n", time4 - time3);
	return 0;
}