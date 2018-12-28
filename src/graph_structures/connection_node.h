// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

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
