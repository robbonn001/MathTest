#include "pch.h"
#include "MathTest.h"

TEST(TaskConstructor, DefaultConstructorGeneratesValidTask) {
    Task task;

    EXPECT_GE(task.num_1, 1);
    EXPECT_LE(task.num_1, 100);
    EXPECT_GE(task.num_2, 1);
    EXPECT_LE(task.num_2, 100);

    bool validOp = (task.operation == '+' || task.operation == '-' ||
        task.operation == '*' || task.operation == '/');
    
    EXPECT_TRUE(validOp) << "Неверная операция: " << task.operation;
}

TEST(TaskConstructor, ParameterizedConstructorRespectsRange) {
    Task task(10, 50);

    EXPECT_GE(task.num_1, 10);
    EXPECT_LE(task.num_1, 50);
    EXPECT_GE(task.num_2, 10);
    EXPECT_LE(task.num_2, 50);
}

TEST(TaskConstructor, SpecificOperationIsSet) {
    Task task(1, 10, '+');

    EXPECT_EQ('+', task.operation);
    EXPECT_EQ(task.num_1 + task.num_2, task.answer);
}

TEST(TaskConstructor, DivisionByZeroThrowsException) {
    EXPECT_THROW(Task(0, 0, '/'), std::runtime_error);
}

TEST(TaskConstructor, InvalidRangeThrowsException) {
    EXPECT_THROW(Task(100, 1), std::invalid_argument);
}

TEST(MathTestConstructor, CreatesCorrectSize) {
    MathTest test(5);
    EXPECT_EQ(test.getCount(), 5);
    EXPECT_EQ(test.getCorrectCount(), 0);
}

TEST(MathTestConstructor, WithRangeCreatesValidTasks) {
    MathTest test(3, 10, 20);

    for (int i = 0; i < 3; ++i) {
        const Task& t = test.getTask(i);
        EXPECT_GE(t.num_1, 10);
        EXPECT_LE(t.num_1, 20);
        EXPECT_GE(t.num_2, 10);
        EXPECT_LE(t.num_2, 20);
    }
}

TEST(MathTestConstructor, WithOperationSetsCorrectOp) {
    MathTest test(4, 1, 10, '*');

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(test.getTask(i).operation, '*');
    }
}

TEST(MathTestConstructor, InvalidSizeThrows) {
    EXPECT_THROW(MathTest(0), std::invalid_argument);
    EXPECT_THROW(MathTest(-5), std::invalid_argument);
}

TEST(MathTestSubmitAnswer, CorrectAnswerIncrementsCount) {
    MathTest test(3, 1, 10, '+');

    const Task& t = test.getTask(0);
    bool result = test.submitAnswer(0, t.answer);

    EXPECT_TRUE(result);
    EXPECT_EQ(test.getCorrectCount(), 1);
    EXPECT_EQ(test.getUserAnswer(0), t.answer);
}

TEST(MathTestSubmitAnswer, WrongAnswerDoesNotIncrement) {
    MathTest test(3, 1, 10, '+');

    const Task& t = test.getTask(0);
    bool result = test.submitAnswer(0, t.answer + 1);

    EXPECT_FALSE(result);
    EXPECT_EQ(test.getCorrectCount(), 0);
}

TEST(MathTestSubmitAnswer, OutOfRangeThrows) {
    MathTest test(3);

    EXPECT_THROW(test.submitAnswer(-1, 0), std::out_of_range);
    EXPECT_THROW(test.submitAnswer(3, 0), std::out_of_range);
}

TEST(MathTestCalculateMark, ReturnsCorrectGrades) {
    EXPECT_EQ(MathTest::calculateMark(9, 10), 5);
    EXPECT_EQ(MathTest::calculateMark(7, 10), 4);
    EXPECT_EQ(MathTest::calculateMark(5, 10), 3);
    EXPECT_EQ(MathTest::calculateMark(3, 10), 2);
    EXPECT_EQ(MathTest::calculateMark(1, 10), 1);
}

TEST(MathTestCalculateMark, ZeroTotalReturns0) {
    EXPECT_EQ(MathTest::calculateMark(0, 0), 0);
}

TEST(MathTestGetters, WorkCorrectly) {
    MathTest test(2, 5, 15, '-');

    EXPECT_EQ(test.getCount(), 2);
    EXPECT_EQ(test.getCorrectCount(), 0);

    const Task& t0 = test.getTask(0);
    EXPECT_GE(t0.num_1, 5);
    EXPECT_LE(t0.num_1, 15);
    EXPECT_EQ(t0.operation, '-');
}