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

#include "graph_structures/path_selection/overlap_selection.h"

#include <vector>
#include <string>
#include <unordered_set>

#include "graph_structures/edge.h"

Edge *OverlapSelection::SelectEdge(
      std::vector<Edge*> &edges,
      std::unordered_set<std::string> &used_nodes) {
  double max_overlap_score = 0;
  Edge *max_edge = NULL;

  for (int i = 0, end = edges.size(); i < end; i++) {
    Edge* edge = edges[i];
    if (used_nodes.find(edge->GetIdEnd()) == used_nodes.end()) {
      if (edge->GetOverlapScore() > max_overlap_score) {
        max_overlap_score = edge->GetOverlapScore();
        max_edge = edges[i];
      }
    }
  }
  return max_edge;
}
