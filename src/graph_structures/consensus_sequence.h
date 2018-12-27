//
// Created by dplus on 26.12.2018..
//

#include "sequence_node.h"
#include "path.h"
#include "group.h"

#ifndef BIOINFORMATICS_CONSENSUSSEQUENCE_H
#define BIOINFORMATICS_CONSENSUSSEQUENCE_H

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

#endif  // BIOINFORMATICS_CONSENSUSSEQUENCE_H
