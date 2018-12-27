//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include <string>
#include <unordered_set>
#include "../edge.h"
#include "node_selection.h"

#ifndef SCAFFOLD_OVERLAP_SELECTION_H
#define SCAFFOLD_OVERLAP_SELECTION_H

class OverlapSelection : public NodeSelection {
 public:
  Edge *SelectEdge(std::vector<Edge*> &edges,
                   std::unordered_set<std::string> &used_nodes) override;
};

#endif //SCAFFOLD_OVERLAP_SELECTION_H
