#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP

#include "./Token.hpp"
#include "./UnaryRewriter.hpp"
#include <vector> 
#include <cstring>
#include <string>
#include <stack>
#include <iostream>



class Tokenizer {
  private:

  std::vector<Token> tokens;


  bool is_Unary_Operator(char character) {
      // Identify unary operators
      return (character == '+' || character == '-');
  }


  bool is_Operator(char character) {
    //Allows tokenizer to identify if the current character is an operator
    if (character == '+' || character == '-' || character == '/' || character == '*' || character == '(' || character == ')' || character == '^' || character == '%') {
      return true;
    }

    return false;
  }

  bool is_Decimal(char character) {
    // Check if the character is a digit (48 - 57 is the decimal range for ascii digits)
    if (character >= 48 && character <= 57) return true;

    // Check if the character is a decimal point
    if (character == '.') return true;

    // If the character is neither a digit nor a decimal point, return false
    return false;
  }

  void fix_Unary_Operators(ErrorReporter * error_Reporter) {
	UnaryRewriter ur(tokens,error_Reporter);
	ur.fix();
	tokens = ur.get_Tokens();
  }
	
  bool is_Valid_Character(char character) {
      // Allow digits, operators, and whitespaces
      return (isdigit(character) || is_Operator(character) || isspace(character));
  }
  void tokenize(const char * input, ErrorReporter *error_reporter) {
    int operandCount = 0;
    int operatorCount = 0;
         
    int length = strlen(input);

    tokens.push_back(Token('('));

    bool isUnary = true;  // Assume the first operator is unary

    for (int i = 0; i < length;) {
      if (!is_Valid_Character(input[i])) {
          error_reporter->add_error("InfixToPostfix", "Invalid Character");
      }

      if (!is_Decimal(input[i]) && !is_Operator(input[i])) {i++; continue;}
      if (is_Operator(input[i])) {
              if (input[i] == '(') {
                  operatorCount++;
              } else if (input[i] == ')') {
                  operatorCount--;
              } else {
                  operatorCount++;
              }
              tokens.push_back(Token(input[i]));
              i++;
              continue;
          }

          std::string decimal_String;

          while (is_Decimal(input[i])) {
              decimal_String.push_back(input[i]);
              i++;
          }

          tokens.push_back(std::stold(decimal_String));
          operandCount++;
      }

      tokens.push_back(Token(')'));
      fix_Unary_Operators(error_reporter);

      // Check if there are more operands than operators
      if (operandCount > operatorCount*2 && operatorCount > 0) {
          error_reporter->add_error("InfixToPostfix", "Not enough operators."); 
      }
    
  }
  public:

  Tokenizer(const char * input, ErrorReporter * error_reporter) {	
    tokenize(input, error_reporter);
  }

  std::vector<Token> get_Tokens() {return tokens;}


};

class InfixToPostfix {
  private:

  //Higher numbers mean higher priority
    int get_Precedence(char oper) {
    switch (oper) {
      case '-':
      case '+':
        return 1;
      break;

      case '%':
        return 2;
      break;

      case '*':
      case '/':
        return 3;
      break;

      case '^':
        return 4;
      break;

      case '(':
      case ')':
        return -1;
      break;
    }
    return -1;
  }

  //return -1 (op1 < op2)
  //return 0 (op1 == op2)
  //return 1 (op1 > op2)
  int precedence_Compare(char op1, char op2) {
    return ((get_Precedence(op1) > get_Precedence(op2)) - (get_Precedence(op1) < get_Precedence(op2)));
  }
  bool is_Unary(char op){
    return (op == '+' || op == '-');
  }
  public:
std::vector<Token> convert(const char *infix_expression, ErrorReporter *error_reporter) {
    Tokenizer tokenizer(infix_expression, error_reporter);
    std::stack<Token> operator_Stack;
    std::vector<Token> output;
    std::vector<Token> infix_Tokens = tokenizer.get_Tokens();

    int open_Parentheses_Count = 0;
    int close_Parentheses_Count = 0;

    for (const Token &token : infix_Tokens) {
        if (token.is_This_An_Operator()) {
            if (token.get_Operator() == '(') {
                open_Parentheses_Count++;
            } else if (token.get_Operator() == ')') {
                close_Parentheses_Count++;
            }
        }
    }

    if (open_Parentheses_Count != close_Parentheses_Count) {
        error_reporter->add_error("InfixToPostfix", "Unmatched parentheses.");
        return output;  // or handle the error in a way that makes sense for your program
    }

    int infix_Token_Count = infix_Tokens.size();

    for (int i = 0; i < infix_Token_Count; i++) {
        if (!(infix_Tokens[i].is_This_An_Operator())) {
            output.push_back(infix_Tokens[i]);
        } else {
            char oper = infix_Tokens[i].get_Operator();

            if (oper == '(') {
                operator_Stack.push(infix_Tokens[i]);
            } else if (oper == ')') {
                while (!operator_Stack.empty() && operator_Stack.top().get_Operator() != '(') {
                    output.push_back(operator_Stack.top());
                    operator_Stack.pop();
                }

                // Pop the '(' from the stack
                operator_Stack.pop();
            } else {
                // Check if the operator is unary and handle it accordingly
                if (is_Unary(oper)) {
                    // Handle unary operator
                    while (!operator_Stack.empty() && precedence_Compare(oper, operator_Stack.top().get_Operator()) <= 0) {
                        output.push_back(operator_Stack.top());
                        operator_Stack.pop();
                    }
                    operator_Stack.push(infix_Tokens[i]);  // Push the unary operator onto the stack
                } else {
                    // Check if the operator stack is not empty and the precedence of the current operator is less than or equal to the precedence of the operator on top of the stack
                    if (!operator_Stack.empty() && precedence_Compare(oper, operator_Stack.top().get_Operator()) <= 0) {
                        // Pop all operators with greater or equal precedence at the top of
                        // the stack
                        while (!operator_Stack.empty() && precedence_Compare(oper, operator_Stack.top().get_Operator()) <= 0) {
                            output.push_back(operator_Stack.top());
                            operator_Stack.pop();
                        }

                        // Push the new operator to the operator stack
                        operator_Stack.push(infix_Tokens[i]);
                    } else {
                        // If the operator stack is empty or there isn't anything with greater
                        // or equal precedence at the top of the stack, push the current token
                        // onto the stack.
                        operator_Stack.push(infix_Tokens[i]);
                    }
                }
            }
        }
    }

    while (!operator_Stack.empty()) {
        output.push_back(operator_Stack.top());
        operator_Stack.pop();
    }

    return output;
}


};
#endif
