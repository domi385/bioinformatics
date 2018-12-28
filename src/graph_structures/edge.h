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

#include <string>
#include "file_structures/paf_entry.h"

#ifndef SRC_GRAPH_STRUCTURES_EDGE_H_
#define SRC_GRAPH_STRUCTURES_EDGE_H_

class Edge {
 private:
  std::string id_start_;
  std::string id_end_;
  double overlap_score_;
  double extension_score_;
  double sequence_identity_;
  long overlap_length_;

  long overhang_origin_;  // oh1
  long overhang_target_;  // oh2
  long extension_len_origin_;  // el1
  long extension_len_target_;  // el2
  long overlap_len_origin_;  // ol1
  long overlap_len_target_;  // ol2

 public:
  // constructor
  explicit Edge(PafEntry entry);

  // getters
  std::string GetIdEnd();
  double GetOverlapScore();
  double GetExtensionScore();
  double GetSequenceIdentity();
  long GetOverlapLength();
  long GetOverhangOrigin();
  long GetOverhangTarget();
  long GetExtensonLenOrigin();
  long GetExtensonLenTarget();
  long GetOverlapLenOrigin();
  long GetOverlapLenTarget();
  std::string GetStartId();
};

#endif  // SRC_GRAPH_STRUCTURES_EDGE_H_
