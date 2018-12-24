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
  std::string end_node_id_;
  bool finalized_;

 public:
  explicit Path(SequenceNode &start_node);
  void Add(SequenceNode &node, Edge &edge);
  void Finalize();
  long GetLength();
  bool operator< (const Path &other) const;
  std::string GetEndId();
};

#endif //SCAFFOLD_PATH_H
