//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include "../edge.h"
#include "../sequence_node.h"
#include "node_selection.h"

#ifndef SCAFFOLD_MONTE_CARLO_SELECTION_H
#define SCAFFOLD_MONTE_CARLO_SELECTION_H

class MonteCarloSelection : public NodeSelection {

  Edge *SelectEdge(std::vector<Edge> &edges, std::unordered_set<std::string> &used_nodes) override;

};

#endif //SCAFFOLD_MONTE_CARLO_SELECTION_H
