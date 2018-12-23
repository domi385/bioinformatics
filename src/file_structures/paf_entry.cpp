//
// Created by dplus on 20.12.2018..
//
#include <string>
#include <algorithm>
#include "paf_entry.h"

PafEntry::PafEntry(std::vector<std::string> paf_parts) {
  std::string id1 = paf_parts.at(0);
  long len1 = stol(paf_parts.at(1));
  long s1 = stol(paf_parts.at(2));
  long e1 = stol(paf_parts.at(3));
  same_strand_ = paf_parts.at(4) == "+"; //TODO handle same_strand depented on sequence order
  std::string id2 = paf_parts.at(5);
  long len2 = stol(paf_parts.at(6));
  long s2 = stol(paf_parts.at(7));
  long e2 = stol(paf_parts.at(8));
  num_matches_ = stol(paf_parts.at(9));
  num_bases_ = stol(paf_parts.at(10));
  map_quality_ = stoi(paf_parts.at(11));
  sam_data_ = paf_parts.at(12);

  order_ = determine_order(id1, id2, len1, len2, s1, e1, s2, e2);
  calculate_scores();

}

bool PafEntry::determine_order(std::string id1, std::string id2, long len1, long len2, long s1,
                               long e1, long s2, long e2) {

  long l1 = s1;
  long ol1 = e1 - s1;
  long r1 = len1 - e1;
  long l2 = s2;
  long ol2 = e2 - s2;
  long r2 = len2 - e2;

  if (l1 + r2 > l2 + r1) {
    store(id1, id2, len1, len2, l1, ol1, r1, l2, ol2, r2);
    return true;
  }
  store(id2, id1, len2, len1, l2, ol2, r2, l1, ol1, r1);
  return false;
}

void PafEntry::store(std::string id1, std::string id2, long len1, long len2, long el1, long ol1, long oh1, long oh2,
                     long ol2, long el2) {
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
void PafEntry::calculate_scores() {
  sequence_identity_ = num_matches_ /
      (double) std::min(origin_length_, target_length_);
  overlap_score_ = sequence_identity_ * (ol_1_ + ol_2_) / 2.;
  double mean_overhang = (oh_1_ + oh_2_) / 2.;
  extension_score_ = overlap_score_ + el_2_ / 2. - mean_overhang;
}

long PafEntry::getTargetLen() {
  return target_length_;
}

long PafEntry::getTargetStart() {
  return target_start_coord_;
}

long PafEntry::getQueryEnd() {
  return query_end_coord_;
}

long PafEntry::getQueryLen() {
  return origin_length_;
}

long PafEntry::getQueryStart() {
  return query_start_coord_;
}

long PafEntry::getTargetEnd() {
  return target_end_coord_;
}

long PafEntry::getNumMatchesWithoutGaps() {
  return num_matches_;
}
std::string PafEntry::GetTargetId() {
  return std::string();
}

double PafEntry::GetOverlapScore() {
  return overlap_score_;
}
double PafEntry::GetExtensionScore() {
  return extension_score_;
}
long PafEntry::GetOverlapLength() {
  //TODO get ol
  return 0;
}
double PafEntry::GetSequenceIdentity() {
  return sequence_identity_;
}
long PafEntry::GetExtensionLenStart() {
  //TODO get es start
  return 0;
}
long PafEntry::GetOverlapLenStart() {
  //TODO get ol start
  return 0;
}
long PafEntry::GetExtensionLenEnd() {
  //TODO get es end
  return 0;
}
long PafEntry::GetOverlapLenEnd() {
  //TODO get ol end
  return 0;
}
