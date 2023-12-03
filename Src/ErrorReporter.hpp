//Include guard to prevent multiple inclusion of the ERRORREPORTER_HPP header file
#ifndef ERRORREPORTER_HPP
//If ERRORREPORTER_HPP is not defined, define it to avoid multiple inclusion of the header file
#define ERRORREPORTER_HPP
//Include the vector header file, providing functionalities for working with vectors
#include <vector> 
//Include the cstring header file, providing functionalities for string manipulation
#include <cstring>
//Include the cstdlib header file, providing funcions involving memory allocation and more
#include <cstdlib>
//Include the iostream header file, providing functionalities for input and output using streams
#include <iostream>

//Definition of the ErrorReporter class
class ErrorReporter {
  private:
    //Struct to represent an error report
    struct error_Report {
      //Member variable to store the module name associated with an error report
      //Which header file the error came from
      char * module_Name;
      //Member variable to store the error description associated with an error
      char * error_Description;
    };
    //Vector to store instances of the error_Report struct, formin a list of errors
    std::vector<struct error_Report> error_List;
  public:
    //This function adds an error to the error_List vector
    void add_error(const char * module_Name, const char * error_Description) {
      //Declare a local variable of type error_Report named report
      struct error_Report report;
      //Copy the provided module_Name string to the module_Name member of the report using strdup
      report.module_Name = strdup(module_Name);
      //Copy the provided error_Description string to the error_Description member of the report using strdup
      report.error_Description = strdup(error_Description);
      //Add the constructed error report to the error_List vector
      error_List.push_back(report);
    }
    //This function returns the number of errors
    int get_error_count() {
      //Returns the size of the error_List vector
      return error_List.size();
    }
    //clears list of errors that was created while an expression was evaluated
    void remove_errors() {
      //Gets the current count of the number of errors
      int error_Count = get_error_count();
      //Using a for loop it'll iterate through each error
      for (int i = 0; i < error_Count; i++) {
        //Gets the current error report
        struct error_Report current_Error = error_List[i];
        //Deletes the current module_Name from the allocated memory
        delete current_Error.module_Name;
        //Deletes the current error_Description from the allocated memory
        delete current_Error.error_Description;
      }
      //Clears the error_List vector, removing all of the errors
      error_List.clear();
    }
    //This function formats a certain error at an index
    char * get_error_string(int index){
      //Retrieves the error report at the index specified in the parameters
      struct error_Report report = error_List[index];
      //Calculates the length of the module_Name string
      int module_Name_Length = strlen(report.module_Name);
      //Calculates the length of the error_Description string
      int error_Description_Length = strlen(report.error_Description);

      // Allocate memory and initialize with null character
      char * error_String = (char *)malloc(sizeof(char) * (module_Name_Length + error_Description_Length + 3));
      if (error_String == NULL) {
          // Handle memory allocation failure
          return NULL;
      }
      //Initialize the first character of the error string with a null character
      error_String[0] = '\0';
      //Concatenate the error description to the error string
      strcat(error_String, report.error_Description);
      //Concatentate a newline character to the error string
      strcat(error_String, "\n");
      //Returns the formatted error string
      return error_String;
    }
    //This function will print the first error in the vector error_List, it's a void function so it won't return anything
    void print_first_error() {
      //Declares a variable named first_Error which is a struct that initializes with the first element in the error_List array
      struct error_Report first_Error = error_List[0];
      //Uses standard output to print the error description stored in first_Error
      //A newline is also printed using standard output
      std::cout << first_Error.error_Description << "\n";
        
    }

};
//End of the ifndef directive for ERRORREPORTER_HPP
#endif
