//
// Created by dplus on 22.12.2018..
//

#include "edge.h"

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
