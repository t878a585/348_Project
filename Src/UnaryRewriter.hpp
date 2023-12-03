#ifndef UNARYREWRITER_HPP
#define UNARYREWRITER_HPP

#include <string>
#include <vector>
#include <stack>
#include "./ErrorReporter.hpp"
#include "./Token.hpp"
#include <iostream>

class UnaryRewriter {

private:

std::vector<Token> ts;
ErrorReporter * error_Report;

template <typename T>
T top_And_Pop(std::stack<T> &s) {
	T val = s.top();
	s.pop();
	return val; 
}

template <typename T>
std::stack<T> create_Reverse_Stack (std::vector<T>& v) {
	std::stack<T> reverse_Stack;
	int v_Size = v.size();

	for (int i = v_Size - 1; i > -1; i--) reverse_Stack.push(v[i]);

	return reverse_Stack;
}


std::vector<Token> positive_Rewriter_For_Parentheses(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);

	Token t1 = top_And_Pop<Token>(r_Stack);
	Token t2 = top_And_Pop<Token>(r_Stack);
	Token t3('!');//This is not being used yet, this is dummy value
	
	if (t1.is_Operator_And_Is_Value('+') && t2.is_Operator_And_Is_Value('(')) {
		new_Tokens.push_back(t2);
	} else {
		r_Stack.push(t2);
		r_Stack.push(t1);
	}
	
	while (r_Stack.size() >= 3) {
		t1 = top_And_Pop<Token>(r_Stack);
		t2 = top_And_Pop<Token>(r_Stack);
		t3 = top_And_Pop<Token>(r_Stack);
		
		if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('+') && t3.is_Operator_And_Is_Value('(')) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(t3);
			continue;
		}

		new_Tokens.push_back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);
	}

	while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));

	return new_Tokens;
}

std::vector<Token> negative_Rewriter_For_Parentheses(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);
		
	Token t1 = top_And_Pop<Token>(r_Stack);
	Token t2 = top_And_Pop<Token>(r_Stack);
	Token t3('!');
	
	if (t1.is_Operator_And_Is_Value('-') && t2.is_Operator_And_Is_Value('(')) {
		new_Tokens.push_back(Token('('));
		new_Tokens.push_back(Token('-'));
		new_Tokens.push_back(Token(1.0l));
		new_Tokens.push_back(Token('*'));
		new_Tokens.push_back(Token('('));
		
		int open_Parentheses_Count = 1;
		std::vector<Token> backup;

		while (open_Parentheses_Count > 0) {
			Token t = top_And_Pop<Token>(r_Stack);
			backup.push_back(t);

			if (t.is_Operator_And_Is_Value(')')) open_Parentheses_Count--;
			if (t.is_Operator_And_Is_Value('(')) open_Parentheses_Count++;
		}

		r_Stack.push(Token(')'));
		int backup_Size = backup.size();

		for (int i = 0; i < backup_Size; i++) {r_Stack.push(backup.back()); backup.pop_back();}
	} else {
		r_Stack.push(t2);
		r_Stack.push(t1);
	}

	while (r_Stack.size() >= 3) {
		t1 = top_And_Pop<Token>(r_Stack);
		t2 = top_And_Pop<Token>(r_Stack);
		t3 = top_And_Pop<Token>(r_Stack);
		

		if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('-') && t3.is_Operator_And_Is_Value('(')) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(Token('('));
			new_Tokens.push_back(Token('-'));
			new_Tokens.push_back(Token(1.0l));
			new_Tokens.push_back(Token('*'));
			new_Tokens.push_back(Token('('));
			
			int open_Parentheses_Count = 1;
			std::vector<Token> backup;

			while (open_Parentheses_Count > 0) {
				Token t = top_And_Pop<Token>(r_Stack);
				backup.push_back(t);

				if (t.is_Operator_And_Is_Value(')')) open_Parentheses_Count--;
				if (t.is_Operator_And_Is_Value('(')) open_Parentheses_Count++;
			}

			r_Stack.push(Token(')'));
			int backup_Size = backup.size();

			for (int i = 0; i < backup_Size; i++) {r_Stack.push(backup.back()); backup.pop_back();}
			
			continue;
		}

		new_Tokens.push_back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);
	}

	while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));

	return new_Tokens;
}

std::vector<Token> negative_Rewriter_For_Operands(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);
	
	Token t1 = top_And_Pop<Token>(r_Stack);
	Token t2 = top_And_Pop<Token>(r_Stack);
	Token t3('!');//This is just a dummy value, until it is set to something else
	
	if (t1.is_Operator_And_Is_Value('-') && !t2.is_This_An_Operator()) {
		new_Tokens.push_back(Token(t2.get_Operand()*-1.0));
	} else {
		r_Stack.push(t2);
		r_Stack.push(t1);
	}

	while(r_Stack.size() >= 3) {
		Token t1 = top_And_Pop<Token>(r_Stack);
		Token t2 = top_And_Pop<Token>(r_Stack);
		Token t3 = top_And_Pop<Token>(r_Stack);

		if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('-') && !t3.is_This_An_Operator()) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(Token(t3.get_Operand()*-1.0));
			continue;
		}
		
		
		new_Tokens.push_back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);

	}

	while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));

	return new_Tokens;
}

std::vector<Token> positive_Rewriter_For_Operands(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);

	Token t1 = top_And_Pop<Token>(r_Stack);
	Token t2 = top_And_Pop<Token>(r_Stack);
	Token t3('!');//This is just a dummy value until it gets set to something else

	if (t1.is_Operator_And_Is_Value('+') && !t2.is_This_An_Operator()) {
		new_Tokens.push_back(t2);
	} else {
		r_Stack.push(t2);
		r_Stack.push(t1);
	}

	while (r_Stack.size() >= 3) {
		t1 = top_And_Pop<Token>(r_Stack);
		t2 = top_And_Pop<Token>(r_Stack);
		t3 = top_And_Pop<Token>(r_Stack);
		
		if (t1.is_Operator_And_Has_Intersection("+-/*%^(") && t2.is_Operator_And_Is_Value('+') && !t3.is_This_An_Operator()) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(t3);
			continue;
		}

		new_Tokens.push_back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);
	}

	while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));

	return new_Tokens;
}

public:


UnaryRewriter(std::vector<Token> _ts, ErrorReporter * _error_Report) {
	ts = _ts;
	error_Report = _error_Report;
}

std::vector<Token> get_Tokens() {
	return ts;
}


void fix() {
	ts = positive_Rewriter_For_Parentheses(ts);

	//This is a hack, it things should not be done this way
	int old_Size = ts.size();
	while (true) {
		ts = negative_Rewriter_For_Parentheses(ts);
		if (old_Size == ts.size()) break;
		old_Size = ts.size();
	}
	//This is the end of the hack

	//Do not put these before the parentheses rewriter.
	//The parentheses rewriter creates unary operators associated with operands.
	
	ts = positive_Rewriter_For_Operands(ts);
	
	ts = negative_Rewriter_For_Operands(ts);

}

};

#endif
