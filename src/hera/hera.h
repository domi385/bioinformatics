#include <string>
#include <vector>
#include <unordered_map>
#include "../file_structures/paf_entry.h"
#include "../graph_structures/sequence_node.h"
#include "../graph_structures/path.h"
#include "../graph_structures/path_selection/node_selection.h"

#ifndef SCAFFOLD_HERA
#define SCAFFOLD_HERA

class Hera {
 private:
  std::unordered_map<std::string, SequenceNode> conting_nodes_;
  std::unordered_map<std::string, SequenceNode> read_nodes_;

  Path GeneratePath(Path &path, Edge &edge, NodeSelection &selection);

 public:
  Hera();

  void ConstructOverlapGraph(std::vector<PafEntry> &paf_entries);
  std::vector<Path> GeneratePaths();
};

#endif //SCAFFOLD_HERA