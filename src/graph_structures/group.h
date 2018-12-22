//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include "path.h"

#ifndef SCAFFOLD_GROUP_H
#define SCAFFOLD_GROUP_H


class Group {
private:
    std::vector<Path> paths_;
    long min_length_;
    long max_length_;
    int max_frequency;

    int frequencies_[];
    void calculate_frequencies();
public:
    Group(std::vector<Path>& paths);
    void filter_group();
};


#endif //SCAFFOLD_GROUP_H
