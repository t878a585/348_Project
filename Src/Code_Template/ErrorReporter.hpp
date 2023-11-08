CLASS NAME: ErrorReporter
//////////////////////////////////////////

Public Methods


/* This function adds an error message to the list of errors
 *
 * (module_Name) This is the name of the module reporting the error.
 * This string must be duplicated. We must do this because the calling class may modify
 * the string later.
 *
 * (error_Description) This string describes the error that has occurred. As with the previous parameter,
 * this must also be duplicated.
 *
 * (@return) Nothing is returned.
 */

void add_error(char * module_Name, char * error_Description);


/* This function returns the amount of errors reported to it.
 *
 * (@return) The amount of errors reported. If there are none, 0 is returned.
 */

int get_error_count();


/* Removes all of the reported errors.
 *
 * (@return) Nothing is returned.
 */

void remove_errors();


/* This returns an error string for the given error index (starting from 0).
 * Do not call this if get_error_count() returns zero. This will result in undefined behavior.
 * The string returned must be freeable by the callee.
 *
 * (@return) Returns a string representing the error description and module that reported the error.
 */

char * get_error_string(int index);
