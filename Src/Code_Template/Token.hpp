#ifndef TOKEN_HPP
#define TOKEN_HPP

class Token {
        private:
                //Is true if operator, false if operand
                bool is_Operator;
                long long int operand_Value;
                char operator_Value;

        public:

                Token (long long int _operand_Value) {
                        is_Operator = false;
                        operand_Value = _operand_Value;
                }

                Token (char _operator_Value) {
                        is_Operator = true;
                        operator_Value = _operator_Value;
                }

                bool is_This_An_Operator() {
                        return is_Operator;
                }
};


#endif
