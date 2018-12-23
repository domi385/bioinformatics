//
// Created by dplus on 22.12.2018..
//

#include "sequence_node.h"

SequenceNode::SequenceNode(std::string& id, long length, bool is_conting) {
  id_=id;
  length_ = length;
  is_conting_ = is_conting;
}

long SequenceNode::getLength() {
  return length_;
}

bool SequenceNode::isConting() {
  return is_conting_;
}

std::string SequenceNode::getId() {
  return id_;
}

std::vector<Edge> SequenceNode::getEdges() {
  return edges;
}

void SequenceNode::add_edge(Edge &edge) {
  edges.push_back(edge);
}


