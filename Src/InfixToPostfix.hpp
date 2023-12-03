//Include guard to prevent multiple inclusion of the INFIX_TO_POSTFIX_HPP header file
#ifndef INFIX_TO_POSTFIX_HPP
//If INFIX_TO_POSTFIX_HPP is not defined, define it to avoid multiple inclusion of the header file
#define INFIX_TO_POSTFIX_HPP

//Include Token header file, which will allow the use of declarations and definitions from that file
#include "./Token.hpp"
//Include UnaryRewriter header file, which will allow the use of declarations and definitions from that file
#include "./UnaryRewriter.hpp"
//Include the vector header file, providing functionalities for working with vectors
#include <vector>
//Include cstring allows for useful string manipulation functions
#include <cstring>
//Include the string header file, providing functionalities for working with strings
#include <string>
//Include this header for the C++ stack
#include <stack>
//Include the iostream header file, providing functionalities for input and output using streams
#include <iostream>


//This is the Tokenizer Class
class Tokenizer {
  private:
  //Vector to store Token objects
  std::vector<Token> tokens;
  //Function to check if a character is unary operator
  bool is_Unary_Operator(char character) {
      // Identify unary operators
      return (character == '+' || character == '-');
  }

  //This function will return a boolean value depending on if the characteer is an operator
  bool is_Operator(char character) {
    //Allows tokenizer to identify if the current character is an operator
    if (character == '+' || character == '-' || character == '/' || character == '*' || character == '(' || character == ')' || character == '^' || character == '%') {
      //If true, it'll return true
      return true;
    }
    //If the character is not one of the operators it'll return false
    return false;
  }
  //This function will return a boolean value depending on if the character is a decimal
  bool is_Decimal(char character) {
    // Check if the character is a digit (48 - 57 is the decimal range for ascii digits)
    if (character >= 48 && character <= 57) return true;

    // Check if the character is a decimal point
    if (character == '.') return true;

    // If the character is neither a digit nor a decimal point, return false
    return false;
  }
  //This function will fix the unary operators in the expression
  //Takes an ErrorReporter pointer as a parameter
  void fix_Unary_Operators(ErrorReporter * error_Reporter) {
  //Creates a UnaryRewriter object with the 'tokens' vector and the provided ErrorReporter pointer
  UnaryRewriter ur(tokens,error_Reporter);
  //Apply the fix method of the Unary Rewriter to handle unary operators
  ur.fix();
  //Updates token with the modified tokens from the UnaryRewriter
  tokens = ur.get_Tokens();
  }
  //This function will return a boolean value depending on if the character is a valid character or not
  bool is_Valid_Character(char character) {
      // Allow digits, operators, and whitespaces, or decimal number
      return (isdigit(character) || is_Operator(character) || isspace(character) || is_Decimal(character));
  }
  void tokenize(const char * input, ErrorReporter *error_reporter) {
    //Initializes operandCount with zero which will count the amount of operands
    int operandCount = 0;
    //Initializes operatorCount with zero which will count the amount of operators
    int operatorCount = 0;

    //Gets the length of the input
    int length = strlen(input);
    //Push an opening parenthesis to the back of tokens
    tokens.push_back(Token('('));

    bool isUnary = true;  // Assume the first operator is unary
    //Uses a for in loop to iterate through the user input
    for (int i = 0; i < length;) {
      //Checks to see if the that character at a certain index is not a vaild character
      if (!is_Valid_Character(input[i])) {
        //Adds an error to the error_reporter using the add_error function that tells the user there is an invalid character
        error_reporter->add_error("InfixToPostfix", "Invalid Character");
      }
      //If the character is not a decimal and not an operator it'll continue to the next iteration
      if (!is_Decimal(input[i]) && !is_Operator(input[i])) {i++; continue;}
      //If the character is an operator
      if (is_Operator(input[i])) {
              //Checks to see if the character is an opening paraenthesis
              if (input[i] == '(') {
                //Adds 1 to the operatorCount
                operatorCount++;
              //Checks to see if the character is a closing parenthesis
              } else if (input[i] == ')') {
                //Minus 1 to the operatorCount
                operatorCount--;
              //Otherwise it'll be one of the other operators
              } else {
                //Adds 1 to the operatorCount
                operatorCount++;
              }
              //Pushs that character to the back of the tokens vector
              tokens.push_back(Token(input[i]));
              //increments 1 to i
              i++;
              //continue to the next iteration of the loop
              continue;
          }
          //This is a string that'll accumlate characters forming a decimal
          std::string decimal_String;
          //While the current character is a decimal digit or a decimal point
          while (is_Decimal(input[i])) {
              //Appends the current character to the decimal string
              decimal_String.push_back(input[i]);
              //Increments 1 to move to the next character
              i++;
          }
          //Convert the accumulated decimal string to a floating-point number and add it to the Tokens vector
          tokens.push_back(std::stold(decimal_String));
          //increment the operand count
          operandCount++;
      }
      //Appends a closing parenthesis to the Tokens vector
      tokens.push_back(Token(')'));
      //Fix unary operators in the Tokens vector
      fix_Unary_Operators(error_reporter);

      // Check if there are more operands than operators
      if (operandCount > operatorCount*2 && operatorCount > 0) {
          //It'll add an error to the error_reporter saying there is not enough operators
          error_reporter->add_error("InfixToPostfix", "Not enough operators."); 
      }

  }
  public:
  //Constructor for the Tokenizer class
  Tokenizer(const char * input, ErrorReporter * error_reporter) {	
    //Tokenize the input string and handle errors using the provided ErrorReporter
    tokenize(input, error_reporter);
  }
  //This member function will get the Tokens
  //Returns the vector of tokens
  std::vector<Token> get_Tokens() {return tokens;}


};

class InfixToPostfix {
  private:

  //Higher numbers mean higher priority
    //This function will return the precedence of the operator
    int get_Precedence(char oper) {
    //Uses a switch statement
    switch (oper) {
      //If the operator is '+' or '-' it'll return 1 as the precedence
      case '-':
      case '+':
        return 1;
      break;
      //If the operator is '%' it'll return 2 as the precedence
      case '%':
        return 2;
      break;
      //If the operator is '*' or '/' it'll return 3 as the precedence
      case '*':
      case '/':
        return 3;
      break;
      //If the operator is '^' or it'll return 4 as the precedence
      case '^':
        return 4;
      break;
      //If the operator is '(' or ')' it'll return -1 as the precedence
      case '(':
      case ')':
        return -1;
      break;
    }
    //If it isn't one of those it'll also return -1
    return -1;
  }

  //return -1 (op1 < op2)
  //return 0 (op1 == op2)
  //return 1 (op1 > op2)
  int precedence_Compare(char op1, char op2) {
    return ((get_Precedence(op1) > get_Precedence(op2)) - (get_Precedence(op1) < get_Precedence(op2)));
  }
  //This function will return a boolean value depending on if it's an Unary operator or not
  bool is_Unary(char op){
    return (op == '+' || op == '-');
  }
  public:
//Function converts from infix to postfix
  std::vector<Token> convert(const char *infix_expression, ErrorReporter *error_reporter) {
    //Create a Tokenizer object to tokenize the infix expression
    Tokenizer tokenizer(infix_expression, error_reporter);
    //Stack to hold operators
    std::stack<Token> operator_Stack;
    //Vector to store the result
    std::vector<Token> output;
    //Retrieve the vector of Token from the Tokenizer
    std::vector<Token> infix_Tokens = tokenizer.get_Tokens();
    //Initializes the open_Parentheses_Count to zero which will count the number of open parentheses
    int open_Parentheses_Count = 0;
    //Initializes the close_Parentheses_Count to zero which will count the number of closee parentheses 
    int close_Parentheses_Count = 0;
    //Loop through each token in the infix expression
    for (const Token &token : infix_Tokens) {
      //Checks to see if the token is an operator
      if (token.is_This_An_Operator()) {
        //Checks to see if the operator is an open parenthesis
        if (token.get_Operator() == '(') {
          //If true, it'll increment open_Parentheses_Count by one
          open_Parentheses_Count++;
        //Checks to see if the operator is a closed parenthesis
        } else if (token.get_Operator() == ')') {
          //If true, it'll increment close_Parentheses_Count by one
          close_Parentheses_Count++;
        }
      }
    }
    //Checks to see if the number of open_Parentheses_Count is not equal to close_Parentheses_Count
    if (open_Parentheses_Count != close_Parentheses_Count) {
      //Adds the error to error_reporter which will tell the user there are Unmatched parentheses
      error_reporter->add_error("InfixToPostfix", "Unmatched parentheses.");
      return output;  // returns the output to stop computation
    }
    //Gets the size of the infix_Tokens
    int infix_Token_Count = infix_Tokens.size();
    //Uses a for loop to iterate through the infix_Token_Count
    for (int i = 0; i < infix_Token_Count; i++) {
      //Checks to see if the Token is Not an operator
      if (!(infix_Tokens[i].is_This_An_Operator())) {
        //If true, it'll be pushed to the back of the output vector
        output.push_back(infix_Tokens[i]);
      } else {
        //If false, well create an variable that hold that operator
        char oper = infix_Tokens[i].get_Operator();
        //Checks to see if the operator is an opening parenthesis
        if (oper == '(') {
          //If true, it'll push it to the top of the operator stack
          operator_Stack.push(infix_Tokens[i]);
        //Checks to see if the operator is a closing parenthesis
        } else if (oper == ')') {
          //If true, if the operator stack is not empty AND the top operator is not an opening parenthesis
          while (!operator_Stack.empty() && operator_Stack.top().get_Operator() != '(') {
            //It'll push the top of the operator_Stack to the back of the output 
            output.push_back(operator_Stack.top());
            //Pops the top of the operator_Stack
            operator_Stack.pop();
          }

          // Pop the '(' from the stack
          operator_Stack.pop();
        } else {
          // Check if the operator is unary and handle it accordingly
          if (is_Unary(oper)) {
            // If true, if the operator stack is not empty AND if the precedence of the current operator is less than or eqaul to zero
            while (!operator_Stack.empty() && precedence_Compare(oper, operator_Stack.top().get_Operator()) <= 0) {
              //Push the top of the operator stack to the back of the output
              output.push_back(operator_Stack.top());
              //Pops the top of the operator stack
              operator_Stack.pop();
            }
            // Push the unary operator onto the stack
            operator_Stack.push(infix_Tokens[i]);  
          } else {
            // Check if the operator stack is not empty and the precedence of the current operator is less than or equal to the precedence of the operator on top of the stack
            if (!operator_Stack.empty() && precedence_Compare(oper, operator_Stack.top().get_Operator()) <= 0) {
              // Pop all operators with greater or equal precedence at the top of the stack
              //Pops the operation from the operator stack
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
    //While the operator stack is not empty
    while (!operator_Stack.empty()) {
      //Adds the operator at the top of the stack to the output vector
      output.push_back(operator_Stack.top());
      //Pops the operator from the stack
      operator_Stack.pop();
    }
    //Returns the output
    return output;
}


};
//End of the ifndef directive for INFIX_TO_POSTFIX_HPP
#endif
