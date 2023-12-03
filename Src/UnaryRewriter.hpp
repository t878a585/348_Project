#include <string>
#include <vector>
#include <stack>
#include "./ErrorReporter.hpp"
#include "./Token.hpp"

class UnaryRewriter {

private:

std::vector<Token> ts;
ErrorReport * error_Report;

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
}


std::vector<Token> positive_Rewriter_For_Parentheses(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);

	Token t1 = pop_And_Top<Token>(r_Stack);
	Token t2 = pop_And_Top<Token>(r_Stack);
	Token t3;
	
	if (t1.is_Operator_And_Is_Value('+')) && t2.is_Operator_And_Is_Value('(')) {
		new_Tokens.push_back(t2);
	} else {
		new_Tokens.push_back(t1);
		r_Stack.push(t2);
	}
	
	while (r_Stack.size() >= 3) {
		t1 = pop_And_Top<Token>(r_Stack);
		t2 = pop_And_Top<Token>(r_Stack);
		t3 = pop_And_Top<Token>(r_Stack);
		
		if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('+') && t3.is_Operator_And_Is_Value('(')) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(t3);
			continue;
		}

		new_Tokens.push_back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);
	}

	while (!r_Stack.empty()) new_Tokens.push_back(pop_And_Top<Token>(r_Stack));

	return new_Tokens;
}

std::vector<Token> negative_Rewriter_For_Parentheses(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);

	while (r_Stack.size() >= 3) {
		Token t1 = pop_And_Top<Token>(r_Stack);
		Token t2 = pop_And_Top<Token>(r_Stack);
		Token t3 = pop_And_Top<Token>(r_Stack);

		if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('-') && t3.is_Operator_And_Is_Value('(')) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(t3);
			new_Tokens.push_back(Token('-'));
			new_Tokens.push_back(Token(1.0));
			new_Tokens.push_back(Token('*'));
			new_Tokens.push_back(Token('('));
			
			int open_Parentheses_Count = 1;
			std::vector<Token> backup;

			while (open_Parentheses_Count > 0) {
				Token t = pop_And_Top<Token>(old_Tokens);
				backup.push_back(t);

				if (t.is_Operator_And_Is_Value(')')) open_Parentheses_Count--;
				if (t.is_Operator_And_Is_Value('(')) open_Parentheses_Count--;
			}

			r_Stack.push(Token(')'));
			r_Backup = create_Reverse_Stack<Token>(backup);
			int r_Backup_Size = r_Backup.size();

			for (int i = 0; i < r_Backup_Size; i++) r_Stack.push(pop_And_Top<Token>(r_Backup));
			
			continue;
		}

		new_Tokens.push_Back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);
	}	

	return new_Tokens;
}

std::vector<Token> negative_Rewriter_For_Operands(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);
	
	Token t1 = pop_And_Top<Token>(r_Stack);
	Token t2 = pop_And_Top<Token>(r_Stack);
	Token t3;
	
	if (t1.is_Operator_And_Is_Value('-') && t2.is_This_An_Operand()) {
		new_Tokens.push_back(t1);
		new_Tokens.push_back(Token(t2.get_Operand()*-1.0));
	} else {
		new_Tokens.push_back(t1);
		r_Stack.push(t2);
	}

	while(r_Stack.size() >= 3) {
		Token t1 = pop_And_Top<Token>(r_Stack);
		Token t2 = pop_And_Top<Token>(r_Stack);
		Token t3 = pop_And_Top<Token>(r_Stack);

		if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('-') && t3.is_This_An_Operand()) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(Token(t3.get_Operand*-1.0));
			continue;
		}
		
		
		new_Tokens.push_back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);

	}

	while (!r_Stack.empty()) new_Tokens.push_back(pop_And_Top<Token>(r_Stack));

	return new_Tokens;
}

std::vector<Token> positive_Rewriter_For_Operands(std::vector<Token> old_Tokens) {
	std::vector<Token> new_Tokens;
	std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);

	Token t1 = pop_And_Top<Token>(r_Stack);
	Token t2 = pop_And_Top<Token>(r_Stack);
	Token t3;

	if (t1.is_Operator_And_Is_Value('+') && t2.is_Operand()) {
		new_Tokens.push_back(t2);
	} else {
		new_Tokens.push_back(t1);
		r_Stack.push(t2);
	}

	while (r_Stack.size() >= 3) {
		t1 = pop_And_Top<Token>(r_Stack);
		t2 = pop_And_Top<Token>(r_Stack);
		t3 = pop_And_Top<Token>(r_Stack);
		
		if (t1.is_Operator_And_Has_Intersection("+-/*%^(") && t2.is_Operator_And_Is_Value('+') && t3.is_Operator()) {
			new_Tokens.push_back(t1);
			new_Tokens.push_back(t3);
			continue;
		}

		new_Tokens.push_back(t1);
		r_Stack.push(t3);
		r_Stack.push(t2);
	}

	while (!r_Stack.empty()) new_Tokens.push_back(pop_And_Top<Token>(r_Stack));

	return new_Tokens;
}

public:

UnaryFixer(std::vector<Token> _ts, ErrorReporter * _error_Report) {
	ts = _ts;
	error_Report = _error_Report;
}

std::vector<Token> get_Tokens() {
	return ts;
}

void fix() {
	ts = positive_Rewriter_For_Parentheses(ts);
	ts = negative_Rewriter_For_Parentheses(ts);
	//Do not put these before the parentheses rewriter.
	//The parentheses rewriter creates unary operators associated with operands.
	ts = positive_Rewriter_For_Operands(ts);
	ts = negative_Rewriter_For_Operands(ts);
}

};
