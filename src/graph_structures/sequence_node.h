//
// Created by dplus on 22.12.2018..
//

#include <string>
#include <vector>
#include "edge.h"

#ifndef SCAFFOLD_SEQUENCE_NODE_H
#define SCAFFOLD_SEQUENCE_NODE_H

class SequenceNode {
 private:
  std::string id_;
  bool is_conting_;
  long length_;
  std::vector<Edge> edges;

 public:
  //constructor
  SequenceNode(std::string& id, long length, bool is_conting);

  //getters
  std::string getId();
  bool isConting();
  long getLength();
  std::vector<Edge> getEdges();

  void add_edge(Edge &edge);
};

#endif //SCAFFOLD_SEQUENCE_NODE_H
