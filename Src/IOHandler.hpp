#ifndef IOHANDLER_HPP
#define IOHANDLER_HPP

#include "./ErrorReporter.hpp"
#include "./Token.hpp"
#include "./InfixToPostfix.hpp"
#include "./PostfixEvaluator.hpp"
#include <iostream>
#include <string>
#include <list>

class IOHandler {
	private:
	
	InfixToPostfix infixToPostfix;
	PostfixEvaluator postfixEvaluator;
	ErrorReporter errorReporter;

	
	void start_Message() {
		std::cout << "Welcome to the Arithmetic Expression Evaluator" << std::endl;
		std::cout << "To exit, type q or Q at any time and hit enter" << std::endl;
		std::cout << "Alternatively, press control-c" << std::endl;
		std::cout << "Whenever prompted with \"Input your equations:,\"" << std::endl;
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
		//Someone define this
	}

	bool print_And_Clear_Errors() {
		int error_Count = errorReporter.get_error_count();

		for (int i = 0; i < error_Count; i++) {
			char * error_String = errorReporter.get_error_string(i);
			
			std::cout << error_String << std::endl;

			delete error_String;
		}

		errorReporter.remove_errors();
	}
	
	public:
	
	void execute() {
		start_Message();
		
		std::string input;
		
		while (1) {
			std::cout << "Input your equation:";
			std::getline(cin, input);
			
			if (has_Q(input)) break;

			std::string stripped_Input = remove_Newlines(input);
			std::list<Token> postfix_Tokens = infixToPostfix.convert(stripped_Input.c_str(), &error_reporter);
			
			if (errorReporter.get_error_count() > 0) {
				print_And_Clear_Errors();
				continue;
			}

			long double result = postfixEvaluator.evaluate(postfix_Tokens, &error_reporter);

			
			if (errorReporter.get_error_count() > 0) {
				print_And_Clear_Errors();
				continue;
			}

			std::cout << result << std::endl;
		}

		std::cout << "Exiting Calculator..." << std::endl;
	}
}

#endif
