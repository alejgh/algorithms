#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Stack.h"
#include "Utils.h"

TEST_CASE("Simple stack test.") {
    ds::Stack<int> stack;
    stack.Push(5);
    stack.Push(7);
    stack.Push(9);
    REQUIRE(stack.Peek() == 9);
    ds::Stack<int> anotherStack(stack);
    REQUIRE(anotherStack.Peek() == 9);
    anotherStack.Pop();
    REQUIRE(anotherStack.Peek() == 7);
    REQUIRE(stack.Peek() == 9);
    utils::CheckString(stack, "[9, 7, 5]");
    utils::CheckString(anotherStack, "[7, 5]");
    anotherStack = stack;
    utils::CheckString(stack, "[9, 7, 5]");
    utils::CheckString(anotherStack, "[9, 7, 5]");
    REQUIRE(stack.Pop() == 9);
    REQUIRE(stack.Pop() == 7);
    REQUIRE(stack.Pop() == 5);
    anotherStack.Push(1);
    anotherStack.Push(2);
    utils::CheckString(stack, "[]");
    utils::CheckString(anotherStack, "[2, 1, 9, 7, 5]");
}



