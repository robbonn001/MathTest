#include <iostream>
#include "MathTest.h"
#include <windows.h>

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

    std::cout << "--- Тест 1: Базовый конструктор (5 вопросов) ---\n";
    {
        MathTest test1(5);
        test1.run();
    }

    std::cout << "\n---------------------------------------------\n\n";

    std::cout << "--- Тест 2: Диапазон [1, 20] (3 вопроса) ---\n";
    {
        MathTest test2(3, 1, 20);
        test2.run();
    }

    std::cout << "\n---------------------------------------------\n\n";

    std::cout << "--- Тест 3: Только умножение [2, 9] (4 вопроса) ---\n";
    {
        MathTest test3(4, 2, 9, '*');
        test3.run();
    }

    return 0;
}