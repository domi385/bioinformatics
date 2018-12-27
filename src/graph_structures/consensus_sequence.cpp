//
// Created by dplus on 26.12.2018..
//

#include "group.h"
#include "consensus_sequence.h"

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
