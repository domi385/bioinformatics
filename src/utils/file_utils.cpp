//
// Created by dplus on 22.12.2018..
//


#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "../file_structures/fasta_entry.h"
#include "../file_structures/paf_entry.h"
#include "file_utils.h"
#include "project_utils.h"


namespace file_utils {

    /**
     * Function loads FASTA file to unordered map that maps fasta enrty id to fasta entry object.
     *
     * @param filename fasta file name
     * @param is_conting_file true if given file contains contings, false otherwise
     *
     * @returns unordered map that maps fasta entry id to fasta entry object
     */
    std::unordered_map<std::string, FastaEntry> loadFromFasta(std::string &filename, bool is_conting_file) {

        std::unordered_map<std::string, FastaEntry> sequence_nodes;
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
                    sequence_nodes.emplace(node_id, FastaEntry(node_id, node_value, is_conting_file));
                    node_id.clear();
                    node_value.clear();
                }
                node_id = line.substr(1, line.length() - 1);
                continue;
            }
            node_value = line;
        }

        if (!node_id.empty()) {
            sequence_nodes.emplace(node_id, FastaEntry(node_id, node_value, is_conting_file));
        }

        return sequence_nodes;
    }


    /**
     * Function loads PAF file to vector of paf entries, it also filters PAF entries using filterPafEntries function.
     *
     * @param file_name paf file name
     *
     * @returns vector of filtered paf entries
     */
    std::vector<PafEntry> loadFromPAF(std::string &file_name) {
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

            std::vector<std::string> line_parts = project_utils::splitString(line, paf_delimiter);
            PafEntry currEntry = PafEntry(line_parts);
            if (filterPafEntries(currEntry)) {
                continue;
            }
            sequence_overlaps.push_back(currEntry);
        }
        return sequence_overlaps;
    }

    /**
     * Function decides should you filter given paf entry.
     * @param entry paf entry for which to decide if it should be filtered
     * @return true if the entry should be filtered
     */
    bool filterPafEntries(PafEntry entry) {
        //TODO add filtering
        return false;
    }

}
