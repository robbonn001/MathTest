#include "MathTest.h"
#include <stdexcept>

static bool seedInitialized = false;

Task::Task(int min, int max, char operation_) {
	if (!seedInitialized) {
		std::srand(std::time(nullptr));
		seedInitialized = true;
	}

	if (min > max) {
		throw std::invalid_argument("min не может быть больше max");
	}

	num_1 = std::rand() % (max - min) + min;
	num_2 = std::rand() % (max - min) + min;

	if (operation_ == '\0') {
		const char operations[] = { '+', '-', '*', '/' };
		operation = operations[std::rand() % 4];
	}
	else {
		operation = operation_;
	}

	switch (operation) {
	case '+':
		answer = num_1 + num_2;
		break;
	case '-':
		answer = num_1 - num_2;
		break;
	case '*':
		answer = num_1 * num_2;
		break;
	case '/':
		if (num_2 == 0) {
			throw std::runtime_error("Деление на ноль");
		}
		answer = num_1 / num_2;
		break;
	default:
		throw std::invalid_argument("Неизвестная операция");
	}
}

Task::Task():Task(1,100) {}
