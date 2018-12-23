//
// Created by dplus on 22.12.2018..
//
#include <vector>
#include "../edge.h"
#include "../sequence_node.h"
#include "node_selection.h"

#ifndef SCAFFOLD_EXTENSION_SELECTION_H
#define SCAFFOLD_EXTENSION_SELECTION_H

class ExtensionSelection {
  Edge SelectEdge(std::vector<Edge> &edges, std::unordered_set<SequenceNode> &used_nodes);
};

#endif //SCAFFOLD_EXTENSION_SELECTION_H
