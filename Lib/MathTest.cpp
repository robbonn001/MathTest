#include "MathTest.h"

Task::Task() {
	num_1 = rand() % 100;
	num_2 = rand() % 100;
	int num = rand()%4;
	switch (num) {
	case 0: operation = '+'; break;
	case 1: operation = '-'; break;
	case 2: operation = '*'; break;
	case 3: operation = '/'; break;
	}
}

Task::Task(int min, int max, char operation_ = '\0'){
	num_1 = rand() % (max - min) + min;
	num_2 = rand() % (max - min) + min;
	
	switch (num) {
	case 0: operation = '+'; break;
	case 1: operation = '-'; break;
	case 2: operation = '*'; break;
	case 3: operation = '/'; break;
	}
}

