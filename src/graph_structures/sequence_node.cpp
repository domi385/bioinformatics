//
// Created by dplus on 22.12.2018..
//

#include "sequence_node.h"

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

std::vector<Edge> SequenceNode::GetEdges() {
  return edges_;
}

void SequenceNode::AddEdge(Edge &edge) {
  edges_.push_back(edge);
}


