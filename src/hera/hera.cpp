#include "hera.h"
#include "../graph_structures/edge.h"
#include "../graph_structures/sequence_node.h"

Hera::Hera(std::unordered_map<std::string, SequenceNode> conting_nodes, std::unordered_map<std::string, SequenceNode> read_nodes){
  conting_nodes_=conting_nodes;
  read_nodes_=read_nodes;
}

void Hera::ConstructOverlapGraph(std::vector<PafEntry> &conting_read_paf_entries, std::vector<PafEntry> &read_read_paf_entries) {
  AddEdges(conting_read_paf_entries);
  AddEdges(read_read_paf_entries);

}
void Hera::AddEdges(std::vector<PafEntry>& entries){
  for (int i = 0, end = entries.size(); i < end; i++) {
    Edge edge = Edge(entries.at(i));
    std::string curr_end_id = edge.GetIdEnd();
    SequenceNode p_node = GetNode(curr_end_id);
    p_node.AddEdge(edge);
  }
}

SequenceNode Hera::GetNode(std::string& node_id){
  if (conting_nodes_.find(node_id)!=conting_nodes_.end()){
    return conting_nodes_.at(node_id);
  }
  if (read_nodes_.find(node_id) != read_nodes_.end()){
    return read_nodes_.at(node_id);
  }
  throw "Shouldn't never happen! Thrown if a node id is not in conting and read maps";
}

