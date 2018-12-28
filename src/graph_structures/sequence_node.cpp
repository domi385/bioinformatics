// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include "graph_structures/sequence_node.h"

#include <string>
#include <vector>

#include "graph_structures/edge.h"

SequenceNode::SequenceNode(std::string &id, long length, bool is_conting) {
  id_ = id;
  length_ = length;
  is_conting_ = is_conting;
}

long SequenceNode::GetLength() {
  return length_;
}

bool SequenceNode::IsConting() {
  return is_conting_;
}

std::string SequenceNode::GetId() {
  return id_;
}

std::vector<Edge*> SequenceNode::GetEdges() {
  return edges_;
}

void SequenceNode::AddEdge(Edge* edge) {
  edges_.push_back(edge);
}
