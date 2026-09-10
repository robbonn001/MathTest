#pragma once
#include <cmath>
struct Task {
	int num_1;
	int num_2;
	char operation;
	double answer;
	Task();
	Task(int min, int max, char operation_ = '\0');
};
class MathTest;


