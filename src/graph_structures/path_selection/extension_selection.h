//
// Created by dplus on 22.12.2018..
//
#include <vector>
#include "../edge.h"
#include "../sequence_node.h"
#include "node_selection.h"

#ifndef SCAFFOLD_EXTENSION_SELECTION_H
#define SCAFFOLD_EXTENSION_SELECTION_H

class ExtensionSelection : public NodeSelection {
 public:
  Edge *SelectEdge(std::vector<Edge> &edges, std::unordered_set<std::string> &used_nodes) override;
};

#endif //SCAFFOLD_EXTENSION_SELECTION_H
