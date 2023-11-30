/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

#ifndef POSTFIXEVALUATOR_HPP
#define POSTFIXEVALUATOR_HPP

#include "./Token.hpp"
#include "./ErrorReporter.hpp"

#include <vector>
#include <stack>
#include <cmath>

class PostfixEvaluator {
  private:

  std::stack<long double> number_Stack;

  //If error occurred, return false, otherwise true
  bool perform_Operation(char operation, ErrorReporter * error_reporter) {
    if (number_Stack.size() < 2) {
        error_reporter->add_error("PostfixEvaluator", "Not enough operands for operation.");
        return false;
    }
    long double operand_Two = number_Stack.top();
    number_Stack.pop();

    long double operand_One = number_Stack.top();
    number_Stack.pop();

    long double result; 

    switch (operation) {
      case '+': 
        result = operand_One + operand_Two;
      break;

      case '-': 
        result = operand_One - operand_Two;
      break;

      case '/':
        if (operand_Two == 0.0) {
          error_reporter->add_error("PostfixEvaluator", "Division by zero is invalid.");
          return false;
        }

        result = operand_One / operand_Two;
      break;

      case '*': 
        result = operand_One * operand_Two;
      break;

      case '^': 
        result = pow(operand_One, operand_Two);
      break;

      case '%': 
        if (operand_Two == 0.0) {
          error_reporter->add_error("PostfixEvaluator", "Modulus by zero is invalid.");
          return false;
        }else{
          result = fmod(operand_One, operand_Two);
        }
      break;
    }

    number_Stack.push(result);
    return true;
  }

  public:

  long double evaluate(std::vector<Token> postfix_Expression, ErrorReporter * error_reporter) {
    int token_Count = postfix_Expression.size();

    for (int i = 0; i < token_Count; i++) {

      Token token = postfix_Expression.front();
      postfix_Expression.erase(postfix_Expression.begin());

      if (token.is_This_An_Operator()) {
        perform_Operation(token.get_Operator(), error_reporter);
      } else {
        number_Stack.push(token.get_Operand());
      }
    }

    if (!number_Stack.empty()) {
        long double result = number_Stack.top();
        number_Stack.pop();
        return result;
    } else {
        // Handle the case where the stack is empty, report an error or return a default value.
        
        return 0.0; // or any appropriate default value
    }
  }
};

#endif
