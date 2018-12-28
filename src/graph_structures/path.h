// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include <vector>
#include <string>

#include "graph_structures/edge.h"
#include "graph_structures/sequence_node.h"

#ifndef SRC_GRAPH_STRUCTURES_PATH_H_
#define SRC_GRAPH_STRUCTURES_PATH_H_

class Path {
 private:
  std::vector<SequenceNode*> path_;
  long length_;
  std::vector<Edge*> edges_;
  std::string end_node_id_;
  bool finalized_;

 public:
  explicit Path(SequenceNode* start_node);
  ~Path();
  void Add(SequenceNode* node, Edge* edge);
  void Finalize();
  long GetLength();
  bool operator<(const Path& other) const;
  std::string GetEndId();

  std::vector<Edge *> GetEdges();
  std::vector<SequenceNode*> GetNodes();
};

#endif  // SRC_GRAPH_STRUCTURES_PATH_H_
