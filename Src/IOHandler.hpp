/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */


//Include guard to prevent multiple inclusion of the IOHANDLER_HPP header file
#ifndef IOHANDLER_HPP
//If IOHANDLER_HPP is not defined, define it to avoid multiple inclusion of the header file
#define IOHANDLER_HPP

//Includes the ErrorReporter header file, which will allow the use of declarations and defintions from that file 
#include "./ErrorReporter.hpp"
//Include the Token header file, which will allow the use declarations and defintions from that file 
#include "./Token.hpp"
//Include InfixToPostfix header file, which will allow the use of declarations and definitions from that file
#include "./InfixToPostfix.hpp"
//Include the PostfixEvaluator header file, which will allow the use of declarations and definition from that file
#include "./PostfixEvaluator.hpp"

#include "./testCases.hpp"
//Include the iostream header file, providing functionalities for input and output using streams
#include <iostream>
//Include the string header file, providing functionalities for working with strings
#include <string>
//Include the vector header file, providing functionalities for working with vectors
#include <vector>

//Definition of the IOHandler class
class IOHandler {
  private:
  //Instantiate an InfixToPostfix object
  InfixToPostfix infixToPostfix;
  //Instantiate a PostfixEvaluator object
  PostfixEvaluator postfixEvaluator;
  //Instantiate an ErrorReporter object
  ErrorReporter errorReporter;

  //This function displays a welcome message and instructions for the user 
  void start_Message() {
    //Provides a welcome message
    std::cout << "Welcome to the Arithmetic Expression Evaluator" << std::endl;
    //Provides a message on how to exit the program
    std::cout << "To exit, type q or Q at any time and hit enter" << std::endl;
    //Additional instruction for exiting the program
    std::cout << "Alternatively, press control-c" << std::endl;
    //Inform the user about the prompt for entering equations
    std::cout << "Whenever prompted with \"Input your equations:\"" << std::endl;
    //Provide guidance on entering equations and evaluating them
    std::cout << "you may enter in your equation and hit enter to evaluate it." << std::endl;
  }

  //Evaluates whether user is trying to quit the program with input of "q" or "Q"
  bool has_Q(std::string s) {
    //Get the length of the input string
    int length = s.length();
    //Using a for loop it'll Iterate through each character in the string
    for (int i = 0; i < length; i++) {
      //Checks to see if the current character is 'q' or 'Q'
      if (s[i] == 'q' || s[i] == 'Q') {
        //Return true if 'q' or 'Q' is found in the string
        return true;
      }
    }
    //Return false if 'q' or 'Q' is not found in the string
    return false;
  }
  //Cleans up user input so it can be handed to InfixtoPostfix
  std::string remove_Newlines(std::string s) {
    //Get the length of the input string
    int length = s.length();
    //Declare a new string to store characters without newline characters
    std::string new_String;
    //Using a for loop it'll iterate through each character in the input string
    for (int i = 0; i < length; i++) {
      //Checks if the current character is not a newline character and appends the non-newline character to the new string
      if (s[i] != '\n') new_String += s[i];
    }
    //Returns the new string without newline characters
    return new_String;
  }
  //This function prints error message stored in the ErrorReporter and then clears the errors
  void print_And_Clear_Errors() {
    //Gets the current count of errors from the ErrorReporter
    int error_Count = errorReporter.get_error_count();
    //Using a for loop it'll iterate through each error
    for (int i = 0; i < error_Count; i++) {
      //Gets the error string for the current error
      char * error_String = errorReporter.get_error_string(i);
      //Prints the error string
      std::cout << error_String << std::endl;

      //Free the memory allocated for the error string
      delete error_String;
    }
    //Clears the errors from the ErrorReporter
    errorReporter.remove_errors();

  }
  

  public:
  //This function is to execute the calculator, and start taking user input
  void execute() {
    runTests();
    //Calls the start_message() function to display a welcome message and instructions for the user
    start_Message();
    //Declare a string variable to store user input
    std::string input;
    //Start an infinite loop for continuous user interaction
    while (1) {
      //Prompts the user to input an eqaution
      std::cout << "Input your equation:";
      //Read the line of input from the user
      std::getline(std::cin, input);
      //Checks if the user input contains 'q' or 'Q'; if yes, it'll break out of the loop
      if (has_Q(input)) break;
      //Removes the newline characters from the user input
      std::string stripped_Input = remove_Newlines(input);
      //Convert the infix expression to postfix and get the result in a vector of Tokens
      std::vector<Token> postfix_Tokens = infixToPostfix.convert(stripped_Input.c_str(), &errorReporter);
      //Check for errors during the conversion process
      if (errorReporter.get_error_count() > 0) {
        //Print and clear errors, then continue to the next iteration of the loop
        print_And_Clear_Errors();
        continue;
      }
      //Evaluate the postfix expression and get the result
      long double result = postfixEvaluator.evaluate(postfix_Tokens, &errorReporter);

      //Check for errors during the evaluation process
      if (errorReporter.get_error_count() > 0) {
        //Prints and clear errors, then continue to the next iteration of the loop
        print_And_Clear_Errors();
        continue;
      }
      //Print the result of the evaluation
      std::cout << std::fixed << result << std::endl;
    }
    //Displays a messasge telling the using that the program is exiting
    std::cout << "Exiting Calculator..." << std::endl;
  }
};

//End of the ifndef directive for IOHANDLER_HPP
#endif
