cmake_minimum_required(VERSION 3.13)
project(bioinformatics)

set(CMAKE_CXX_STANDARD 14)

add_executable(bioinformatics src/main.cpp src/file_structures/fasta_entry.cpp src/file_structures/fasta_entry.h src/file_structures/paf_entry.cpp src/file_structures/paf_entry.h src/graph_structures/edge.cpp src/graph_structures/edge.h src/graph_structures/sequence_node.cpp src/graph_structures/sequence_node.h src/utils/project_utils.h src/utils/project_utils.cpp src/utils/file_utils.cpp src/utils/file_utils.h src/graph_structures/path.cpp src/graph_structures/path.h src/graph_structures/group.cpp src/graph_structures/group.h src/graph_structures/path_selection/node_selection.cpp src/graph_structures/path_selection/node_selection.h src/graph_structures/path_selection/overlap_selection.cpp src/graph_structures/path_selection/overlap_selection.h src/graph_structures/path_selection/extension_selection.cpp src/graph_structures/path_selection/extension_selection.h src/graph_structures/path_selection/monte_carlo_selection.cpp src/graph_structures/path_selection/monte_carlo_selection.h src/hera/hera.cpp src/hera/hera.h)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})