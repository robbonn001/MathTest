#pragma once
#include <cstdlib>
#include <ctime>

struct Task {
	int num_1;
	int num_2;
	char operation;
	int answer;
	Task();
	Task(int, int, char operation_ = '\0');
};
class MathTest {
	Task* tasks;
	int count;
	int* user_answers;
	int correct_count;

	// Вспомогательный метод для инициализации памяти
	void allocateMemory(int size);

	// Вспомогательный метод для очистки памяти
	void freeMemory();

public:
	MathTest(int size);
	MathTest(int size, int min, int max);
	MathTest(int size, int min, int max, char operation);

	~MathTest();

	MathTest(const MathTest&) = delete;
	MathTest& operator=(const MathTest&) = delete;

	void run();

	void showStatistics() const;

	// Принять ответ пользователя и обновить статистику
	bool submitAnswer(int index, int answer);

	const Task& getTask(int index) const;

	int getUserAnswer(int index) const;

	int getCorrectCount() const;

	// Получить общее количество вопросов
	int getCount() const;

	// Вычислить оценку на основе процента правильных ответов
	static int calculateMark(int correct, int total);
};
