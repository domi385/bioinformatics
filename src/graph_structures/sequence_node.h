//
// Created by dplus on 22.12.2018..
//

#include<string>
#include "edge.h"

#ifndef SCAFFOLD_SEQUENCE_NODE_H
#define SCAFFOLD_SEQUENCE_NODE_H


class SequenceNode {
    std::string id;
    bool is_conting;
    long length;

    void add_edge(Edge edge);

};


#endif //SCAFFOLD_SEQUENCE_NODE_H
