//
// Created by dplus on 26.12.2018..
//


#include <unordered_set>
#include <vector>
#include <tuple>
#include "consensus_sequence.h"
#include "sequence_node.h"
#include "path.h"

#ifndef BIOINFORMATICS_CONNECTION_NODE_H
#define BIOINFORMATICS_CONNECTION_NODE_H

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

#endif //BIOINFORMATICS_CONNECTION_NODE_H
