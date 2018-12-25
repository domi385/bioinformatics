#include <string>
#include <vector>
#include <unordered_map>
#include "../file_structures/paf_entry.h"
#include "../graph_structures/sequence_node.h"
#include "../graph_structures/path.h"
#include "../graph_structures/group.h"
#include "../graph_structures/path_selection/node_selection.h"

#ifndef SCAFFOLD_HERA
#define SCAFFOLD_HERA

class Hera {
 private:
  std::unordered_map<std::string, SequenceNode> conting_nodes_;
  std::unordered_map<std::string, SequenceNode> read_nodes_;

  Path *GeneratePath(Path &path, SequenceNode &conting_node, Edge &edge, NodeSelection* selection);
  SequenceNode* GetNode(std::string &node_id);
  void AddEdges(std::vector<PafEntry> &entries);
  int MaxFrequencyIndex(std::vector<Group*> &groups);
  Group* GenerateConsenzusSequence(std::vector<Path*> &paths);
  std::vector<Group*> GenerateConsenzusSequencesForNode(std::vector<Path*> &paths);

 public:
  Hera(std::unordered_map<std::string, SequenceNode> &conting_nodes,
       std::unordered_map<std::string, SequenceNode> &read_nodes);

  void ConstructOverlapGraph(std::vector<PafEntry> &conting_read_paf_entries,
                             std::vector<PafEntry> &read_read_paf_entries);
  std::vector<Path*> GeneratePaths(std::string &conting_id);
  std::vector<Group*> GroupPaths(std::vector<Path*> &paths);
  std::unordered_map<std::string, std::vector<Group*>> GenerateConsenzusSequences(
      std::unordered_map<std::string, std::vector<Path*>> &paths);

  std::unordered_map<std::string, SequenceNode> GetContingNodesMap();
};

#endif //SCAFFOLD_HERA