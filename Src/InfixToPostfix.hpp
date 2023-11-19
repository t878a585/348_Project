/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP

#include "../Token.hpp"
#include <vector> 
#include <cstring>
#include <string>
#include <stack>

class Tokenizer {
	private:

	std::vector<Token> tokens;

	bool is_Operator(char character) {
		if (character == '+' || character == '-' || character == '/' || character == '*' || character == '(' || character == ')' || character == '^' || character == '%') {
			return true;
		}

		return false;
	}

	bool is_Decimal(char character) {
		if (character >= 48 && character <= 57) return true;

		if (character == '.') return true;

		return false;
	}

	void fix_False_Negative_Operators() {

	}
	
	void tokenize(char * input) {
		int length = strlen(input);

		for (int i = 0; i < length;) {
			if (!is_Decimal(input[i]) && !is_Operator(input[i])) {i++; continue;}

			if (is_Operator(input[i])) {
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
		}
		
		fix_False_Negative_Operators();
	}

	public:

	Tokenizer(char * input) {	
		tokenize(input);
	}

	std::list<vector> get_Tokens() {return tokens;}


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
				return 5
			break;
		}
	}

	//return -1 (op1 < op2)
	//return 0 (op1 == op2)
	//return 1 (op1 > op2)
	int precedence_Compare(char op1, char op2) {
		return ((get_Precedence(op1) > get_Precedence(op2)) - (get_Precedence(op1) < get_Precedence(op2)));
	}
    
  public:
    std::list<Token> convert(char * infix_expression, ErrorReporter * error_reporter){
	Tokenizer tokenizer(infix_Expression);
	std::stack<Token> operator_Stack;
	std::vector<Token> output;
	std::vector<Token> infix_Tokens = tokenizer.get_Tokens();
	
	int infix_Token_Count = infix_Tokens.size();

	for (int i = 0; i < infix_Token_Count; i++) {
		if (!( infix_Tokens[i].is_This_An_Operator() )) {
			output.push_back(infix_Tokens[i]);
		} else {
			char oper = infix_Tokens[i].get_Operator;
			
			if (oper == '(') {
				operator_Stack.push_back(infix_Tokens[i]);
			} else if (oper == ')') {
				while (operator_Stack.top().get_Operator() != '(') {
					output.push_back(operator_Stack.pop());
				}

				operator_Stack.pop();
			} else {
				
			}

		}
	}

	return output;
    }
};
#endif
