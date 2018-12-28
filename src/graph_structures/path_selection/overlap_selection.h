// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include <vector>
#include <string>
#include <unordered_set>

#include "graph_structures/path_selection/node_selection.h"
#include "graph_structures/edge.h"

#ifndef SRC_GRAPH_STRUCTURES_PATH_SELECTION_OVERLAP_SELECTION_H_
#define SRC_GRAPH_STRUCTURES_PATH_SELECTION_OVERLAP_SELECTION_H_

class OverlapSelection : public NodeSelection {
 public:
  Edge *SelectEdge(std::vector<Edge*> &edges,
                   std::unordered_set<std::string> &used_nodes) override;
};

#endif  // SRC_GRAPH_STRUCTURES_PATH_SELECTION_OVERLAP_SELECTION_H_

