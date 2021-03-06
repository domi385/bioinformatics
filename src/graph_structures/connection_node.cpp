/* Copyright 2018 Dunja Vesinger, Domagoj Pluščec
 *
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

#include "graph_structures/connection_node.h"

#include <algorithm>
#include <unordered_set>
#include <vector>
#include <tuple>

#include "graph_structures/consensus_sequence.h"
#include "graph_structures/sequence_node.h"
#include "graph_structures/path.h"

ConnectionNode::ConnectionNode(
      SequenceNode *origin,
      std::vector<ConsensusSequence *> origin_sequences) {
  contained_nodes_.push_back(origin);
  sequences_ = origin_sequences;

  CalculateConflictIndex();
}

void ConnectionNode::CalculateConflictIndex() {
  if (sequences_.empty()) {
    conflict_index_ = 1;
    return;
  }
  if (sequences_.size() == 1) {
    conflict_index_ = 0;
    return;
  }

  int max_np = 0;
  int second_max_np = 0;

  for (int i = 0, end = sequences_.size(); i < end; i++) {
    int curr_np = sequences_.at(i)->GetPathNumber();
    if (curr_np > max_np) {
      second_max_np = max_np;
      max_np = curr_np;
    } else if (curr_np > second_max_np) {
      second_max_np = curr_np;
    }
  }
  conflict_index_ = second_max_np / (double) max_np;
}

void ConnectionNode::RecalculateConflictIndex(
    std::unordered_set<ConnectionNode *> targets) {
  std::vector<ConsensusSequence *> new_sequences;

  std::unordered_set<SequenceNode *> target_nodes;

  for (auto it = targets.begin(); it != targets.end(); it++) {
    ConnectionNode *curr_node = *it;
    std::vector<SequenceNode *> curr_nodes = curr_node->contained_nodes_;
    for (int i = 0, end = curr_nodes.size(); i < end; i++) {
      target_nodes.emplace(curr_nodes.at(i));
    }
  }

  for (int i = 0, end = sequences_.size(); i < end; i++) {
    ConsensusSequence *curr_sequence = sequences_.at(i);

    if (target_nodes.find(curr_sequence->GetTarget()) != target_nodes.end()) {
      new_sequences.push_back(sequences_.at(i));
    }
  }

  sequences_.clear();
  sequences_ = new_sequences;
  CalculateConflictIndex();
}

void ConnectionNode::ConnectNodes(ConnectionNode *connection_node,
                                  Path *connection) {
  // ADD ALL CURR CONNECTIONS
  std::vector<SequenceNode *> target_nodes = connection_node->contained_nodes_;
  for (int i = 0, end = target_nodes.size(); i < end; i++) {
    contained_nodes_.push_back(target_nodes.at(i));
  }

  // CALC CURRENT CONSENSUS SEQUENCES
  std::vector<ConsensusSequence *>
      target_sequences = connection_node->sequences_;
  sequences_.clear();
  for (int i = 0, end = target_sequences.size(); i < end; i++) {
    ConsensusSequence *curr_consensus = target_sequences.at(i);
    if (std::find(contained_nodes_.begin(),
                  contained_nodes_.end(),
                  curr_consensus->GetTarget())
        == contained_nodes_.end()) {
      sequences_.push_back(target_sequences.at(i));
    }
  }

  // Add all paths to other nodes
  connecting_paths_.push_back(connection);
  std::vector<Path *>
      target_connecting_paths = connection_node->GetConnectingPaths();
  for (int i = 0, end = target_connecting_paths.size(); i < end; i++) {
    connecting_paths_.push_back(target_connecting_paths.at(i));
  }
}

double ConnectionNode::GetConflictIndex() {
  return conflict_index_;
}

SequenceNode *ConnectionNode::GetOriginNode() {
  return contained_nodes_.front();
}
std::tuple<SequenceNode *, Path *> ConnectionNode::GetTarget() {
  if (sequences_.empty()) {
    return std::make_tuple<SequenceNode *, Path *>(NULL, NULL);
  }

  ConsensusSequence *max_target = sequences_.at(0);
  int max_np = max_target->GetPathNumber();
  for (int i = 1, end = sequences_.size(); i < end; i++) {
    ConsensusSequence *curr_target = sequences_.at(i);
    int curr_np = curr_target->GetPathNumber();
    if (curr_np > max_np) {
      max_np = curr_np;
      max_target = curr_target;
    }
  }
  return std::make_tuple<SequenceNode *, Path *>(max_target->GetTarget(),
                                                 max_target->GetPath());
}

std::vector<SequenceNode *> ConnectionNode::GetNodes() {
  return contained_nodes_;
}

std::vector<Path *> ConnectionNode::GetConnectingPaths() {
  return connecting_paths_;
}
