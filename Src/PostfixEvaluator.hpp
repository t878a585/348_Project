//Include guard to prevent multiple inclusion of the POSTFIXEVALUATOR_HPP header file
#ifndef POSTFIXEVALUATOR_HPP
//If POSTFIXEVALUATOR_HPP is not defined, define it to avoid multiple inclusion of the header file
#define POSTFIXEVALUATOR_HPP
//Include Token header file, which will allow the use of declarations and definitions from that file
#include "./Token.hpp"
//Includes the ErrorReporter header file, which will allow the use of declarations and defintions from that file
#include "./ErrorReporter.hpp"
//Include the vector header file, providing functionalities for working with vectors
#include <vector>
//Include this header for the C++ stack
#include <stack>
//Include cmath header file, to provide user math functions
#include <cmath>
//Include the iostream header file, providing functionalities for input and output using streams
#include <iostream>

//Class for taking postfix output from InfixToPostfix class and evaluating it using a stack
class PostfixEvaluator {
  private:
  //This will hold the stack of numerical operands
  std::stack<long double> number_Stack;
  //This function will return a boolean value depending on if there is unmatched parentheses
  bool check_Unmatched_Parentheses(const std::vector<Token> &postfix_Expression, ErrorReporter *error_reporter) {
    //Initializes open_Count to zero which will count the number of opening parentheses
    int open_Count = 0;
    //Initializes close_Count to zero which will count the number of closing parentheses
    int close_Count = 0;
    //Uses a for loop to iterate through the expression
    for (const Token &token : postfix_Expression) {
      //Checks to see if the token is an operator
      if (token.is_This_An_Operator()) {
        //Checks to see if the Token is an open parenthesis
        if (token.get_Operator() == '(') {
          //If true, it'll increment the open_Count by 1
          open_Count++;
        //Checks to see if the Token is a closed parenthesis
        } else if (token.get_Operator() == ')') {
          //If true, it'll increment the close_Count by 1
          close_Count++;
        }
      }
    }
    //Checks to see if the number of opening parentheses is not equal to the number of closing parentheses
    if (open_Count != close_Count) {
      //If true, then it'll add an error to error_reporter telling the user there are unmatched parentheses
      error_reporter->add_error("PostfixEvaluator", "Unmatched parentheses.");
      //Returns false
      return false;
    }
    //Returns true
    return true;
  }

  //This function will return a boolean value and perform the operation
  bool perform_Operation(char operation, ErrorReporter * error_reporter) {
    //Checks to see if the size of the number stack is less than 2
    if (number_Stack.size() < 2) {
      //The error is added to error_reporter that'll tell the user that there is Not enough operands
      error_reporter->add_error("PostfixEvaluator", "Not enough operands.");
      //It'll return false
      return false;
    }
    //Sets operand two to the top of the number stack
    long double operand_Two = number_Stack.top();
    //Pops the top of the number stack
    number_Stack.pop();
    //Sets operand one to the top of the number stack
    long double operand_One = number_Stack.top();
    //Pops the top of the number stack
    number_Stack.pop();
    //Creates a variable called result without initializing it
    long double result; 
    //Uses a switch statement to figure out which operation it is
    switch (operation) {
      //Checks if the operation is addition
      case '+': 
        //If true, it'll set the result to operand 1 + operand 2
        result = operand_One + operand_Two;
      //Breaks out of the switch
      break;
      //Checks if the operation is subtraction
      case '-': 
        //If true, it'll set the result to operand 1 - operand 2
        result = operand_One - operand_Two;
        //Breaks out of the switch
      break;
      //Checks if the operation is division
      case '/':
        //Checks to see if operand two is 0
        if (operand_Two == 0.0) {
          //If true, it'll add the error to error_reporter that'll tell the user that Division by zero is invalid
          error_reporter->add_error("PostfixEvaluator", "Division by zero is invalid.");
          //Returns false
          return false;
        }
        //If true, it'll set result to operand 1 / operand 2
        result = operand_One / operand_Two;
        //Breaks out of the switch
      break;
      //Checks if the operation is mulitiplication
      case '*': 
        //If true, it'll set result to operand 1 * operand 2
        result = operand_One * operand_Two;
        //Breaks out of the switch
      break;
      //Checks if the operation is '^'
      case '^': 
        //If true, it'll set result to operand 1 to the power of operand 2
        result = pow(operand_One, operand_Two);
        //Breaks out of the switch
      break;
      //Checks if the operation is modulo
      case '%': 
        //Checks if operand 2 is equal to zero
        if (operand_Two == 0.0) {
          //If true, it'll add the error to the error_reporter telling the user that modulus by zero is invalid
          error_reporter->add_error("PostfixEvaluator", "Modulus by zero is invalid.");
          //Returns false
          return false;
        }else{
          //If true, it'll set the result to the modulo of operand 1 by operand 2
          result = fmodf(operand_One, operand_Two);
          //Checks to see if operand 1 is less than 0 AND operand 2 is less than 0
          if(operand_One < 0 && operand_Two < 0) {
            //If true, it'll times the result by 1
            result *= 1;
          //Checks to see if operand 1 is less than 0 AND operand 2 is greater than 0
          }else if (operand_One < 0 && operand_Two > 0){
            //If true, it'll times the result by -1
            result *= -1;
          //Checks to see if operand 1 is greater than 0 AND operand 2 less than 0
          }else if (operand_One > 0 && operand_Two < 0){
            //If true, it'll times the result by -1
            result *= -1;
          }
        }
        //Breaks out of the switch
      break;
    }

    //This pushes the result to the number stack to the top
    number_Stack.push(result);
    //Returns true
    return true;
  }

  public:
  //This function does the evaluation of the postfix 
  long double evaluate(std::vector<Token> postfix_Expression, ErrorReporter * error_reporter) {
    //Checks to see for unmatched parentheses
    if (!check_Unmatched_Parentheses(postfix_Expression, error_reporter)) {
      //If there are unmatched parentheses it'll return 0.0
      return 0.0; 
    }
    //Gets the size of the postfix_Expression
    int token_Count = postfix_Expression.size();
    //Uses a for loop to iterate through each token in the postfix expression
    for (int i = 0; i < token_Count; i++) {
      //Get the front token from the postfix expression 
      Token token = postfix_Expression.front();
      //It'll remove the token
      postfix_Expression.erase(postfix_Expression.begin());
      //Checks to see if the token is an operator
      if (token.is_This_An_Operator()) {
        //If true, it'll perform the opeation on that operator
        perform_Operation(token.get_Operator(), error_reporter);
      //Otherwise the token isn't an operator 
      } else {
        //If it's operand it'll push the operand to the top to the number stack
        number_Stack.push(token.get_Operand());
      }
    }

    //Checks to see if the number stack is NOT empty
    if (!number_Stack.empty()) {  
      //Sets the result to the top of the number stack
      long double result = number_Stack.top();
      //Pops the number stack
      number_Stack.pop();
      //Returns the result
      return result;
    } else {
        // Handle the case where the stack is empty, report an error or return a default value.

        return 0.0; // or any appropriate default value
    }
  }
};
//End of the ifndef directive for POSTFIXEVALUATOR_HPP
#endif
