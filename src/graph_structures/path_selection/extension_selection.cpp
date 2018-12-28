// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include "graph_structures/path_selection/extension_selection.h"

#include <string>
#include <vector>
#include <unordered_set>

#include "graph_structures/edge.h"

Edge *ExtensionSelection::SelectEdge(
      std::vector<Edge*> &edges,
      std::unordered_set<std::string> &used_nodes) {
  double max_extension_score = 0;
  Edge *max_edge = NULL;

  for (int i = 0, end = edges.size(); i < end; i++) {
    Edge* edge = edges[i];
    if (used_nodes.find(edge->GetIdEnd()) == used_nodes.end()) {
      if (edge->GetExtensionScore() > max_extension_score) {
        max_extension_score = edge->GetExtensionScore();
        max_edge = edges[i];
      }
    }
  }
  return max_edge;
}
