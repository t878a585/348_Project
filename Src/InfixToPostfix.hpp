/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP

#include "./Token.hpp"
#include <vector> 
#include <cstring>
#include <string>
#include <stack>

class Tokenizer {
	private:

	std::vector<Token> tokens;

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

	void fix_False_Negative_Operators() {
		std::vector<Token> new_Tokens;
		std::stack<Token> holding_Stack;
		
		//Push tokens on in reverse order so that they are popped in order
		for (int i = tokens.size() - 1; i >= 0 ; i--) holding_Stack.push(tokens[i]);
		
		while (!holding_Stack.empty() && holding_Stack.size() >= 3) {
			Token t1 = holding_Stack.top();
			holding_Stack.pop();
			
			Token t2 = holding_Stack.top();
			holding_Stack.pop();

			Token t3 = holding_Stack.top();
			holding_Stack.pop();
			
			// Check for the following string of tokens <any_operator> <negative_operator> <operand>
			// If it matches this format, output the following tokens <any_operator> -<operand>
			if (t1.is_This_An_Operator() && t2.is_This_An_Operator() && t2.get_Operator() == '-' && !t3.is_This_An_Operator()) {
				new_Tokens.push_back(t1);
				//Minus token is absorbed through negation of the operand
				new_Tokens.push_back(Token(t3.get_Operand() * -1.0));

			} else {
				//If tokens don't match pattern, output the top token to the output
				//Put the remaining tokens back on the stack in the old order
				new_Tokens.push_back(t1);
				holding_Stack.push(t3);
				holding_Stack.push(t2);
			}
		}
		
		// There will be potentially two remaining tokens that need to be processed. Pop these directly
		// to the output. These can't be matched by our replacement pattern because there aren't at
		// least three tokens.
		while (!holding_Stack.empty()) {new_Tokens.push_back(holding_Stack.top()); holding_Stack.pop();}

		// Replace the old tokens with our new processed tokens
		tokens = new_Tokens;
	}
	
	void tokenize(const char * input) {
		int length = strlen(input);
		
		tokens.push_back(Token('('));

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

		tokens.push_back(Token(')'));
		
		fix_False_Negative_Operators();
	}

	public:

	Tokenizer(const char * input) {	
		tokenize(input);
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
    
  public:
    std::vector<Token> convert(const char * infix_expression, ErrorReporter * error_reporter){
	Tokenizer tokenizer(infix_expression);
	std::stack<Token> operator_Stack;
	std::vector<Token> output;
	std::vector<Token> infix_Tokens = tokenizer.get_Tokens();
	
	int infix_Token_Count = infix_Tokens.size();

	for (int i = 0; i < infix_Token_Count; i++) {
		if (!( infix_Tokens[i].is_This_An_Operator() )) {
			output.push_back(infix_Tokens[i]);
		} else {
			char oper = infix_Tokens[i].get_Operator();
			
			if (oper == '(') {
				operator_Stack.push(infix_Tokens[i]);

			} else if (oper == ')') {
				while (operator_Stack.top().get_Operator() != '(') {
					output.push_back(operator_Stack.top());
					operator_Stack.pop();
				}

				operator_Stack.pop();
			} else {
				// Check if the operator stack is not empty and the precedence of the current operator is less than or equal to the precedence of the operator on top of the stack
				if (!operator_Stack.empty() && precedence_Compare(oper, operator_Stack.top().get_Operator()) <= 0) {
					// Pop all operators with greater or equal precedence at the top of
					// the stack
					while (!operator_Stack.empty() && precedence_Compare(oper, operator_Stack.top().get_Operator()) <= 0) {
						output.push_back(operator_Stack.top());
						operator_Stack.pop();
					}
					
					//Push the new operator to the operator stack
					operator_Stack.push(infix_Tokens[i]);
				} else {
					
					//If the operator stack is empty or there isn't anything with greater
					// or equal precedence at the top of the stack, push the current token 
					// onto the stack.
					operator_Stack.push(infix_Tokens[i]);
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
