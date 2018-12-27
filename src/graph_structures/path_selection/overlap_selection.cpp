//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include <string>
#include <unordered_set>
#include "../edge.h"
#include "overlap_selection.h"

Edge *OverlapSelection::SelectEdge(std::vector<Edge*> &edges,
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
