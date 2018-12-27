//
// Created by dplus on 22.12.2018..
//


#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "../file_structures/fasta_entry.h"
#include "../file_structures/paf_entry.h"
#include "project_utils.h"
#include "file_utils.h"
#include "../graph_structures/sequence_node.h"
#include "../graph_structures/connection_node.h"
#include "../graph_structures/path.h"

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
    if (line.rfind('>') == 0) {
      if (!node_id.empty()) {
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

void SaveFastaFile(std::string & file_name, std::vector<ConnectionNode *> &connection_graph){

  std::ofstream output_file(file_name);
  if (!output_file.is_open()){
    std::cout << "Unable to open file " + file_name;
    exit(-1);
  }

  for (int i=0, end = connection_graph.size(); i<end; i++) {
    output_file << ">scaffold" << i << std::endl;
    ConnectionNode *curr_conn = connection_graph.at(i);
    std::vector<Path *> paths = curr_conn->GetConnectingPaths();

    for(int j=0, end_j = paths.size(); j < end_j; j++){
      Path *current_path = paths.at(j);
      std::vector<SequenceNode *> contained_nodes = current_path->GetNodes();
      for(int node=0, max_node = contained_nodes.size(); node < max_node; node++){
        SequenceNode *current_node = contained_nodes.at(node);
        output_file<<current_node->GetId()<<" ";
      }
    }
    output_file<<std::endl;
  }
    output_file.close();
}

}
