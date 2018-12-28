// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include <string>
#include <vector>

#include "graph_structures/edge.h"

#ifndef SRC_GRAPH_STRUCTURES_SEQUENCE_NODE_H_
#define SRC_GRAPH_STRUCTURES_SEQUENCE_NODE_H_

class SequenceNode {
 private:
  std::string id_;
  bool is_conting_;
  long length_;
  std::vector<Edge*> edges_;

 public:
  // constructor
  SequenceNode(std::string &id, long length, bool is_conting);

  // getters
  std::string GetId();
  bool IsConting();
  long GetLength();
  std::vector<Edge*> GetEdges();

  void AddEdge(Edge* edge);
};

#endif  // SRC_GRAPH_STRUCTURES_SEQUENCE_NODE_H_
