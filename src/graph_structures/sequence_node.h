/* Copyright 2018 Dunja Vesinger, Domagoj Pluščec
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

#include <string>
#include <vector>

#include "graph_structures/edge.h"

#ifndef SRC_GRAPH_STRUCTURES_SEQUENCE_NODE_H_
#define SRC_GRAPH_STRUCTURES_SEQUENCE_NODE_H_

/**
 * Sequence node representing read or conting in overlap graph.
 */
class SequenceNode {
 private:
  /**
   * Sequence id.
   */
  std::string id_;
  /**
   * Conting flag that is true if the sequence is conting and false otherwise.
   */
  bool is_conting_;
  /**
   * Sequence length.
   */
  long length_;
  /**
   * Collection of edges that represent directed connections to other nodes.
   */
  std::vector<Edge*> edges_;

 public:
  /**
   * Constructor that constructs sequence node.
   * @param id sequence id
   * @param length sequence length
   * @param is_conting conting flag that is true if the sequence is conting and
   * false otherwise
   */
  SequenceNode(std::string &id, long length, bool is_conting);

  /**
   * Getter method for obtaining node id.
   * @return sequence node id
   */
  std::string GetId();
  /**
   * Method checks if the current node is conting.
   * @return true if the sequence is conting, false otherwise
   */
  bool IsConting();
  /**
   * Getter method for obtaining sequence length.
   * @return sequence length
   */
  long GetLength();
  /**
   * Method for obtaining edges that current sequence node has.
   * @return connection edges from current node
   */
  std::vector<Edge*> GetEdges();
  /**
   * Method adds given edge to sequence node collection of edges.
   * @param edge sequence node connection
   */
  void AddEdge(Edge* edge);
};

#endif  // SRC_GRAPH_STRUCTURES_SEQUENCE_NODE_H_
