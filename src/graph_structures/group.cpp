//
// Created by dplus on 22.12.2018..
//
#include <algorithm>
#include "group.h"



Group::Group(std::vector<Path> &paths){
    this->paths_=paths;
}

void Group::filter_group(){
    calculate_frequencies();
    std::vector<Path> filtered_paths;
    //TODO finish filtering groups
}

void Group::calculate_frequencies(){
    int n = max_length_-min_length_+1;
    frequencies_ = int[n];
    for (int i=0, end = paths_.size(); i<end; i++){
        int index = paths_.at(i).getLength()-min_length_;
        frequencies_[index]++;
    }
    max_frequency = *std::max_element(frequencies_, frequencies_+n);
}