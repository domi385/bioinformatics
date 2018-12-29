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

#include "utils/file_utils.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "file_structures/fasta_entry.h"
#include "file_structures/paf_entry.h"
#include "graph_structures/edge.h"
#include "graph_structures/sequence_node.h"
#include "graph_structures/connection_node.h"
#include "graph_structures/path.h"
#include "utils/project_utils.h"

namespace file_utils {
std::vector<FastaEntry> LoadFromFasta(std::string &filename,
                                      bool is_conting_file) {
  std::vector<FastaEntry> sequence_nodes;
  std::ifstream fasta_file(filename);

  if (!fasta_file.is_open()) {
    std::cout << "Unable to open file " + filename;
    exit(-1);
  }

  std::string line, node_id, node_value;
  while (std::getline(fasta_file, line)) {
    if (line.empty()) {
      continue;
    }
    if (line.find('>') == 0 || line.find('@') == 0) {
      if (!node_id.empty()) {
        if (node_id.find(' ') != 0) {
          node_id = node_id.substr(0, node_id.find(' '));
        }

        sequence_nodes.push_back(FastaEntry(node_id,
                                            node_value,
                                            is_conting_file));
        node_id.clear();
        node_value.clear();
      }
      node_id = line.substr(1, line.length() - 1);
      continue;
    }
    node_value = line;
  }

  if (!node_id.empty()) {
    if (node_id.find(' ') != 0) {
      node_id = node_id.substr(0, node_id.find(' '));
    }
    sequence_nodes.push_back(FastaEntry(node_id, node_value, is_conting_file));
  }

  return sequence_nodes;
}

std::vector<PafEntry> LoadFromPAF(std::string &file_name) {
  std::vector<PafEntry> sequence_overlaps;
  std::ifstream paf_file(file_name);
  std::string paf_delimiter("\t");
  if (!paf_file.is_open()) {
    std::cout << "Unable to open file " + file_name;
    exit(-1);
  }

  std::string line;
  while (std::getline(paf_file, line)) {
    if (line.empty()) {
      continue;
    }

    std::vector<std::string>
        line_parts = project_utils::SplitString(line, paf_delimiter);
    PafEntry currEntry = PafEntry(line_parts);
    if (FilterPafEntries(currEntry)) {
      continue;
    }
    sequence_overlaps.push_back(currEntry);
  }
  return sequence_overlaps;
}

bool FilterPafEntries(PafEntry &entry) {
  return (entry.GetSequenceIdentity() < 0.5)
      || (entry.GetSequenceIdentity() >= 1);
}

void SaveFastaFile(
    std::string & file_name, std::vector<ConnectionNode *> &connection_graph,
    std::unordered_map<std::string, FastaEntry*> fasta_map) {
  std::ofstream output_file(file_name);
  if (!output_file.is_open()) {
    std::cout << "Unable to open file " + file_name;
    exit(-1);
  }

  for (int i=0, end = connection_graph.size(); i < end; i++) {
    output_file << ">scaffold" << i << std::endl;
    ConnectionNode *curr_conn = connection_graph.at(i);
    std::vector<Path *> paths = curr_conn->GetConnectingPaths();

    if (paths.empty()) {
      // paths is empty when there is only one conting in connection node
      std::vector<SequenceNode*> curr_contings = curr_conn->GetNodes();
      SequenceNode* curr_conting = curr_contings.at(0);
      FastaEntry* origin_entry = fasta_map.at(curr_conting->GetId());
      std::string origin_value = origin_entry->GetValue();
      output_file << origin_value << std::endl;
      continue;
    }

    Path *start_path = paths.at(0);
    std::vector<Edge *> contained_edges = start_path->GetEdges();
    Edge* first_edge = contained_edges.front();
    output_file << EdgeBeginningToString(first_edge, fasta_map);

    Edge * prev_edge = first_edge;
    for (int j = 0, end_j = paths.size(); j < end_j; j++) {
      Path *current_path = paths.at(j);
      std::vector<Edge *> contained_edges = current_path->GetEdges();

      for (int edge = 0, max_edge = contained_edges.size();
          edge < max_edge; edge++) {
        if (j == 0 && edge == 0) {
          continue;
        }
        Edge *current_edge = contained_edges.at(edge);
        std::string edge_string = EdgeToString(
            prev_edge, current_edge, fasta_map);
        output_file << edge_string;
        prev_edge = current_edge;
      }
    }

    std::vector<Edge *> last_edges = paths.at(paths.size() - 1)->GetEdges();
    Edge *last_edge = last_edges.at(last_edges.size() - 1);
    std::string edge_string = EdgeEndToString(last_edge, fasta_map);
    output_file << edge_string;

    output_file << std::endl;
  }
    output_file.close();
}

std::string EdgeToString(
    Edge* prevEdge,
    Edge* edge,
    std::unordered_map<std::string, FastaEntry*> fasta_map) {
  std::string start_id = edge->GetStartId();

  FastaEntry* origin_entry = fasta_map.at(start_id);
  std::string origin_value = origin_entry->GetValue();

  long beginning_index = prevEdge->GetOverhangTarget()
      +prevEdge->GetOverlapLenTarget();
  long end_index = edge->GetExtensionLenOrigin()+edge->GetOverlapLenOrigin();

  if (end_index-beginning_index <0) {
    return "";
  }

  return origin_value.substr(beginning_index, end_index);
}
std::string EdgeBeginningToString(
    Edge* edge,
    std::unordered_map<std::string, FastaEntry*> fasta_map) {
  std::string start_id = edge->GetStartId();

  FastaEntry* origin_entry = fasta_map.at(start_id);
  std::string origin_value = origin_entry->GetValue();

  long index = edge->GetExtensionLenOrigin()+edge->GetOverlapLenOrigin();

  return origin_value.substr(0, index);
}

std::string EdgeEndToString(
    Edge* edge,
    std::unordered_map<std::string, FastaEntry*> fasta_map) {
  std::string end_id = edge->GetIdEnd();

  FastaEntry* target_entry = fasta_map.at(end_id);
  std::string target_value = target_entry->GetValue();

  long index = edge->GetOverhangTarget()+edge->GetOverlapLenTarget();

  return target_value.substr( index, target_value.size());
}
}  // namespace file_utils
