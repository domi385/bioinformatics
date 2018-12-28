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

#include <unordered_set>
#include <vector>
#include <tuple>

#include "graph_structures/consensus_sequence.h"
#include "graph_structures/sequence_node.h"
#include "graph_structures/path.h"

#ifndef SRC_GRAPH_STRUCTURES_CONNECTION_NODE_H_
#define SRC_GRAPH_STRUCTURES_CONNECTION_NODE_H_

class ConnectionNode {
 private:
  std::vector<SequenceNode *> contained_nodes_;
  std::vector<ConsensusSequence *> sequences_;
  std::vector<Path *> connecting_paths_;
  double conflict_index_;

 public:
  ConnectionNode(SequenceNode *origin,
                 std::vector<ConsensusSequence *> origin_sequences);
  void CalculateConflictIndex();

  void ConnectNodes(ConnectionNode *connection_node, Path *connection);
  void RecalculateConflictIndex(std::unordered_set<ConnectionNode *> targets);
  double GetConflictIndex();

  SequenceNode *GetOriginNode();
  std::tuple<SequenceNode *, Path *> GetTarget();

  std::vector<SequenceNode*> GetNodes();
  std::vector<Path *> GetConnectingPaths();
};

#endif  // SRC_GRAPH_STRUCTURES_CONNECTION_NODE_H_
