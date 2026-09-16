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
    
    EXPECT_TRUE(validOp) << "invalid operation: " << task.operation;
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