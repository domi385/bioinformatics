// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include <string>
#include <vector>
#include <unordered_map>

#include "graph_structures/sequence_node.h"
#include "file_structures/fasta_entry.h"

#ifndef SRC_UTILS_PROJECT_UTILS_H_
#define SRC_UTILS_PROJECT_UTILS_H_

namespace project_utils {
void OutputStringVector(std::vector<std::string> &collection);

std::vector<std::string> SplitString(std::string &s, std::string &delimiter);

std::unordered_map<std::string, SequenceNode> ConvertFastaToNodeMap(std::vector<
    FastaEntry> &entries);
}  // namespace project_utils

#endif  // SRC_UTILS_PROJECT_UTILS_H_
