//
// Created by dplus on 22.12.2018..
//

#include "path.h"

Path::Path(SequenceNode &start_node) {
  this->path_.push_back(start_node);
  this->finalized_ = false;
}

void Path::Add(SequenceNode &node, Edge &edge) {
  this->path_.push_back(node);
  this->edges_.push_back(edge);

}

void Path::Finalize() {
  end_node_id_ = path_.back().GetId();

  long sum = 0;
  for (int i=0, end=edges_.size(); i<end; i++){
    Edge currEdge = edges_.at(i);
    sum+=currEdge.GetExtensonLenTarget();
    //TODO calc lenght
  }

  finalized_ = true;
}

long Path::GetLength() {
  if (!finalized_) {
    throw "Path is not finalized";
  }


  return length_;
}

bool Path::operator< (const Path &other) const {
  return length_ < other.length_;
}
std::string Path::GetEndId() {
  if (!finalized_) {
    throw "Path is not finalized";
  }
  return end_node_id_;
}
