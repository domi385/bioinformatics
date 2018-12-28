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

#include "utils/project_utils.h"

#include <vector>
#include <unordered_map>
#include <iostream>

#include "graph_structures/sequence_node.h"
#include "file_structures/fasta_entry.h"

namespace project_utils {
void OutputStringVector(std::vector<std::string> &collection) {
  for (int i = 0, end = collection.size(); i < end; i++) {
    std::cout << "'" << collection.at(i) << "' ";
  }
  std::cout << std::endl;
}

std::vector<std::string> SplitString(std::string &s, std::string &delimiter) {
  std::vector<std::string> string_parts;
  size_t last_index = 0;
  size_t index = 0;
  while ((index = s.find(delimiter, last_index)) != std::string::npos) {
    std::string curr_part = s.substr(last_index, index - last_index);
    string_parts.push_back(curr_part);
    last_index = index + 1;
  }
  std::string last_part = s.substr(last_index);
  string_parts.push_back(last_part);
  return string_parts;
}

std::unordered_map<std::string, SequenceNode> ConvertFastaToNodeMap(std::vector<
    FastaEntry> &entries) {
  std::unordered_map<std::string, SequenceNode> nodes_map;
  for (int i = 0, end = entries.size(); i < end; i++) {
    FastaEntry curr_entry = entries.at(i);
    std::string entry_id = curr_entry.GetEntryId();
    SequenceNode *curr_node = new SequenceNode(entry_id,
                                               curr_entry.GetLength(),
                                               curr_entry.IsConting());
    nodes_map.emplace(curr_entry.GetEntryId(), *curr_node);
  }
  return nodes_map;
}
}  // namespace project_utils
