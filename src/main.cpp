#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "file_structures/fasta_entry.h"
#include "file_structures/paf_entry.h"
#include "utils/file_utils.h"


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