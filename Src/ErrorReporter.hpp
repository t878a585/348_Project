/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

#ifndef ERRORREPORTER_HPP
#define ERRORREPORTER_HPP

#include <vector> 
#include <cstring>

class ErrorReporter {
	private:

		struct error_Report {
			char * module_Name;
			char * error_Description;
		};

		std::vector<struct error_Report> error_List;
  	public:
		void add_error(char * module_Name, char * error_Description) {
			struct error_Report;
			error_Report.module_Name = strdup(module_Name);
			error_Report.error_Description = strdup(error_Description);

			error_List.push_back(error_Report);
		}

		int get_error_count() {
			return error_List.size();
		}

		void remove_errors() {
			int error_Count = get_error_count();

			for (int i = 0; i < error_Count; i++) {
				struct current_Error = error_List[i];
				delete error_List.module_Name;
				delete error_List.error_Description;
			}

			error_List.clear();
		}

		char * get_error_string(int index){
			struct error_Report = error_List[index];

			int module_Name_Length = strlen(error_List.module_Name);
			int error_Description_Length = strlen(error_List.error_Description);
			char * error_String = malloc(sizeof(char) * (module_Name_Length + error_Description_Length + 3));

			strcpy(error_String, error_List.module_Name);
			strcat(error_String, ":");
			strcat(error_String, error_List.error_Description);
			strcat(error_String, "\n");

			return error_String;
		}
		
};
#endif
