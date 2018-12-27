#include <ctime>

#include <iostream>
#include <fstream>

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

#include "file_structures/fasta_entry.h"
#include "file_structures/paf_entry.h"
#include "graph_structures/sequence_node.h"
#include "utils/project_utils.h"
#include "utils/file_utils.h"
#include "hera/hera.h"

int main(int argc, char **argv) {
  clock_t start_t = std::clock();
  int expected_num_arguments = 6;
  if (argc != expected_num_arguments) {
    std::cout << "Invalid number of arguments, expected "
              << expected_num_arguments << ", given " << argc
              << std::endl;
    exit(-1);
  }

  // INIT ARGUMENT VARIABLES
  std::string contigs_fasta_file_name = argv[1];
  std::string reads_fasta_file_name = argv[2];
  std::string conting_read_overlap_file_name = argv[3];
  std::string read_read_overlap_file_name = argv[4];
  std::string output_file_name = argv[5];

  // LOAD CONTING NODES FROM FASTA
  clock_t t = std::clock();
  std::vector<FastaEntry> conting_fasta_entries =
      file_utils::LoadFromFasta(contigs_fasta_file_name, true);
  std::cout << "Number of conting fasta entries: "
            << conting_fasta_entries.size() << std::endl;
  std::unordered_map<std::string, SequenceNode>
      conting_nodes_map =
      project_utils::ConvertFastaToNodeMap(conting_fasta_entries);
  double conting_nodes_loading_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;

  // LOAD READ NODES FROM FASTA
  t = std::clock();
  std::vector<FastaEntry> read_fasta_entries =
      file_utils::LoadFromFasta(reads_fasta_file_name, false);
  std::cout << "Number of read fasta entries: " << read_fasta_entries.size()
            << std::endl;
  std::unordered_map<std::string, SequenceNode>
      read_nodes_map = project_utils::ConvertFastaToNodeMap(read_fasta_entries);
  double read_nodes_loading_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;

  // LOAD READ_CONTING OVERLAP FROM PAF
  t = std::clock();
  std::vector<PafEntry> read_conting_paf_entries =
      file_utils::LoadFromPAF(conting_read_overlap_file_name);
  std::cout << "Number of read conting paf entries: "
            << read_conting_paf_entries.size() << std::endl;
  double read_conting_paf_loading_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;

  // LOAD READ_READ OVERLAP FROM PAF
  t = std::clock();
  std::vector<PafEntry> read_read_paf_entries =
      file_utils::LoadFromPAF(read_read_overlap_file_name);
  std::cout << "Number of read read paf entries: "
            << read_read_paf_entries.size() << std::endl;
  double read_read_paf_loading_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;

  // CONSTRUCT OVERLAP GRAPH
  t = std::clock();
  Hera hera = Hera(conting_nodes_map, read_nodes_map);
  hera.ConstructOverlapGraph(read_conting_paf_entries, read_read_paf_entries);
  double overlap_graph_construction_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;

  // GENERATE PATHS
  t = std::clock();
  std::unordered_map<std::string, std::vector<Path *>> conting_paths_map;
  for (auto iter = conting_nodes_map.begin();
       iter != conting_nodes_map.end(); ++iter) {
    std::string conting_id = iter->first;
    std::vector<Path *> currPaths = hera.GeneratePaths(conting_id);
    conting_paths_map.emplace(conting_id, currPaths);
    std::cout << "\tConting " << conting_id << ", number of paths: "
              << currPaths.size() << std::endl;
  }
  double path_generation_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;


  // GENERATE CONSENSUS SEQUENCES
  std::cout << "Generate consensus sequence" << std::endl;
  t = std::clock();
  std::unordered_map<std::string, std::vector<Group *>>
      conting_consensus_sequences =
      hera.GenerateConsenzusSequences(conting_paths_map);
  double consensus_generation_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;
  std::cout << "Size of conting consensus sequences: "
            << conting_consensus_sequences.size() << std::endl;

  // CONSTRUCT CONNECTION GRAPH
  std::cout <<"Generate connection graph"<<std::endl;
  t = std::clock();
  std::vector<ConnectionNode *> connection_graph =
      hera.ConstructConnectionGraph(conting_consensus_sequences);
  double connection_graph_construction_time = (std::clock() - t)/(double)CLOCKS_PER_SEC;
  std::cout << "Connection graph " << connection_graph.size() << std::endl;

  // SAVE OUTPUT FILE
  file_utils::SaveFastaFile(output_file_name, connection_graph);


  std::cout << "Time for loading anchorn nodes: " << conting_nodes_loading_time
            << " seconds" << std::endl;
  std::cout << "Time for loading read nodes: " << read_nodes_loading_time
            << " seconds" << std::endl;
  std::cout << "Time for loading read conting overlaps: "
            << read_conting_paf_loading_time << " seconds"
            << std::endl;
  std::cout << "Time for loading read read overlaps: "
            << read_read_paf_loading_time << " seconds" << std::endl;
  std::cout << "Time for constructing overlap graph: "
            << overlap_graph_construction_time << " seconds"
            << std::endl;
  std::cout << "Time for generating paths: " << path_generation_time
            << " seconds" << std::endl;
  std::cout << "Time for generating consensus sequences: "
            << consensus_generation_time << " seconds" << std::endl;
  std::cout << "Time for connecting graph construction: "<<connection_graph_construction_time<<" seconds"<<std::endl;
  double program_time = (std::clock()-start_t)/(double) CLOCKS_PER_SEC;
  std::cout << "Time for program run: "<<program_time<<" seconds"<<std::endl;

  return 0;
}
