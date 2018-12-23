//
// Created by dplus on 22.12.2018..
//

#include <string>
#include <vector>

#ifndef SCAFFOLD_PROJECT_UTILS_H
#define SCAFFOLD_PROJECT_UTILS_H

namespace project_utils {

void outputStringVector(std::vector<std::string> &collection);

std::vector<std::string> splitString(std::string &s, std::string &delimiter);
}

#endif //SCAFFOLD_PROJECT_UTILS_H
