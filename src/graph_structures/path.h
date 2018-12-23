//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include "sequence_node.h"

#ifndef SCAFFOLD_PATH_H
#define SCAFFOLD_PATH_H


class Path {

private:
    std::vector<SequenceNode> path_;
    long length_;
    std::vector<Edge> edges_;
    bool finalized_;

public:
    explicit Path(SequenceNode& start_node, Edge& start_edge);
    void add(SequenceNode& node, Edge& edge);
    void finalize();
    long getLength();
};




#endif //SCAFFOLD_PATH_H
