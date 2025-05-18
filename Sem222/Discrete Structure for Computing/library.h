#ifndef library_h
#define library_h

// #include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

bool isOperator(char c)
{ return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

bool isLogicOperator(char c) 
{ return (c == '&' || c == '|' || c=='-' || c=='<'); }

int getPrecedence(char op) 
{
    switch (op) 
    {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default : return 0;
    }
}

int getLogicPrecedence(string op) 
{
    if (op == "~")
        return 3;
    if (op == "&" || op == "|") 
        return 2;
    if (op == "<->")
        return 1;
    if (op == "->")
        return 0;
    return -1;
}


void checkInfixValidity(string expression) 
{
    // Check for consecutive operators
    for (size_t i = 0; i < expression.length() - 1; i++)
        if (isOperator(expression[i]) && isOperator(expression[i+1]) && expression[i] != '-' && expression[i+1] != '-')
            throw runtime_error("Undefined error");


    // Check for precedence order
    for (size_t i = 0; i < expression.length() - 1; i++)
        if (isOperator(expression[i]) && isOperator(expression[i+1]) && expression[i] != '-' && expression[i+1] != '-')
            if (getPrecedence(expression[i]) < getPrecedence(expression[i+1])) 
                throw runtime_error("Multiple-output error");


    // Check for parenthesis
    int openCount = 0, closeCount = 0;
    for (size_t i = 0; i < expression.length(); i++) 
    {
        if (expression[i] == '(')       
            openCount++;
        else if (expression[i] == ')')  
            closeCount++;
        if (closeCount > openCount)
            throw runtime_error("Syntax error");
    }
    if (openCount != closeCount)
        throw runtime_error("Syntax error");

    // Check for floating point errors
    for (size_t i = 0; i < expression.length() - 1; i++) 
    {
        if (expression[i] == '.' && expression[i+1] == '.')
            throw runtime_error("Syntax error");
        
        if (expression[i] == '+' && expression[i+1] == '.')
            throw runtime_error("Syntax error");
    }
    return;
}

void checkLogicInfixValidity(string expression) 
{
    // // Check for consecutive operators
    // for (size_t i = 0; i < expression.length() - 1; i++)
    //     if (isLogicOperator(expression[i]) && isLogicOperator(expression[i+1]))
    //         throw runtime_error("Consecutive operators");

    // // Check for precedence order
    // for (size_t i = 0; i < expression.length() - 1; i++)
    // {
    //     if (isLogicOperator(expression[i]) && isLogicOperator(expression[i+1]))
    //     {
    //         string currentOperator = string(1, expression[i]);
    //         string nextOperator = string(1, expression[i+1]);

    //         if (getLogicPrecedence(currentOperator) < getLogicPrecedence(nextOperator)) 
    //             throw runtime_error("Incorrect precedence order");
    //     }
    // }

    // // Check for parenthesis
    // int openCount = 0, closeCount = 0;
    // for (size_t i = 0; i < expression.length(); i++) 
    // {
    //     if (expression[i] == '(')       
    //         openCount++;
    //     else if (expression[i] == ')')  
    //         closeCount++;
    //     if (closeCount > openCount)
    //         throw runtime_error("Mismatched parentheses");
    // }
    // if (openCount != closeCount)
    //     throw runtime_error("Mismatched parentheses");

    return;
}

void checkVariablesValidity (string expression, string variables)
{
    unordered_set <char> chars (expression.begin(), expression.end());

    for (char c : chars) // Check if variables match with expression
    {
        if (!std::isalpha(c)) continue;  // Skip non-letter characters
        if ((isalpha(c) && variables.find(c) == string::npos))
            throw runtime_error("Invalid Values"); 
    }
    for (char c : variables)
        if (isalpha(c)) return;

    throw runtime_error("Invalid Values"); // No variables found
}


#endif
