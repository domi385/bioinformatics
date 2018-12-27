//
// Created by dplus on 22.12.2018..
//

#include <string>
#include <vector>
#include <unordered_map>
#include "../graph_structures/sequence_node.h"
#include "../file_structures/fasta_entry.h"

#ifndef SCAFFOLD_PROJECT_UTILS_H
#define SCAFFOLD_PROJECT_UTILS_H

namespace project_utils {

void OutputStringVector(std::vector<std::string> &collection);

std::vector<std::string> SplitString(std::string &s, std::string &delimiter);

std::unordered_map<std::string, SequenceNode> ConvertFastaToNodeMap(std::vector<
    FastaEntry> &entries);
}

#endif //SCAFFOLD_PROJECT_UTILS_H
