#include "MathTest.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

static bool seedInitialized = false;

Task::Task(int min, int max, char operation_) {
	if (!seedInitialized) {
		std::srand(std::time(nullptr));
		seedInitialized = true;
	}

	if (min > max) {
		throw std::invalid_argument("min не может быть больше max");
	}

	if (min == max) {
		throw std::runtime_error("min и max не могут быть равны");
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

void MathTest::allocateMemory(int size) {
	if (size <= 0) {
		throw std::invalid_argument("Размер теста должен быть положительным");
	}
	count = size;
	tasks = new Task[count];
	user_answers = new int[count]();
	correct_count = 0;
}

void MathTest::freeMemory() {
	delete[] tasks;
	delete[] user_answers;
	tasks = nullptr;
	user_answers = nullptr;
	count = 0;
	correct_count = 0;
}

MathTest::MathTest(int size) {
	allocateMemory(size);
	for (int i = 0; i < count; ++i) {
		tasks[i] = Task(); // Базовый конструктор Task
	}
}

MathTest::MathTest(int size, int min, int max) {
	allocateMemory(size);
	for (int i = 0; i < count; ++i) {
		tasks[i] = Task(min, max);
	}
}

MathTest::MathTest(int size, int min, int max, char operation) {
	allocateMemory(size);
	for (int i = 0; i < count; ++i) {
		tasks[i] = Task(min, max, operation);
	}
}

MathTest::~MathTest() {
	freeMemory();
}

bool MathTest::submitAnswer(int index, int answer) {
	if (index < 0 || index >= count) {
		throw std::out_of_range("Индекс вне диапазона");
	}

	user_answers[index] = answer;

	if (answer == tasks[index].answer) {
		++correct_count;
		return true;
	}
	return false;
}

const Task& MathTest::getTask(int index) const {
	if (index < 0 || index >= count) {
		throw std::out_of_range("Индекс вне диапазона");
	}
	return tasks[index];
}

int MathTest::getUserAnswer(int index) const {
	if (index < 0 || index >= count) {
		throw std::out_of_range("Индекс вне диапазона");
	}
	return user_answers[index];
}

int MathTest::getCorrectCount() const {
	return correct_count;
}

int MathTest::getCount() const {
	return count;
}

int MathTest::calculateMark(int correct, int total) {
	if (total <= 0) return 0;

	double percentage = (static_cast<double>(correct) / total) * 100.0;

	if (percentage > 80) return 5;
	if (percentage > 60) return 4;
	if (percentage > 40) return 3;
	if (percentage > 20) return 2;
	return 1;
}

void MathTest::run() {
	std::cout << "Начинаем тест из " << count << " вопросов.\n\n";
	int answer;
	for (int i = 0; i < count; ++i) {
		std::cout << "Вопрос " << (i + 1) << ": " << tasks[i].num_1 << " " << tasks[i].operation << " " << tasks[i].num_2 << " = ";
		std::cin >> answer;
		submitAnswer(i, answer);
	}

	std::cout << "\nТест завершён.\n\n";
	showStatistics();
}

void MathTest::showStatistics() const {
	const int colWidth = 12;

	// Заголовок с номерами
	std::cout << "|" << std::setw(colWidth) << "No" << "|";
	for (int i = 0; i < count; ++i) {
		std::cout << std::setw(colWidth) << (i + 1) << "|";
	}
	std::cout << "\n+";
	for (int i = 0; i <= count; ++i) {
		for (int j = 0; j < colWidth; ++j) std::cout << "-";
		std::cout << "+";
	}
	std::cout << "\n";

	// Question
	std::cout << "|" << std::setw(colWidth) << "Question" << "|";
	for (int i = 0; i < count; ++i) {
		std::string q = std::to_string(tasks[i].num_1) + " " + tasks[i].operation + " " + std::to_string(tasks[i].num_2);
		std::cout << std::setw(colWidth) << q << "|";
	}
	std::cout << "\n";

	// True Answer
	std::cout << "|" << std::setw(colWidth) << "True Answer" << "|";
	for (int i = 0; i < count; ++i) {
		std::cout << std::setw(colWidth) << tasks[i].answer << "|";
	}
	std::cout << "\n";

	// Your Answer
	std::cout << "|" << std::setw(colWidth) << "Your Answer" << "|";
	for (int i = 0; i < count; ++i) {
		std::cout << std::setw(colWidth) << user_answers[i] << "|";
	}
	std::cout << "\n";

	// Result
	std::cout << "|" << std::setw(colWidth) << "Result" << "|";
	for (int i = 0; i < count; ++i) {
		char res = (user_answers[i] == tasks[i].answer) ? '+' : '-';
		std::cout << std::setw(colWidth) << res << "|";
	}
	std::cout << "\n\n";

	// Итог
	char mark = calculateMark(correct_count, count);
	std::cout << "Total Result: " << correct_count << " / " << count << " (mark: " << mark << ")\n";
}