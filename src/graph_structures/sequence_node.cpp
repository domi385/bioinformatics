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
