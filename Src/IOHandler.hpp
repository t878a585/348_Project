/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */


#ifndef IOHANDLER_HPP
#define IOHANDLER_HPP

#include "./ErrorReporter.hpp"
#include "./Token.hpp"
#include "./InfixToPostfix.hpp"
#include "./PostfixEvaluator.hpp"
#include "./testcases.hpp"
#include <iostream>
#include <string>
#include <vector>

class IOHandler {
	private:
	
	InfixToPostfix infixToPostfix;
	PostfixEvaluator postfixEvaluator;
	ErrorReporter errorReporter;

	
	void start_Message() {
		std::cout << "Welcome to the Arithmetic Expression Evaluator" << std::endl;
		std::cout << "To exit, type q or Q at any time and hit enter" << std::endl;
		std::cout << "Alternatively, press control-c" << std::endl;
		std::cout << "Whenever prompted with \"Input your equations:\"" << std::endl;
		std::cout << "you may enter in your equation and hit enter to evaluate it." << std::endl;
	}

	bool has_Q(std::string s) {
		int length = s.length();
		
		for (int i = 0; i < length; i++) {
			if (s[i] == 'q' || s[i] == 'Q') {
				return true;
			}
		}

		return false;
	}
	
	std::string remove_Newlines(std::string s) {
		int length = s.length();
		std::string new_String;
		
		for (int i = 0; i < length; i++) {
			if (s[i] != '\n') new_String += s[i];
		}

		return new_String;
	}

	
	
	public:
	
	void execute() {
		runTests(); //RUNS TEST CASES. COMMENT OUT BEFORE PROD
		start_Message();
		
		std::string input;
		
		while (1) {
			std::cout << "Input your equation:";
			std::getline(std::cin, input);
			
			if (has_Q(input)) break;

			std::string stripped_Input = remove_Newlines(input);
			std::vector<Token> postfix_Tokens = infixToPostfix.convert(stripped_Input.c_str(), &errorReporter);
			
			if (errorReporter.get_error_count() > 0) {
				errorReporter.print_And_Clear_Errors();
				continue;
			}

			long double result = postfixEvaluator.evaluate(postfix_Tokens, &errorReporter);

			
			if (errorReporter.get_error_count() > 0) {
				errorReporter.print_And_Clear_Errors();
				continue;
			}

			std::cout << std::fixed << result << std::endl;
		}

		std::cout << "Exiting Calculator..." << std::endl;
	}
};

#endif
