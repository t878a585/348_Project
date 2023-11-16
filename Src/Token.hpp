/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

#ifndef TOKEN_HPP
#define TOKEN_HPP
class Token {
        private:
                //Is true if operator, false if operand
                bool is_Operator;
                long double operand_Value;
                char operator_Value;

        public:

                Token (long double _operand_Value) {
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

		char get_Operator() { return operator_Value; }

		long double get_Operand() { return operand_Value; }
};


#endif
