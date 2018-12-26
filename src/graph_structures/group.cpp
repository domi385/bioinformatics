//
// Created by dplus on 22.12.2018..
//
#include <algorithm>
#include <iostream>
#include "group.h"

Group::Group(std::vector<Path *> &paths) {
  this->paths_ = paths;

  min_length_ = paths.at(0)->GetLength();
  max_length_ = paths.at(0)->GetLength();
  for (int i = 0, end = paths_.size(); i < end; i++) {
    Path *curr_path = paths.at(i);
    if (curr_path->GetLength() > max_length_) {
      max_length_ = curr_path->GetLength();
    }
    if (curr_path->GetLength() < min_length_) {
      min_length_ = curr_path->GetLength();
    }
  }
}

int Group::GetMaxFrequency() {
  return max_frequency_;
}

void Group::FilterGroup() {
  CalculateFrequencies();
  std::vector<Path *> filtered_paths;

  for (int i = 0, end = paths_.size(); i < end; i++) {
    int index = paths_[i]->GetLength() - min_length_;
    int frequency = frequencies_[index];
    if (frequency >= 0.5 * max_frequency_) {
      filtered_paths.push_back(paths_.at(i));
    }else{
      delete paths_.at(i);
    }
  }
  paths_ = filtered_paths;
}

void Group::CalculateFrequencies() {
  int n = max_length_ - min_length_ + 1;

  frequencies_.resize(n, 0);
  for (int i = 0, end = paths_.size(); i < end; i++) {
    int index = paths_.at(i)->GetLength() - min_length_;
    frequencies_.at(index)++;
  }
  int max_freq_index = 0;
  max_frequency_ = frequencies_.at(0);
  for (int i = 0; i < n; i++) {
    if (frequencies_.at(i) > max_frequency_) {
      max_freq_index = i;
      max_frequency_ = frequencies_.at(i);
    }
  }
  max_frequency_length_ = min_length_ + max_freq_index;
}