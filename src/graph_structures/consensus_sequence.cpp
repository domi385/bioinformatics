// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include "graph_structures/group.h"
#include "graph_structures/consensus_sequence.h"

ConsensusSequence::ConsensusSequence(Group *group,
                                     SequenceNode *origin,
                                     SequenceNode *target) {
  path_ = group->GetConsensusPath();
  path_number_ = group->GetMaxFrequency();
  origin_ = origin;
  target_ = target;
}

SequenceNode *ConsensusSequence::GetOrigin() {
  return origin_;
}

SequenceNode *ConsensusSequence::GetTarget() {
  return target_;
}

Path *ConsensusSequence::GetPath() {
  return path_;
}

int ConsensusSequence::GetPathNumber() {
  return path_number_;
}
