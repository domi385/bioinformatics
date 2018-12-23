//
// Created by dplus on 22.12.2018..
//

#include <string>
#include "../file_structures/paf_entry.h"

#ifndef SCAFFOLD_EDGE_H
#define SCAFFOLD_EDGE_H


class Edge {
private:
    std::string id_end_;
    double overlap_score_;
    double extension_score_;
    double sequence_identity_;
    long overlap_length_;

    long overhang_origin_; //oh1
    long overhang_target_; //oh2
    long extension_len_origin_; //el1
    long extension_len_target_; //el2
    long overlap_len_origin_; //ol1
    long overlap_len_target_; //ol2

public:
    //constructor
    Edge(PafEntry entry);

    //getters
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
};


#endif //SCAFFOLD_EDGE_H
