/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

#ifndef ERRORREPORTER_HPP
#define ERRORREPORTER_HPP

#include <vector> 
#include <cstring>
#include <cstdlib>

class ErrorReporter {
  private:

    struct error_Report {
      char * module_Name;
      char * error_Description;
    };

    std::vector<struct error_Report> error_List;
    public:
    void add_error(const char * module_Name, const char * error_Description) {
      struct error_Report report;
      report.module_Name = strdup(module_Name);
      report.error_Description = strdup(error_Description);

      error_List.push_back(report);
    }

    int get_error_count() {
      return error_List.size();
    }

    void remove_errors() {
      int error_Count = get_error_count();

      for (int i = 0; i < error_Count; i++) {
        struct error_Report current_Error = error_List[i];
        delete current_Error.module_Name;
        delete current_Error.error_Description;
      }

      error_List.clear();
    }

    char * get_error_string(int index){
      struct error_Report report = error_List[index];

      int module_Name_Length = strlen(report.module_Name);
      int error_Description_Length = strlen(report.error_Description);

      // Allocate memory and initialize with null character
      char * error_String = (char *)malloc(sizeof(char) * (module_Name_Length + error_Description_Length + 3));
      if (error_String == NULL) {
          // Handle memory allocation failure
          return NULL;
      }
      error_String[0] = '\0';

      strcat(error_String, report.error_Description);
      strcat(error_String, "\n");

      return error_String;
    }

};
#endif
