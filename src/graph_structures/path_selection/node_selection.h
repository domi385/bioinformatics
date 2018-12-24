//
// Created by dplus on 22.12.2018..
//
#include <vector>
#include <unordered_set>
#include "../edge.h"
#include "../sequence_node.h"

#ifndef SCAFFOLD_NODESELECTION_H
#define SCAFFOLD_NODESELECTION_H

class NodeSelection {
  public:
    virtual Edge* SelectEdge(std::vector<Edge> &edges, std::unordered_set<std::string> &used_nodes) ;
};

#endif //SCAFFOLD_NODESELECTION_H
