#ifndef TESTCASES_HPP
#define TESTCASES_HPP


#include <iomanip>  // Include for setw
#include <iostream>
#include <string>
#include <stack>
#include <cmath>

#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define RED_BACKGROUND "\033[41m"
#define GREEN_BACKGROUND "\033[42m"
#define RESET_COLOR "\033[0m"

#include "InfixToPostfix.hpp"
#include "PostfixEvaluator.hpp"
#include "IOHandler.hpp"

using namespace std;


bool testInfixToPostfixAndEvaluate(string infix, double expectedValue, double tolerance = .01) {
    InfixToPostfix infixToPostfixConverter;
    PostfixEvaluator postfixEvaluator;  // Create an instance of PostfixEvaluator class
    ErrorReporter errorReporter;  // Assuming you have an instance of ErrorReporter

    vector<Token> postfixTokens = infixToPostfixConverter.convert(infix.c_str(), &errorReporter);

    // Check if there were any errors during the conversion
    if (errorReporter.get_error_count() > 0) {
        cout << "Error during infix to postfix conversion." << endl;
        return false;
    }

    // Evaluate the postfix expression
    double actualValue = postfixEvaluator.evaluate(postfixTokens, &errorReporter);

    cout << setw(5) << left << "Infix: " << setw(15) << left << infix
         << setw(15) << left << "Expected Value: " << setw(10) << left << expectedValue
         << setw(15) << left << "Actual Value: " << setw(10) << left << actualValue;

    if (fabs(actualValue - expectedValue) < tolerance) {
        cout << setw(20) << left << GREEN_BACKGROUND << GREEN_TEXT << "Pass" << RESET_COLOR << endl;
        return true;
    } if (errorReporter.get_error_count() > 0) {
        cout << setw(20) << left << RED_BACKGROUND << RED_TEXT << "1) Fail" << RESET_COLOR << endl;
        //errorReporter.print_And_Clear_Errors(); Function moved to IOHanlder 
        return false;
    }else {
        cout << setw(20) << left << RED_BACKGROUND << RED_TEXT << "2) Fail" << RESET_COLOR << endl;
        return false;
    }
}

void runTests() {
  testInfixToPostfixAndEvaluate("(2+(-3))" , -1); //Add-101
  testInfixToPostfixAndEvaluate("-(2+(3))", -5); //Add-102
  testInfixToPostfixAndEvaluate("-(2+(-3))", 1); //Add-103
  testInfixToPostfixAndEvaluate("6+7", 13); //Add-104
  testInfixToPostfixAndEvaluate("5+0", 5); //Add-105
  testInfixToPostfixAndEvaluate("2.5+2.5", 5); //Add-106
  
  testInfixToPostfixAndEvaluate("(2-(-3))", 5); //Sub-101
  testInfixToPostfixAndEvaluate("-(2-(3))", -1);//Sub-102
  testInfixToPostfixAndEvaluate("-(2-(-3))", -5); //Sub-103
  testInfixToPostfixAndEvaluate("3-2", 1); //Sub-104
  testInfixToPostfixAndEvaluate("2-0", 2); //Sub-105
  testInfixToPostfixAndEvaluate("(-2)-(-3)", 6); //sub-106
  testInfixToPostfixAndEvaluate("5-2.5", 2.5);//Sub-107
  
  testInfixToPostfixAndEvaluate("(2*(-3))",-6); //Mult-101
  testInfixToPostfixAndEvaluate("-(2*(3))", -6);                  // Mult-102
  testInfixToPostfixAndEvaluate("-(2*(-3))", 6);                  // Mult-103
  testInfixToPostfixAndEvaluate("2*3", 6);                       // Mult-104
  testInfixToPostfixAndEvaluate("2*0", 0);                       // Mult-105
  testInfixToPostfixAndEvaluate("2*1", 2);                       // Mult-106
  testInfixToPostfixAndEvaluate("2*(-3)", -6);                   // Mult-107
  testInfixToPostfixAndEvaluate("2*2.5", 5);                     // Mult-108
  testInfixToPostfixAndEvaluate("2*-3", -6);                     // Mult-109
  
  testInfixToPostfixAndEvaluate("(9/(-3))", -3);//Div-101
  testInfixToPostfixAndEvaluate("-(9/(3))",-3); //Div-102
  testInfixToPostfixAndEvaluate("-(9/(-3))",3); //Div-103
  testInfixToPostfixAndEvaluate("5/0",0); //Div-104
  testInfixToPostfixAndEvaluate("1/3",.33); //Div-105
  testInfixToPostfixAndEvaluate("5/2.5",2);//Div-106
  testInfixToPostfixAndEvaluate("6*3/2", 9);                     // Div-107
  testInfixToPostfixAndEvaluate("9/3", 3);                       // Div-108
  
  testInfixToPostfixAndEvaluate("5%0", 0);                      // Mod-101
  testInfixToPostfixAndEvaluate("5%-2", -1);                      // Mod-102
  testInfixToPostfixAndEvaluate("-5%2", 1);                     // Mod-103
  testInfixToPostfixAndEvaluate("-5%-2", -1);
  testInfixToPostfixAndEvaluate("5%2.3", 0.4);                   // Mod-104
  
  testInfixToPostfixAndEvaluate("2^-2", 0.25);                   // Exp-101
  testInfixToPostfixAndEvaluate("2^2", 4);                       // Exp-102
  testInfixToPostfixAndEvaluate("-2^2", 4);                      // Exp-103
  testInfixToPostfixAndEvaluate("-2^-2", 0.25);                  // Exp-104
  testInfixToPostfixAndEvaluate("2^(4+3*1)", 128);               // Exp-105
  testInfixToPostfixAndEvaluate(".5^2", 0.25);                   // Exp-106
  testInfixToPostfixAndEvaluate("2^.5", 1.41);                   // Exp-107
  testInfixToPostfixAndEvaluate("2^2^3", 512);                   // Exp-108


  testInfixToPostfixAndEvaluate("qqq", 1000);   //function requires doubles so this is a placeholder
  testInfixToPostfixAndEvaluate("2@2", 1000);   //function requires doubles so this is a placeholder
    //testInfixToPostfixAndEvaluate("(2))", 2); 
  testInfixToPostfixAndEvaluate("3+4",7);
  testInfixToPostfixAndEvaluate("8-(5-2)", 5);
  testInfixToPostfixAndEvaluate("10*2/5",4);
  testInfixToPostfixAndEvaluate("2^3",8);
  testInfixToPostfixAndEvaluate("4*(3+2)%7-1",5);
  testInfixToPostfixAndEvaluate("(((2+3)))+(((1+2)))",8);
  testInfixToPostfixAndEvaluate("((5*2)-((3/1)+((4%3))))",6);
  testInfixToPostfixAndEvaluate("(((2^(1+1))+((3-1)^2))/((4/2)%3))",4);
  testInfixToPostfixAndEvaluate("(((((5-3)))*(((2+1)))+((2*3))))",12);
  testInfixToPostfixAndEvaluate("((9+6))/((3*1)/(((2+2)))-1)",-60);
  testInfixToPostfixAndEvaluate("+(-2)*(-3)-((-4)/(+5))", 6.8);
  testInfixToPostfixAndEvaluate("-(+1)+(+2)", 1);
  testInfixToPostfixAndEvaluate("-(-(-3))+(-4)+(+5)",-2);
  testInfixToPostfixAndEvaluate("+2^(-3)",.125);
  testInfixToPostfixAndEvaluate("-(+2)*(+3)-(-4)/(-5)",-6.8);

  testInfixToPostfixAndEvaluate("2*(4+3-1" , 0);
  testInfixToPostfixAndEvaluate("*5+2",0);
  testInfixToPostfixAndEvaluate("4/0",0);
  testInfixToPostfixAndEvaluate("5(2+3)",0);
  testInfixToPostfixAndEvaluate("7&3",0);
  testInfixToPostfixAndEvaluate("(((3 + 4) - 2) + (1)" ,0);
  testInfixToPostfixAndEvaluate("((5 + 2) / (3 * 0))",0);
  testInfixToPostfixAndEvaluate("((2 -) 1 + 3)",0);
  testInfixToPostfixAndEvaluate("((4 * 2) + ( - ))",0);
  testInfixToPostfixAndEvaluate("((7 * 3) @ 2)",0);
  
  
  

}

#endif