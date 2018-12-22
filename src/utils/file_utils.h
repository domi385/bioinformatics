//
// Created by dplus on 22.12.2018..
//

#include <vector>
#include <unordered_map>
#include <string>
#include "../file_structures/fasta_entry.h"
#include "../file_structures/paf_entry.h"

#ifndef SCAFFOLD_FILE_UTILS_H
#define SCAFFOLD_FILE_UTILS_H


namespace file_utils {

    std::unordered_map<std::string, FastaEntry> loadFromFasta(std::string &filename, bool is_conting_file) ;

    std::vector<PafEntry> loadFromPAF(std::string &file_name);

    bool filterPafEntries(PafEntry entry);
};


#endif //SCAFFOLD_FILE_UTILS_H
