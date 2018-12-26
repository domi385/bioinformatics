//
// Created by dplus on 26.12.2018..
//



#ifndef BIOINFORMATICS_CONNECTION_NODE_H
#define BIOINFORMATICS_CONNECTION_NODE_H

#include "consensus_sequence.h"
#include "sequence_node.h"

class ConnectionNode {
 private:
  std::vector<SequenceNode*> contained_nodes_;
  std::vector<ConsensusSequence*> sequences_;
  double conflict_index_;

 public:
  ConnectionNode(SequenceNode* origin, std::vector<ConsensusSequence*> origin_sequences);
  void CalculateConflictIndex();

  void ConnectNodes(ConnectionNode* connection_node);
  void RecalculateConflictIndex(std::unordered_set<ConnectionNode*> targets);
  double GetConflictIndex();

  SequenceNode* GetOriginNode();
  SequenceNode *GetTarget();
};

#endif //BIOINFORMATICS_CONNECTION_NODE_H
