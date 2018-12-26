//
// Created by dplus on 22.12.2018..
//


#include <vector>
#include <unordered_map>

#include <iostream>
#include "../graph_structures/sequence_node.h"
#include "../file_structures/fasta_entry.h"

#include "project_utils.h"

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

std::unordered_map<std::string, SequenceNode> ConvertFastaToNodeMap(std::vector<FastaEntry> &entries) {
  std::unordered_map<std::string, SequenceNode> nodes_map;
  for (int i = 0, end = entries.size(); i < end; i++) {
    FastaEntry curr_entry = entries.at(i);
    std::string entry_id = curr_entry.GetEntryId();
    SequenceNode *curr_node = new SequenceNode(entry_id, curr_entry.GetLength(), curr_entry.IsConting());
    nodes_map.emplace(curr_entry.GetEntryId(), *curr_node);
  }
  return nodes_map;
}

}