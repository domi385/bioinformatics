
#include "hera.h"

void Hera::ConstructOverlapGraph()
{
    for (int i = 0; i < paf_entries.size(); i++)
    {
        Edge edge = Edge(paf_entries[i]);
        SequenceNode * pNode = NULL;
        if (conting_nodes.find(edge.GetIdEnd()) != conting_nodes.end())        {
            pNode = &conting_nodes[edge.GetIdEnd()];
        }else{
            pNode = &read_nodes[edge.GetIdEnd()];
        }

        // jos treba na pNode pozvati funkciju add_edge i dodati edge
    }
}