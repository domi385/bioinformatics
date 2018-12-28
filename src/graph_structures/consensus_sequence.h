// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include "graph_structures/sequence_node.h"
#include "graph_structures/path.h"
#include "graph_structures/group.h"

#ifndef SRC_GRAPH_STRUCTURES_CONSENSUS_SEQUENCE_H_
#define SRC_GRAPH_STRUCTURES_CONSENSUS_SEQUENCE_H_

class ConsensusSequence {
 private:
  SequenceNode *origin_;
  SequenceNode *target_;
  Path *path_;
  int path_number_;

 public:
  ConsensusSequence(Group *group, SequenceNode *origin, SequenceNode *target);
  SequenceNode *GetOrigin();
  SequenceNode *GetTarget();
  Path *GetPath();
  int GetPathNumber();
};

#endif  // SRC_GRAPH_STRUCTURES_CONSENSUS_SEQUENCE_H_
