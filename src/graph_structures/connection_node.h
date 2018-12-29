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

#include <unordered_set>
#include <vector>
#include <tuple>

#include "graph_structures/consensus_sequence.h"
#include "graph_structures/sequence_node.h"
#include "graph_structures/path.h"

#ifndef SRC_GRAPH_STRUCTURES_CONNECTION_NODE_H_
#define SRC_GRAPH_STRUCTURES_CONNECTION_NODE_H_

/**
 * Connection node represents node in connection graph and containes connected
 * sequence nodes.
 */
class ConnectionNode {
 private:
  /**
   * Nodes contained in current connection node.
   */
  std::vector<SequenceNode *> contained_nodes_;
  /**
   * Consensus sequence from connection node representing possible connections
   * to expand connection node.
   */
  std::vector<ConsensusSequence *> sequences_;
  /**
   * Paths that connect contained nodes.
   */
  std::vector<Path *> connecting_paths_;
  /**
   * Possible connections conflict index.
   */
  double conflict_index_;

 public:
  /**
   * Constructor that initializes connection node with a sequence node.
   * @param origin origin sequence node
   * @param origin_sequences possible sequences from origin node
   */
  ConnectionNode(SequenceNode *origin,
                 std::vector<ConsensusSequence *> origin_sequences);
  /**
   * Method calculates connection node conflict index for possible connections.
   */
  void CalculateConflictIndex();
  /**
   * Method connects two connection nodes. All nodes in given connection nodes
   * are added to current connection node and path connecting two nodes
   * is saved.
   * @param connection_node connection node that needs to be connected with
   * current node
   * @param connection path connecting current and given connection node
   */
  void ConnectNodes(ConnectionNode *connection_node, Path *connection);
  /**
   * Method recalculates current node conflict index based on used target nodes.
   * @param targets nodes that are available targets for connecting
   */
  void RecalculateConflictIndex(std::unordered_set<ConnectionNode *> targets);
  /**
   * Method obtaines connection node conflict index.
   * @return conflict index
   */
  double GetConflictIndex();
  /**
   * Method obtains connection node origin.
   * @return origin node
   */
  SequenceNode *GetOriginNode();
  /**
   * Method returns desired target for connecting.
   * @return tuple containing sequence node and path for a target to which to
   * connect connection node
   */
  std::tuple<SequenceNode *, Path *> GetTarget();
  /**
   * Method returns nodes contained in current connection node.
   * @return contained nodes
   */
  std::vector<SequenceNode*> GetNodes();
  /**
   * Method returns paths that connect contained nodes.
   * @return connecting paths
   */
  std::vector<Path *> GetConnectingPaths();
};

#endif  // SRC_GRAPH_STRUCTURES_CONNECTION_NODE_H_
