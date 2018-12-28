/* Copyright 2018 Dunja Vesinger, Domagoj Pluščec
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "graph_structures/path.h"

#include <vector>
#include <string>

#include "graph_structures/edge.h"
#include "graph_structures/sequence_node.h"

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

std::vector<Edge *> Path::GetEdges() {
  return edges_;
}

std::vector<SequenceNode*> Path::GetNodes() {
  return path_;
}

