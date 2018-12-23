//
// Created by dplus on 22.12.2018..
//
#include <algorithm>
#include "group.h"

Group::Group(std::vector<Path> &paths) {
  this->paths_ = paths;
}

void Group::FilterGroup() {
  CalculateFrequencies();
  std::vector<Path> filtered_paths;
  //TODO finish filtering groups
}

void Group::CalculateFrequencies() {
  int n = max_length_ - min_length_ + 1;

  frequencies_.resize(n, 0);
  for (int i = 0, end = paths_.size(); i < end; i++) {
    int index = paths_.at(i).getLength() - min_length_;
    frequencies_.at(index)++;
  }
  max_frequency_ = *std::max_element(std::begin(frequencies_), std::end(frequencies_));
}