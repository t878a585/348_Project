CLASS NAME: InfixToPostfix
//////////////////////////////////////////

Resources:

https://www.prepbytes.com/blog/stacks/infix-to-postfix-conversion-using-stack/

Public Methods

/* This converts a string in infix form to a list of tokens in postfix form.
 * Remember to include Token.hpp. 
 * 
 * (infix_expression) The string that is in infix form. Do not modify this string.
 *
 * (error_reporter) If there is incorrect syntax being used, it must be reported using the error_Reporter
 * object.
 *
 * (@return) The list of tokens of the postfix form of the expression passed in.
 */

std::list<Token> convert(char * infix_expression, ErrorReporter * error_reporter);
