//
// Created by dplus on 22.12.2018..
//


#include <vector>
#include <string>
#include <iostream>
#include "project_utils.h"


namespace project_utils {

    void outputStringVector(std::vector<std::string> &collection) {
        for (int i = 0, end = collection.size(); i < end; i++) {
            std::cout << "'" << collection.at(i) << "' ";
        }
        std::cout << std::endl;
    }

    std::vector<std::string> splitString(std::string &s, std::string &delimiter) {
        std::vector<std::string> string_parts;

        size_t last_index = 0;
        size_t index = 0;
        while ((index = s.find(delimiter, last_index)) != std::string::npos) {
            std::string curr_part = s.substr(last_index, index - last_index);
            string_parts.push_back(curr_part);
            last_index = index + 1;
        }
        std::string last_part = s.substr(last_index);
        string_parts.push_back(last_part);
        return string_parts;
    }

}