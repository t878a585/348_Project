/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class ErrorReporter {
private:
    struct ErrorReport {
        std::string module_Name;
        std::string error_Description;
    };

    std::vector<std::unique_ptr<ErrorReport> > error_List;

public:
    void add_error(const char *module_Name, const char *error_Description) {
        std::unique_ptr<ErrorReport> report(new ErrorReport());
        report->module_Name = module_Name;
        report->error_Description = error_Description;
        error_List.push_back(std::move(report));
    }

    int get_error_count() const {
        return error_List.size();
    }

    void remove_errors() {
        error_List.clear(); // Smart pointers handle memory automatically
    }

    std::string get_error_string(int index) const {
        const ErrorReport &report = *error_List[index];
        return report.module_Name + ": " + report.error_Description + "\n";
    }

    std::string get_all_errors() const {
        std::string all_errors;
        for (size_t i = 0; i < error_List.size(); ++i) {
            all_errors += get_error_string(i);
        }
        return all_errors;
    }
	void print_And_Clear_Errors() {
		int error_Count = get_error_count();

		for (int i = 0; i < error_Count; i++) {
			char *error_String = strdup(get_error_string(i).c_str());
			// Use error_String as needed
			//free(error_String); 
			
			std::cout << error_String;

			delete error_String;
		}

		remove_errors();

	}
};

#endif