#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "file_structures/fasta_entry.h"
#include "file_structures/paf_entry.h"
#include "utils/file_utils.h"


std::vector<PafEntry> filterPAFOverlaps(std::vector<PafEntry> &paf_entries) {
    std::vector<PafEntry> filtered_entries;
    for (int i = 0, end = paf_entries.size(); i < end; i++) {
        PafEntry curr_entry = paf_entries.at(i);
        long el1 = curr_entry.getQueryStart();
        long ol1 = curr_entry.getQueryEnd() - el1;
        long oh1 = curr_entry.getQueryLen() - curr_entry.getQueryEnd();

        long oh2 = curr_entry.getTargetStart();
        long ol2 = curr_entry.getTargetEnd() - oh2;
        long el2 = curr_entry.getTargetLen() - curr_entry.getTargetEnd();

        double sequence_identity = curr_entry.getNumMatchesWithoutGaps() /
                                   (double) std::min(curr_entry.getQueryLen(), curr_entry.getTargetLen());
        double overlap_score = sequence_identity * (ol1 + ol2) / 2.;
        double mean_overhang = (oh1 + oh2) / 2.;
        double extension_score1 = overlap_score + el1 / 2. - mean_overhang;
        double extension_score2 = overlap_score + el2 / 2. - mean_overhang;

        //std::cout << i << "\t" << sequence_identity << "\t" << overlap_score << "\t" << extension_score1 << "\t"
        //          << extension_score2 << std::endl;


        filtered_entries.push_back(paf_entries.at(i));
    }
    return filtered_entries;
}


int main(int argc, char **argv) {
    int expected_num_arguments = 5;
    if (argc != expected_num_arguments) {
        std::cout << "Invalid number of arguments, expected " << expected_num_arguments << ", given " << argc
                  << std::endl;
        exit(-1);
    }

    std::string contigs_fasta_file_name = argv[1];
    std::string reads_fasta_file_name = argv[2];
    std::string conting_read_overlap_file_name = argv[3];
    std::string read_read_overlap_file_name = argv[4];

    clock_t t = std::clock();
    std::vector<FastaEntry> anchorn_nodes = file_utils::loadFromFasta(contigs_fasta_file_name, true);
    std::cout << "Number of anchorn nodes: " << anchorn_nodes.size() << std::endl;
    clock_t anchorn_nodes_loading_time = std::clock() - t;

    t = std::clock();
    std::vector<FastaEntry> read_nodes = file_utils::loadFromFasta(reads_fasta_file_name, false);
    std::cout << "Number of read nodes: " << read_nodes.size() << std::endl;
    clock_t read_nodes_loading_time = std::clock() - t;

    t = std::clock();
    std::vector<PafEntry> read_conting_paf_entries = file_utils::loadFromPAF(conting_read_overlap_file_name);
    std::cout << "Number of read conting paf entries: " << read_conting_paf_entries.size() << std::endl;
    clock_t read_conting_paf_loading_time = std::clock() - t;

    t = std::clock();
    std::vector<PafEntry> read_read_paf_entries = file_utils::loadFromPAF(read_read_overlap_file_name);
    //std::cout << "Number of read read paf entries: " << read_read_paf_entries.size() << std::endl;
    clock_t read_read_paf_loading_time = std::clock() - t;

    std::vector<PafEntry> filtered_read_conting_paf_entries = filterPAFOverlaps(read_conting_paf_entries);

    std::cout << "Time for loading anchorn nodes: " << anchorn_nodes_loading_time << " miliseconds" << std::endl;
    std::cout << "Time for loading read nodes: " << read_nodes_loading_time << " miliseconds" << std::endl;
    std::cout << "Time for loading read conting overlaps: " << read_conting_paf_loading_time << " miliseconds"
              << std::endl;
    std::cout << "Time for loading read read overlaps: " << read_read_paf_loading_time << " miliseconds" << std::endl;

    return 0;
}