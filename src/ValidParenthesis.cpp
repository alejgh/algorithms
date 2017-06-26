/*
 * Problem number 20 from leetcode.
 *
 * Given a string containing just the characters '(',
 * ')', '{', '}', '[' and ']', determine if the input string is valid.
 *
 * The brackets must close in the correct order, "()" and "()[]{}"
 * are all valid but "(]" and "([)]" are not.
 *
 */
#include "Stack.h"
#include <iostream>

bool isValid(std::string s)
{
    ds::Stack<char> stack;

    for (auto itr = s.begin(); itr != s.end(); itr++)
    {
        char ch = *itr;
        if (ch == '(')
            stack.Push(')');
        else if (ch == '{')
            stack.Push('}');
        else if (ch == '[')
            stack.Push(']');
        else
            if (stack.IsEmpty() || stack.Pop() != ch)
                return false;
    }

    return true;
}


int main()
{
    std::string valid = "()[]{([()])}";
    std::string invalid = "([{)]}";

    std::cout << "Is '" << valid << "' valid? -> " << (isValid(valid) ? "Yes" : "No") << '\n';
    std::cout << "And is '" << invalid << "' valid? -> " << (isValid(invalid) ? "Yes" : "No") << '\n';
}


