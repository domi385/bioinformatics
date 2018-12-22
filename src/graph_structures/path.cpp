//
// Created by dplus on 22.12.2018..
//

#include "path.h"
#include "sequence_node.h"

Path::Path(SequenceNode start_node, Edge start_edge){
    this->path_.push_back(start_node);
    this->edges_.push_back(start_edge);
    this->finalized_ = false;
}


void Path::add(SequenceNode node, Edge edge){
    this->path_.push_back(node);
    this->edges_.push_back(edge);

}

void Path::finalize() {
    //TODO add finalization, calculate path length
    finalized_ = true;
}

long Path::getLength() {
    if (!finalized_){
        throw "Path is not finalized";
    }
    return length_;
}