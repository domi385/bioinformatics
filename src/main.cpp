#include <ctime>

#include <iostream>
#include <fstream>

#include <vector>
#include <algorithm>
#include <unordered_map>

#include "file_structures/fasta_entry.h"
#include "file_structures/paf_entry.h"
#include "graph_structures/sequence_node.h"
#include "utils/file_utils.h"
#include "utils/project_utils.h"
#include "hera/hera.h"

int main(int argc, char **argv) {
  int expected_num_arguments = 5;
  if (argc != expected_num_arguments) {
    std::cout << "Invalid number of arguments, expected " << expected_num_arguments << ", given " << argc
              << std::endl;
    exit(-1);
  }

  //INIT ARGUMENT VARIABLES
  std::string contigs_fasta_file_name = argv[1];
  std::string reads_fasta_file_name = argv[2];
  std::string conting_read_overlap_file_name = argv[3];
  std::string read_read_overlap_file_name = argv[4];

  //LOAD CONTING NODES FROM FASTA
  clock_t t = std::clock();
  std::vector<FastaEntry> conting_fasta_entries = file_utils::loadFromFasta(contigs_fasta_file_name, true);
  std::cout << "Number of conting fasta entries: " << conting_fasta_entries.size() << std::endl;
  std::unordered_map<std::string, SequenceNode>
      conting_nodes_map = project_utils::ConvertFastaToNodeMap(conting_fasta_entries);
  clock_t conting_nodes_loading_time = std::clock() - t;

  //LOAD READ NODES FROM FASTA
  t = std::clock();
  std::vector<FastaEntry> read_fasta_entries = file_utils::loadFromFasta(reads_fasta_file_name, false);
  std::cout << "Number of read fasta entries: " << read_fasta_entries.size() << std::endl;
  std::unordered_map<std::string, SequenceNode>
      read_nodes_map = project_utils::ConvertFastaToNodeMap(read_fasta_entries);
  clock_t read_nodes_loading_time = std::clock() - t;

  //LOAD READ_CONTING OVERLAP FROM PAF
  t = std::clock();
  std::vector<PafEntry> read_conting_paf_entries = file_utils::loadFromPAF(conting_read_overlap_file_name);
  std::cout << "Number of read conting paf entries: " << read_conting_paf_entries.size() << std::endl;
  clock_t read_conting_paf_loading_time = std::clock() - t;

  //LOAD READ_READ OVERLAP FROM PAF
  t = std::clock();
  std::vector<PafEntry> read_read_paf_entries = file_utils::loadFromPAF(read_read_overlap_file_name);
  std::cout << "Number of read read paf entries: " << read_read_paf_entries.size() << std::endl;
  clock_t read_read_paf_loading_time = std::clock() - t;

  //CONSTRUCT OVERLAP GRAPH
  t = std::clock();
  Hera hera = Hera(conting_nodes_map, read_nodes_map);
  hera.ConstructOverlapGraph(read_conting_paf_entries, read_read_paf_entries);
  clock_t overlap_graph_construction_time = std::clock() - t;

  //GENERATE PATHS

  std::cout << "Time for loading anchorn nodes: " << conting_nodes_loading_time << " miliseconds" << std::endl;
  std::cout << "Time for loading read nodes: " << read_nodes_loading_time << " miliseconds" << std::endl;
  std::cout << "Time for loading read conting overlaps: " << read_conting_paf_loading_time << " miliseconds"
            << std::endl;
  std::cout << "Time for loading read read overlaps: " << read_read_paf_loading_time << " miliseconds" << std::endl;
  std::cout << "Time for constructing overlap graph: " << overlap_graph_construction_time << " miliseconds"
            << std::endl;

  return 0;
}