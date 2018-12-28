// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include "graph_structures/path_selection/overlap_selection.h"

#include <vector>
#include <string>
#include <unordered_set>

#include "graph_structures/edge.h"

Edge *OverlapSelection::SelectEdge(
      std::vector<Edge*> &edges,
      std::unordered_set<std::string> &used_nodes) {
  double max_overlap_score = 0;
  Edge *max_edge = NULL;

  for (int i = 0, end = edges.size(); i < end; i++) {
    Edge* edge = edges[i];
    if (used_nodes.find(edge->GetIdEnd()) == used_nodes.end()) {
      if (edge->GetOverlapScore() > max_overlap_score) {
        max_overlap_score = edge->GetOverlapScore();
        max_edge = edges[i];
      }
    }
  }
  return max_edge;
}
