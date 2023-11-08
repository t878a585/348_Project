CLASS NAME: PostfixEvaluator
//////////////////////////////////////////

Public Methods

/* This takes the postfix_Expression represented by the list of tokens
 * and evaluates its value.
 *
 * (postfix_expression) This is the expression that needs to be evaluated.
 *
 * (error_reporter) Reports invalid math operations (divide by zero), but
 * not bad syntax.
 * 
 * (@return) Returns the value equivalent to the given expression. This returns an undefined value
 * if an error was reported.
 */

long double evaluate(std::list<Token> postfix_expression, ErrorReporter * error_reporter);
