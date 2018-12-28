// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include <vector>
#include <string>

#include "graph_structures/path.h"

#ifndef SRC_GRAPH_STRUCTURES_GROUP_H_
#define SRC_GRAPH_STRUCTURES_GROUP_H_

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

#endif  // SRC_GRAPH_STRUCTURES_GROUP_H_
