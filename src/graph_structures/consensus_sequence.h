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

#include "graph_structures/sequence_node.h"
#include "graph_structures/path.h"
#include "graph_structures/group.h"

#ifndef SRC_GRAPH_STRUCTURES_CONSENSUS_SEQUENCE_H_
#define SRC_GRAPH_STRUCTURES_CONSENSUS_SEQUENCE_H_
/**
 * Class describes consensus path between two contings.
 */
class ConsensusSequence {
 private:
  /**
   * Origin of current connecting path.
   */
  SequenceNode *origin_;
  /**
   * Target of current connecting path.
   */
  SequenceNode *target_;
  /**
   * Consensus path between origin and target.
   */
  Path *path_;
  /**
   * Consensus sequence path number.
   */
  int path_number_;

 public:
  /**
   * Constructor for consensus sequence made from origin and target node and
   * selected paths group.
   * @param group selected paths group between origin and target
   * @param origin origin conting node
   * @param target target conting node
   */
  ConsensusSequence(Group *group, SequenceNode *origin, SequenceNode *target);
  /**
   * Getter method for obtaining consensus sequence origin node.
   * @return consensus sequence origin node
   */
  SequenceNode *GetOrigin();
  /**
   * Getter method for obtaining consensus sequence target.
   * @return consensus sequence target
   */
  SequenceNode *GetTarget();
  /**
   * Getter method for obtaining path between origin and target.
   * @return path between origin and target
   */
  Path *GetPath();
  /**
   * Getter method for obtaining path number.
   * @return consensus sequence path number
   */
  int GetPathNumber();
};

#endif  // SRC_GRAPH_STRUCTURES_CONSENSUS_SEQUENCE_H_
