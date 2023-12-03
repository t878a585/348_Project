//Include guard to prevent multiple inclusion of the UNARYREWRITER_HPP header file
#ifndef UNARYREWRITER_HPP
//If UNARYREWRITER_HPP is not defined, define it to avoid multiple inclusion of the header file
#define UNARYREWRITER_HPP
//Include the string header file, providing functionalities for working with strings
#include <string>
//Include the vector header file, providing functionalities for working with vectors
#include <vector>
//Include this header for the C++ stack
#include <stack>
//Includes the ErrorReporter header file, which will allow the use of declarations and defintions from that file 
#include "./ErrorReporter.hpp"
//Include Token header file, which will allow the use of declarations and definitions from that file
#include "./Token.hpp"
//Include the iostream header file, providing functionalities for input and output using streams
#include <iostream>

//This is the UnaryRewriter class
class UnaryRewriter {

private:
//Declares a vector named 'ts' that stores the objects of the Token class
std::vector<Token> ts;
//Declares a pointer to an ErrorReporter object named 'error_Report'
ErrorReporter * error_Report;

//Template function that returns the top element of stack and pops it
template <typename T>
T top_And_Pop(std::stack<T> &s) {
  //Gets the top element of the stack
  T val = s.top();
  //Removes the top element of the stack
  s.pop();
  //Returns the top element of the stack
  return val; 
}

//Template function that reverses the order of a stack taking in a vector as a parameter
template <typename T>
std::stack<T> create_Reverse_Stack (std::vector<T>& v) {
  //Creates an empty stack that'll hold the reversed stack
  std::stack<T> reverse_Stack;
  //Gets the size of the input vector
  int v_Size = v.size();
  //Uses a for in loop to iterate through the elements in the vector in reverse order
  //Then pushes each element onto the stack in reverse order
  for (int i = v_Size - 1; i > -1; i--) reverse_Stack.push(v[i]);
  //Returns the reversed stack
  return reverse_Stack;
}

//This function will handle + unary operators with parentheses
std::vector<Token> positive_Rewriter_For_Parentheses(std::vector<Token> old_Tokens) {
  //This vector stores the new tokens
  std::vector<Token> new_Tokens;
  //This creates a reversed stack from the old_Tokens given in the parameters
  std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);

  //Stores the first element in the reversed stack
  Token t1 = top_And_Pop<Token>(r_Stack);
  //Stores the second element in the reversed stack
  Token t2 = top_And_Pop<Token>(r_Stack);
  Token t3('!');//This is not being used yet, this is dummy value
  //Checks to see if the first two tokens are '+('
  if (t1.is_Operator_And_Is_Value('+') && t2.is_Operator_And_Is_Value('(')) {
    //if that's the case it'll push t2 to the new_Tokens vector
    new_Tokens.push_back(t2);
  } else {
    //If it's not '+(' then it'll push the tokens back onto the stack
    r_Stack.push(t2);
    r_Stack.push(t1);
  }
  //While the stack size is greater than or eqaul to 3 it'll do the following
  while (r_Stack.size() >= 3) {
    //Get the first 3 elements from the reversed stack
    t1 = top_And_Pop<Token>(r_Stack); //The 1st element
    t2 = top_And_Pop<Token>(r_Stack); //The 2nd element
    t3 = top_And_Pop<Token>(r_Stack); //The 3rd element
    //Uses an AND operator with 3 conditions
    //Checks to see if t1 has an intersection with these "+/-*%^("
    //Checks to see if t2 is the addition sign
    //Checks to see if t3 is an opening parenthesis
    if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('+') && t3.is_Operator_And_Is_Value('(')) {
      //If that is the case it'll push these elements to the back of the new_Tokens vector getting rid of the '+' sign
      //t1 is pushed to the back
      new_Tokens.push_back(t1);
      //t3 is pushed to the back
      new_Tokens.push_back(t3);
      //continue to the next iteration of the loop
      continue;
    }
    //If the if statement isn't true it'll do the following
    //It'll push t1 to the back of new_Tokens
    //Then push t3 to the top of the reversed stack
    //Finally push t2 to the top of the reversed stack
    new_Tokens.push_back(t1);
    r_Stack.push(t3);
    r_Stack.push(t2);
  }
  //While the stack isn't empty it'll push the rest of the Tokens from the reversed stack to the vector new_Tokens
  while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));
  //Returns the modified vector of Tokens
  return new_Tokens;
}
//This function will handle - unary operators wiht Parenthesis
std::vector<Token> negative_Rewriter_For_Parentheses(std::vector<Token> old_Tokens) {
  //This vector stores the modified token vector 
  std::vector<Token> new_Tokens;
  //This creates a reversed stack from the old_Tokens given in the parameters
  std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);
  //Stores the first element in the reversed stack
  Token t1 = top_And_Pop<Token>(r_Stack);
  //Stores the second element in the reversed stack
  Token t2 = top_And_Pop<Token>(r_Stack);
  Token t3('!'); //This is not being used yet, this is dummy value
  //Checks to see if the t1 is '-' and t2 is '('
  if (t1.is_Operator_And_Is_Value('-') && t2.is_Operator_And_Is_Value('(')) {
    //If that is the case it'll replace '-(' with '(-1*('
    new_Tokens.push_back(Token('('));
    new_Tokens.push_back(Token('-'));
    new_Tokens.push_back(Token(1.0l));
    new_Tokens.push_back(Token('*'));
    new_Tokens.push_back(Token('('));
    //initiates the open_Parentheses_Count with 1 which counts the number of open paraentheses
    int open_Parentheses_Count = 1;
    //Tempory stores a backup vector
    std::vector<Token> backup;
    //Uses a while loop to iterate through the stack until the matching closing parenthesis is found
    while (open_Parentheses_Count > 0) {
      //Gets the top Token from the reversed stack
      Token t = top_And_Pop<Token>(r_Stack);
      //Adds it to the back of the backup vector
      backup.push_back(t);
      //If it's a closing parenthesis it'll minus 1 to the open_Parentheses_Count
      if (t.is_Operator_And_Is_Value(')')) open_Parentheses_Count--;
      //If it's an opening parenthesis it'll add 1 to the open_Parentheses_Count
      if (t.is_Operator_And_Is_Value('(')) open_Parentheses_Count++;
    }
    //Pushes a closing parenthesis to the top of the stack
    r_Stack.push(Token(')'));
    //Gets the size of the backup vector
    int backup_Size = backup.size();
    //Uses a for loop to iterate through the backup vector
    //Add the back of the backup vector to the top of the reveresed stack    
    for (int i = 0; i < backup_Size; i++) {r_Stack.push(backup.back()); backup.pop_back();}
  } else {
    //Push t2 to the top of the reversed stack
    r_Stack.push(t2);
    //Push t1 to the top of the reversed stack
    r_Stack.push(t1);
  }
  //While the stack size is greater than or eqaul to 3 it'll do the following
  while (r_Stack.size() >= 3) {
    //Get the first 3 elements from the reversed stack
    t1 = top_And_Pop<Token>(r_Stack); //The 1st element
    t2 = top_And_Pop<Token>(r_Stack); //The 2nd element
    t3 = top_And_Pop<Token>(r_Stack); //The 3rd element

    //Uses an AND operator with 3 conditions
    //Checks to see if t1 has an intersection with these "+/-*%^("
    //Checks to see if t2 is the subtraction sign
    //Checks to see if t3 is an opening parenthesis
    if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('-') && t3.is_Operator_And_Is_Value('(')) {
      //If that is the case it'll push t1 to the back of new_Tokens
      //Then transform '-(' to '(-1*('
      new_Tokens.push_back(t1);
      new_Tokens.push_back(Token('('));
      new_Tokens.push_back(Token('-'));
      new_Tokens.push_back(Token(1.0l));
      new_Tokens.push_back(Token('*'));
      new_Tokens.push_back(Token('('));

      //initiates the open_Parentheses_Count with 1 which counts the number of open paraentheses
      int open_Parentheses_Count = 1;
      //Tempory stores a backup vector
      std::vector<Token> backup;
      //Uses a while loop to iterate through the stack until the matching closing parenthesis is found
      while (open_Parentheses_Count > 0) {
        //Gets the top Token from the reversed stack
        Token t = top_And_Pop<Token>(r_Stack);
        //Adds it to the back of the backup vector
        backup.push_back(t);
        //If it's a closing parenthesis it'll minus 1 to the open_Parentheses_Count
        if (t.is_Operator_And_Is_Value(')')) open_Parentheses_Count--;
        //If it's an opening parenthesis it'll add 1 to the open_Parentheses_Count
        if (t.is_Operator_And_Is_Value('(')) open_Parentheses_Count++;
      }
      //Pushes a closing parenthesis to the top of the stack
      r_Stack.push(Token(')'));
      //Gets the size of the backup vector
      int backup_Size = backup.size();
      //Uses a for loop to iterate through the backup vector
      //Add the back of the backup vector to the top of the reveresed stack  
      for (int i = 0; i < backup_Size; i++) {r_Stack.push(backup.back()); backup.pop_back();}
      //continue to the next iteration of the loop
      continue;
    }
    //Pushes t1 to the back of the new_Tokens
    new_Tokens.push_back(t1);
    //Pushes t3 to the top of the reversed stack
    r_Stack.push(t3);
    //Pushes t2 to the top of the reversed stack
    r_Stack.push(t2);
  }
  //While the reversed stack is not empty push the top of the reversed stack to the back of the new_Tokens vector
  while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));
  //Return the modified new_Tokens vector
  return new_Tokens;
}
//This function will handle - unary operators with operands
std::vector<Token> negative_Rewriter_For_Operands(std::vector<Token> old_Tokens) {
  //This vector stores the modified token vector
  std::vector<Token> new_Tokens;
  //This creates a reversed stack from the old_Tokens given in the parameters
  std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);
  //Stores the first element in the reversed stack
  Token t1 = top_And_Pop<Token>(r_Stack);
  //Stores the second element in the reversed stack
  Token t2 = top_And_Pop<Token>(r_Stack);
  Token t3('!');//This is just a dummy value, until it is set to something else
  //Checks to see if t1 is an '-' and if t2 is NOT an operator
  if (t1.is_Operator_And_Is_Value('-') && !t2.is_This_An_Operator()) {
    //If true, it'll push to the back of the new_Tokens with the negated operand
    new_Tokens.push_back(Token(t2.get_Operand()*-1.0));
  } else {
    //If false, it push the tokens back onto the stack
    r_Stack.push(t2); //Pushes t2 to the top of the reversed stack
    r_Stack.push(t1); //Pushes t3 to the top of the reversed stack
  }
  //While the stack size is greater than or eqaul to 3 it'll do the following
  while(r_Stack.size() >= 3) {
    //Get the first 3 elements from the reversed stack
    Token t1 = top_And_Pop<Token>(r_Stack); //The 1st element
    Token t2 = top_And_Pop<Token>(r_Stack); //The 2nd element
    Token t3 = top_And_Pop<Token>(r_Stack); //The 3rd element
    //Uses an AND operator with 3 conditions
    //Checks to see if t1 has an intersection with these "+/-*%^("
    //Checks to see if t2 is the subtraction sign
    //Checks to see if t3 is NOT an operator
    if (t1.is_Operator_And_Has_Intersection("+/-*%^(") && t2.is_Operator_And_Is_Value('-') && !t3.is_This_An_Operator()) {
      //If true, it'll do the following:
      //Add t1 to the back of new_Tokens
      //Then it'll push the negated t3 operand to the back of the new_Tokens
      new_Tokens.push_back(t1);
      new_Tokens.push_back(Token(t3.get_Operand()*-1.0));
      //continue to the next iteration of the loop
      continue;
    }

    //If the if statement isn't true it'll do the following
    //It'll push t1 to the back of new_Tokens
    //Then push t3 to the top of the reversed stack
    //Finally push t2 to the top of the reversed stack
    new_Tokens.push_back(t1);
    r_Stack.push(t3);
    r_Stack.push(t2);

  }
  //While the reversed stack is not empty push the top of the reversed stack to the back of the new_Tokens vector
  while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));
  //Returns the modified new_Tokens vector
  return new_Tokens;
}
//This function will handle + unary operators with operands
std::vector<Token> positive_Rewriter_For_Operands(std::vector<Token> old_Tokens) {
  //This vector stores the modified token vector
  std::vector<Token> new_Tokens;
  //This creates a reversed stack from the old_Tokens given in the parameters
  std::stack<Token> r_Stack = create_Reverse_Stack<Token>(old_Tokens);
  //Stores the first element in the reversed stack
  Token t1 = top_And_Pop<Token>(r_Stack);
  //Stores the second element in the reversed stack
  Token t2 = top_And_Pop<Token>(r_Stack);
  Token t3('!');//This is just a dummy value until it gets set to something else
  //Checks to see if t1 is '+' AND t2 is NOT an operator
  if (t1.is_Operator_And_Is_Value('+') && !t2.is_This_An_Operator()) {
    //If true, it'll push to the back of the new_Tokens with operand
    new_Tokens.push_back(t2);
  } else {
    //If false, it push the tokens back onto the stack
    r_Stack.push(t2); //Pushes t2 to the top of the stack
    r_Stack.push(t1); //Pushes t1 to the top of the stack
  }
  //While the stack size is greater than or eqaul to 3 it'll do the following
  while (r_Stack.size() >= 3) {
    //Get the first 3 elements from the reversed stack
    t1 = top_And_Pop<Token>(r_Stack); //The 1st element 
    t2 = top_And_Pop<Token>(r_Stack); //The 2nd element
    t3 = top_And_Pop<Token>(r_Stack); //The 3rd element
    //Uses an AND operator with 3 conditions
    //Checks to see if t1 has an intersection with these "+/-*%^("
    //Checks to see if t2 is the addition sign
    //Checks to see if t3 is NOT an operator
    if (t1.is_Operator_And_Has_Intersection("+-/*%^(") && t2.is_Operator_And_Is_Value('+') && !t3.is_This_An_Operator()) {
      //If true, it'll push t1 to the back of new_Tokens then push t3 to the back
      new_Tokens.push_back(t1);
      new_Tokens.push_back(t3);
      //continue to the next iteration of the loop
      continue;
    }
    //If the if statement isn't true it'll do the following
    //It'll push t1 to the back of new_Tokens
    //Then push t3 to the top of the reversed stack
    //Finally push t2 to the top of the reversed stack
    new_Tokens.push_back(t1);
    r_Stack.push(t3);
    r_Stack.push(t2);
  }
  //While the reversed stack is not empty push the top of the reversed stack to the back of the new_Tokens vector
  while (!r_Stack.empty()) new_Tokens.push_back(top_And_Pop<Token>(r_Stack));
  //Returns the modified new_Tokens vector
  return new_Tokens;
}

public:

//Constructor for the UnaryRewriter class
UnaryRewriter(std::vector<Token> _ts, ErrorReporter * _error_Report) {
  //Assign the input vector of Tokens to the memeber variable 'ts'
  ts = _ts;
  //Assign the input ErrorReporter pointer to the member variable 'error_Report'
  error_Report = _error_Report;
}
//This function returns the Tokens
std::vector<Token> get_Tokens() {
  //Returns the vector of Tokens stored in the 'ts' memeber variable
  return ts;
}


void fix() {
  //Rewrites the Tokens to handle positive parentheses
  ts = positive_Rewriter_For_Parentheses(ts);

  //This is a hack, it things should not be done this way
  //Gets the size of the Token
  int old_Size = ts.size();
  while (true) {
    //Rewrites the Tokens to handle negative parentheses
    ts = negative_Rewriter_For_Parentheses(ts);
    //If the old size equals the new size then break out of the loop
    if (old_Size == ts.size()) break;
    //Set old size to the new size
    old_Size = ts.size();
  }
  //This is the end of the hack

  //Do not put these before the parentheses rewriter.
  //The parentheses rewriter creates unary operators associated with operands.
  //Rewrites the Tokens to handle positie operands
  ts = positive_Rewriter_For_Operands(ts);
  //Rewrites the Tokens to handle negative operands
  ts = negative_Rewriter_For_Operands(ts);

}

};
//End of the ifndef directive for UNARYREWRITER_HPP
#endif
