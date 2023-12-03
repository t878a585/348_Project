//Checks if the TOKEN_HPP macro has not been defined before in the code to prevent multiple inclusion
#ifndef TOKEN_HPP
//If TOKEN_HPP is not defined, define it to avoid multiple inclusion of the header file
#define TOKEN_HPP
//Include the string header file, providing functionalities for working with strings
#include <string>

//Definition of the Token class
class Token {

  private:
    //Is true if operator, false if operand
    bool is_Operator;
    //Value of the operand if the Token represents an operand
    long double operand_Value;
    //Value of the operator if the Token represents an operator
    char operator_Value;

  public:
    //Constructor for creating a Token representing an operand with a given value
    Token (long double _operand_Value) {
      //Set is_Operator to false because this Token represents an operand
      is_Operator = false;
      //Set the value of the operand
      operand_Value = _operand_Value;
    }
    //Constructor for creating a Token representing an operator with a given value
    Token (char _operator_Value) {
      //Set is_Operator to true because this Token represents an operator
      is_Operator = true;
      //Set the value of the operator
      operator_Value = _operator_Value;
    }


    //Public method to check if the Token represents an operator
    bool is_This_An_Operator() const {
      //Return the value of is_Operator, indicating whether the Token represents an operator (true) or an operand (false)
      return is_Operator;
    }
    //This function will return a boolean value
    bool is_Operator_And_Is_Value(char val) {
      //Returns true if both conditons are true using AND operator (&&)
      //The conditions are as follows:
      //1)if val is an operator using the is_This_An_Operator function
      //2) it checks to see if operator_Value is equal to val
      return is_This_An_Operator() && operator_Value == val;
    }
    //This function returns a boolean value depending on if there is an intersection or not
    bool is_Operator_And_Has_Intersection(std::string s) {
      //Gets the length of the input string
      int s_Length = s.size();
      //Checks to see if the current value is not an operator, if true it'll return false
      if (!is_This_An_Operator()) return false;
      //uses a for loop to iterate through each character in the input string
      for (int i = 0; i < s_Length; i++) {
        //Checks to see if the current value at the index i in the string is equal to the operator value
        //If true it means there is an intersect and it'll return true
        if (s[i] == operator_Value) return true;
      }
      //if there is no intersection then it'll return false
      return false;
    }

  //Public method to get the value of the operator if the Token represents an operator     
  char get_Operator() const {
    //Return the value of the operator
    return operator_Value; 
  }
  //Public method to get the value of the operand if the Token represents an operand
  long double get_Operand() const {
    //Returns the value of the operand
    return operand_Value; 
  }
};

//End of the ifndef directive for TOKEN_HPP
#endif
