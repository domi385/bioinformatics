/* Copyright 2018 Dunja Vesinger, Domagoj Pluščec
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <vector>
#include <string>

#include "graph_structures/edge.h"
#include "graph_structures/sequence_node.h"

#ifndef SRC_GRAPH_STRUCTURES_PATH_H_
#define SRC_GRAPH_STRUCTURES_PATH_H_
/**
 * Class defines path between two conting nodes in overlap graph.
 */
class Path {
 private:
  /**
   * Collection of sequence nodes contained in the path.
   */
  std::vector<SequenceNode*> path_;
  /**
   * Path length.
   */
  long length_;
  /**
   * Collection edges that connect sequence nodes in the path.
   */
  std::vector<Edge*> edges_;
  /**
   * Id of path end sequence node.
   */
  std::string end_node_id_;
  /**
   * Finalized flag that is true if the path is finalized, false otherwise.
   */
  bool finalized_;

 public:
  /**
   * Path constructor that is initialized with start node.
   * @param start_node first node in the path
   */
  explicit Path(SequenceNode* start_node);
  /**
   * Path destructor.
   */
  ~Path();
  /**
   * Method expands path to given node connected with given edge.
   * @param node new path node
   * @param edge edge connecting path to given node
   */
  void Add(SequenceNode* node, Edge* edge);
  /**
   * Method finalizes path. After call of this method path last node is known
   * and path length is determined.
   */
  void Finalize();
  /**
   * Getter method for obtaining path length.
   * @return path length
   */
  long GetLength();
  /**
   * Getter method for obtaining path target id.
   * @return last node id
   */
  std::string GetEndId();
  /**
   * Getter method for obtaining edges contained in the path.
   * @return collection of contained edges
   */
  std::vector<Edge *> GetEdges();
  /**
   * Getter method for obtaining nodes contained in the path.
   * @return collection of contained nodes
   */
  std::vector<SequenceNode*> GetNodes();
  /**
   *
   * @param other
   * @return
   */
  bool operator<(const Path& other) const;
};

#endif  // SRC_GRAPH_STRUCTURES_PATH_H_
