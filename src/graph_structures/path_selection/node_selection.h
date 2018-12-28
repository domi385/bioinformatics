// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include <vector>
#include <unordered_set>
#include <string>

#include "graph_structures/edge.h"

#ifndef SRC_GRAPH_STRUCTURES_PATH_SELECTION_NODE_SELECTION_H_
#define SRC_GRAPH_STRUCTURES_PATH_SELECTION_NODE_SELECTION_H_

class NodeSelection {
 public:
  virtual Edge *SelectEdge(std::vector<Edge*> &edges,
                           std::unordered_set<std::string> &used_nodes) = 0;
};

#endif  // SRC_GRAPH_STRUCTURES_PATH_SELECTION_NODE_SELECTION_H_
