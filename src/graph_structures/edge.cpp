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

#include "graph_structures/edge.h"

#include <string>

#include "file_structures/paf_entry.h"

Edge::Edge(PafEntry entry) {
  id_start_ = entry.GetOriginId();
  id_end_ = entry.GetTargetId();
  overlap_score_ = entry.GetOverlapScore();
  extension_score_ = entry.GetExtensionScore();
  sequence_identity_ = entry.GetSequenceIdentity();
  overlap_length_ = entry.GetOverlapLength();

  overhang_origin_ = entry.GetOverhangLenOrigin();
  overhang_target_ = entry.GetOverhangLenTarget();
  extension_len_origin_ = entry.GetExtensionLenOrigin();
  extension_len_target_ = entry.GetExtensionLenTarget();
  overlap_len_origin_ = entry.GetOverlapLenOrigin();
  overlap_len_target_ = entry.GetOverlapLenTarget();
}

std::string Edge::GetIdEnd() {
  return id_end_;
}

double Edge::GetOverlapScore() {
  return overlap_score_;
}

double Edge::GetExtensionScore() {
  return extension_score_;
}

double Edge::GetSequenceIdentity() {
  return sequence_identity_;
}

long Edge::GetOverlapLength() {
  return overlap_length_;
}

long Edge::GetOverhangOrigin() {
  return overhang_origin_;
}

long Edge::GetOverhangTarget() {
  return overhang_target_;
}

long Edge::GetExtensonLenOrigin() {
  return extension_len_origin_;
}

long Edge::GetExtensonLenTarget() {
  return extension_len_target_;
}

long Edge::GetOverlapLenOrigin() {
  return overlap_len_origin_;
}

long Edge::GetOverlapLenTarget() {
  return overlap_len_target_;
}
std::string Edge::GetStartId() {
  return id_start_;
}
