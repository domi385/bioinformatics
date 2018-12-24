//
// Created by dplus on 22.12.2018..
//
#include <algorithm>
#include "group.h"

Group::Group(std::vector<Path> &paths) {
  this->paths_ = paths;
}

int Group::GetMaxFrequency(){
  return max_frequency_;
}

void Group::FilterGroup() {
  CalculateFrequencies();
  std::vector<Path> filtered_paths;

  for(int i=0, end = paths_.size(); i < end; i++){
    int index = paths_[i].GetLength() - min_length_;
    int frequency = frequencies_[index];
    if(frequency >= 0.5 * max_frequency_){
      filtered_paths.push_back(paths_[i]);
    }
  }
  paths_ = filtered_paths;
}

void Group::CalculateFrequencies() {
  int n = max_length_ - min_length_ + 1;

  frequencies_.resize(n, 0);
  for (int i = 0, end = paths_.size(); i < end; i++) {
    int index = paths_.at(i).GetLength() - min_length_;
    frequencies_.at(index)++;
  }


  max_frequency_ = *std::max_element(std::begin(frequencies_), std::end(frequencies_));
  //TODO save max frequency length

}