//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include <string>

#include "path.h"

#ifndef SCAFFOLD_GROUP_H
#define SCAFFOLD_GROUP_H

class Group {
 private:
  std::vector<Path *> paths_;
  long min_length_;
  long max_length_;
  int max_frequency_;
  long max_frequency_length_;
  std::string target_id_;

  std::vector<int> frequencies_;
  void CalculateFrequencies();

 public:
  Group(std::vector<Path *> &paths, std::string &target_id);
  void FilterGroup();
  int GetMaxFrequency();
  Path *GetConsensusPath();
  std::string GetTargetId();
};

#endif  // SCAFFOLD_GROUP_H
