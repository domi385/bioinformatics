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

#include "graph_structures/path_selection/monte_carlo_selection.h"

#include <vector>
#include <string>
#include <unordered_set>
#include <random>

#include "graph_structures/edge.h"

Edge *SelectEdge(std::vector<Edge*> &edges,
                 std::unordered_set<std::string> &used_nodes) {
  std::vector<Edge*> potential_edges;
  double extension_score_sum;

  for (int i = 0, end = edges.size(); i < end; i++) {
    Edge* edge = edges[i];
    if (used_nodes.find(edge->GetIdEnd()) == used_nodes.end()) {
      extension_score_sum+=edge->GetExtensionScore();
      potential_edges.push_back(edge);
    }
  }

  if (potential_edges.size() == 0) {
    return NULL;
  }
  if (potential_edges.size() == 1) {
    return edges.front();
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0., extension_score_sum);
  double selected = dis(gen);

  for (int i = 0, end = potential_edges.size(); i < end; i++) {
    Edge* currEdge = potential_edges.at(i);
    selected -= currEdge->GetExtensionScore();
    if (selected < 0) {
      return currEdge;
    }
  }
  return potential_edges.back();
}
