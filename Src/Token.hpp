//Checks if the TOKEN_HPP macro has not been defined before in the code to prevent multiple inclusion
#ifndef TOKEN_HPP
//If TOKEN_HPP is not defined, define it to avoid multiple inclusion of the header file
#define TOKEN_HPP

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