CLASS NAME: IOHandler
//////////////////////////////////////////

/* This starts the expression processing loop.
 * It will take in an expression, pass it to a InfixToPostfix object.
 * If there were any errors, it reports them and stops processing the expression.
 *
 * If there weren't any errors, provide the output of InfixToPostfix object to a PostfixEvaluator object.
 * If there are errors, report them and stop, otherwise, return the value of the expression and wait for 
 * the next user input.
 *
 * ctrl-c should end the program.
 * 
 * (@return)
 */

void execute();
