//
// Created by dplus on 22.12.2018..
//

#include "edge.h"

Edge::Edge(PafEntry entry){
    id_end_ = entry.GetTargetId();
    overlap_score_ = entry.GetOverlapScore();
    extension_score_ = entry.GetExtensionScore();
    sequence_identity_ = entry.GetSequenceIdentity();
    overlap_length_  = entry.GetOverlapLength();

    overhang_start_ = entry.getQueryStart();
    overhang_end_ = entry.getQueryEnd();
    extension_len_start_ = entry.GetExtensionLenStart();
    extension_len_end_= entry.GetExtensionLenEnd();
    overlap_len_start_ = entry.GetOverlapLenStart();
    overlap_len_end_ = entry.GetOverlapLenEnd();
}

std::string Edge::GetIdEnd(){
    return id_end_;
}

double Edge::GetOverlapScore(){
    return overlap_score_;
}

double Edge::GetExtensionScore(){
    return extension_score_;
}

double Edge::GetSequenceIdentity(){
    return sequence_identity_;
}

long Edge::GetOverlapLength(){
    return overlap_length_;
}

long Edge::GetOverhangStart(){
    return overhang_start_;
}

long Edge::GetOverhangEnd(){
    return overhang_end_;
}

long Edge::GetExtensonLenStart(){
    return extension_len_start_;
}

long Edge::GetExtensonLenEnd(){
    return extension_len_end_;
}

long Edge::GetOverlapLenStart(){
    return overlap_len_start_;
}

long Edge::GetOverlapLenEnd(){
    return overlap_len_end_;
}
