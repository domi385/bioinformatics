#include <string>
#include <vector>
#include <map>
#include "paf_entry.h"
#include "sequence_node.h"

#ifndef SCAFFOLD_HERA
#define SCAFFOLD_HERA

class Hera{
private:
    std::vector<PafEntry> paf_entries;
    std::map<std::string, SequenceNode> conting_nodes;
    std::map<std::string, SequenceNode> read_nodes;
    
public:
    void ConstructOverlapGraph();
};

#endif //SCAFFOLD_HERA