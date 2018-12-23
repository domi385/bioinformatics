#include "hera.h"
#include "../graph_structures/edge.h"
#include "../graph_structures/sequence_node.h"

void Hera::ConstructOverlapGraph(std::vector<PafEntry>& paf_entries)
{
    for (int i = 0, end = paf_entries.size(); i < end; i++)
    {
        Edge edge = Edge(paf_entries[i]);
        SequenceNode * pNode = NULL;
        if (conting_nodes_.find(edge.GetIdEnd()) != conting_nodes_.end())        {
            pNode = &conting_nodes_[edge.GetIdEnd()];
        }else{
            pNode = &read_nodes_[edge.GetIdEnd()];
        }

        // jos treba na pNode pozvati funkciju add_edge i dodati edge
    }
}

Path Hera::GeneratePath(Path& path, Edge& edge, NodeSelection& selection){
    //TODO
}