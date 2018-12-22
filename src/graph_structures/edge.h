//
// Created by dplus on 22.12.2018..
//

#include <string>

#ifndef SCAFFOLD_EDGE_H
#define SCAFFOLD_EDGE_H


class Edge {
private:
    std::string id_end_;
    double overlap_score_;
    double extension_score_;
    double sequence_identity_;
    long overlap_length_;

    long oh1_;
    long oh2_;
    long el1_;
    long el2_;
    long ol1_;
    long ol2_;
};


#endif //SCAFFOLD_EDGE_H
