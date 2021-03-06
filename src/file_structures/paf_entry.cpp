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

#include "file_structures/paf_entry.h"

#include <string>
#include <vector>
#include <algorithm>

PafEntry::PafEntry(std::vector<std::string> &paf_parts) {
  std::string id1 = paf_parts.at(0);
  long len1 = stol(paf_parts.at(1));
  long s1 = stol(paf_parts.at(2));
  long e1 = stol(paf_parts.at(3));
  same_strand_ = paf_parts.at(4)
      == "+";
  std::string id2 = paf_parts.at(5);
  long len2 = stol(paf_parts.at(6));
  long s2 = stol(paf_parts.at(7));
  long e2 = stol(paf_parts.at(8));
  num_matches_ = stol(paf_parts.at(9));
  num_bases_ = stol(paf_parts.at(10));
  map_quality_ = stoi(paf_parts.at(11));
  sam_data_ = paf_parts.at(12);

  order_ = DetermineOrder(id1, id2, len1, len2, s1, e1, s2, e2);
  CalculateScores();
}

bool PafEntry::DetermineOrder(std::string &id1,
                              std::string &id2,
                              long len1,
                              long len2,
                              long s1,
                              long e1,
                              long s2,
                              long e2) {
  long l1 = s1;
  long ol1 = e1 - s1;
  long r1 = len1 - e1;
  long l2 = s2;
  long ol2 = e2 - s2;
  long r2 = len2 - e2;

  if (l1 + r2 > l2 + r1) {
    Store(id1, id2, len1, len2, l1, ol1, r1, l2, ol2, r2);
    return true;
  }
  Store(id2, id1, len2, len1, l2, ol2, r2, l1, ol1, r1);
  return false;
}

void PafEntry::Store(std::string &id1,
                     std::string &id2,
                     long len1,
                     long len2,
                     long el1,
                     long ol1,
                     long oh1,
                     long oh2,
                     long ol2,
                     long el2) {
  this->origin_id_ = id1;
  this->target_id_ = id2;
  this->origin_length_ = len1;
  this->target_length_ = len2;
  this->el_1_ = el1;
  this->ol_1_ = ol1;
  this->oh_1_ = oh1;
  this->oh_2_ = oh2;
  this->ol_2_ = ol2;
  this->el_2_ = el2;
}

void PafEntry::CalculateScores() {
  sequence_identity_ = num_matches_ /
      (double) std::min(origin_length_, target_length_);
  overlap_score_ = sequence_identity_ * (ol_1_ + ol_2_) / 2.;
  double mean_overhang = (oh_1_ + oh_2_) / 2.;
  extension_score_ = overlap_score_ + el_2_ / 2. - mean_overhang;
}

std::string PafEntry::GetTargetId() {
  return target_id_;
}

double PafEntry::GetOverlapScore() {
  return overlap_score_;
}
double PafEntry::GetExtensionScore() {
  return extension_score_;
}

double PafEntry::GetSequenceIdentity() {
  return sequence_identity_;
}
long PafEntry::GetOverlapLength() {
  return num_matches_;
}
long PafEntry::GetOverhangLenOrigin() {
  return oh_1_;
}
long PafEntry::GetOverhangLenTarget() {
  return oh_2_;
}
long PafEntry::GetExtensionLenOrigin() {
  return el_1_;
}
long PafEntry::GetExtensionLenTarget() {
  return el_2_;
}
long PafEntry::GetOverlapLenOrigin() {
  return ol_1_;
}
long PafEntry::GetOverlapLenTarget() {
  return ol_2_;
}
std::string PafEntry::GetOriginId() {
  return origin_id_;
}
