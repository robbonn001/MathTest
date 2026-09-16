#pragma once
#include <cstdlib>
#include <ctime>

struct Task {
	int num_1;
	int num_2;
	char operation;
	double answer;
	Task();
	Task(int, int, char operation_ = '\0');
};
class MathTest;
