//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include "edge.h"
#include "sequence_node.h"
#include "path.h"

Path::Path(SequenceNode* start_node) {
  this->path_.push_back(start_node);
  this->finalized_ = false;
}

void Path::Add(SequenceNode* node, Edge* edge) {
  this->path_.push_back(node);
  this->edges_.push_back(edge);

}

void Path::Finalize() {
  end_node_id_ = path_.back()->GetId();

  Edge* first_edge = edges_[0];
  long length =
      first_edge->GetExtensonLenOrigin() + first_edge->GetOverlapLength();

  Edge* previus_edge = first_edge;
  for (int i = 1, end = edges_.size(); i < end; i++) {
    Edge* curr_edge = edges_[i];
    long begining_index =
        previus_edge->GetOverhangTarget() + previus_edge->GetOverlapLenTarget();
    long end_index =
        curr_edge->GetExtensonLenOrigin() + curr_edge->GetOverlapLenOrigin();
    length += end_index - begining_index;
    previus_edge = curr_edge;
  }
  Edge* last_edge = edges_.back();
  length += last_edge->GetExtensonLenTarget();

  length_ = length;
  finalized_ = true;
}

long Path::GetLength() {
  if (!finalized_) {
    throw "Path is not finalized";
  }

  return length_;
}

bool Path::operator<(const Path &other) const {
  return length_ < other.length_;
}
std::string Path::GetEndId() {
  if (!finalized_) {
    throw "Path is not finalized";
  }
  return end_node_id_;
}
Path::~Path() {
  path_.clear();
  path_.shrink_to_fit();

}
std::vector<SequenceNode*> Path::GetNodes(){
  return path_;
}

std::vector<Edge *> Path::GetEdges(){
  return edges_;
}
