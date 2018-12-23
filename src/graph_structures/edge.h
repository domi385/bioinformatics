//
// Created by dplus on 22.12.2018..
//

#include <string>
#include "paf_entry.h"

#ifndef SCAFFOLD_EDGE_H
#define SCAFFOLD_EDGE_H


class Edge {
private:
    std::string id_end_;
    double overlap_score_;
    double extension_score_;
    double sequence_identity_;
    long overlap_length_;

    long overhang_start_; //oh1
    long overhang_end_; //oh2
    long extension_len_start_; //el1
    long extension_len_end_; //el2
    long overlap_len_start_; //ol1
    long overlap_len_end_; //ol2

public:
    //constructor
    Edge(PafEntry entry);

    //getters
    std::string GetIdEnd();
    double GetOverlapScore();
    double GetExtensionScore();
    double GetSequenceIdentity();
    long GetOverlapLength();
    long GetOverhangStart();
    long GetOverhangEnd();
    long GetExtensonLenStart();
    long GetExtensonLenEnd();
    long GetOverlapLenStart();
    long GetOverlapLenEnd();
};


#endif //SCAFFOLD_EDGE_H
