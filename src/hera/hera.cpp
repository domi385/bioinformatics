
#include <algorithm>
#include "hera.h"
#include "../graph_structures/edge.h"
#include "../graph_structures/sequence_node.h"
#include "../graph_structures/path_selection/extension_selection.h"
#include "../graph_structures/path_selection/overlap_selection.h"

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
  throw "Should never happen! Thrown if a node id is not in conting and read maps.";
}

std::vector<Path> Hera::GeneratePaths(SequenceNode conting_node){
  std::vector<Edge> edges = conting_node.GetEdges();
  std::vector<Path> paths;
  std::vector<NodeSelection> selections;
  selections.push_back(ExtensionSelection());
  selections.push_back(OverlapSelection()); //TODO add monte carlo

  for(int j=0, j_end=selections.size(); j < j_end; j++){
    NodeSelection* selection = &selections[j];

    for(int i=0, end=edges.size(); i < end; i++){    
      Edge edge = edges[i];
      Path p = Path(conting_node);
      Path* p_curr = GeneratePath(p, conting_node, edge, *selection);

      if(p_curr != NULL){
        (*p_curr).Finalize();
        paths.push_back(*p_curr);
      }
    }
  }
  return paths;
}

Path* Hera::GeneratePath(Path &path, SequenceNode &conting_node, Edge &edge, NodeSelection &selection){
  std::unordered_set<std::string> traversed_nodes;
  traversed_nodes.insert(conting_node.GetId());
  int edge_count = 1;

  std::string node_id = edge.GetIdEnd();
  SequenceNode n = GetNode(node_id); 
  path.Add(n, edge);

  while(true){
    std::vector<Edge> edges = n.GetEdges();
    Edge* p_next_edge = selection.SelectEdge(edges, traversed_nodes);
    if(p_next_edge == NULL){
      return NULL; //TODO povratak na prethodni cvor
    }
    Edge next_edge = * p_next_edge;
    edge_count++;
    if(edge_count > 1000){ //TODO definirati konstantu
      return NULL;
    }
    std::string node_id = edge.GetIdEnd();
    n = GetNode(node_id);
    path.Add(n, next_edge);
    traversed_nodes.insert(node_id);
    if(n.IsConting()){
      return &path;
    }
  }
}

Group Hera::GenerateConsenzusSequence(std::vector<Path> paths){
  std::sort(paths.begin(), paths.end());
  std::vector<Group> groups = GroupPaths(paths);

  for(int i=0, end=groups.size(); i < end; i++){
    Group group = groups[i];
    group.FilterGroup();
  }

  if(groups.size() == 1){
    return groups[0];
  }

  if(groups.size() == 2){
    return groups[1];
  }

  int max_index = MaxFrequencyIndex(groups);
  Group selected_group = groups[max_index];
  int max_frequency = selected_group.GetMaxFrequency();

  for(int i=max_index + 1, end=groups.size(); i < end; i++){
    Group current_group = groups[i];
    int curr_frequency = current_group.GetMaxFrequency();
    if(curr_frequency < 0.5 * max_frequency){
      break;
    }
    selected_group = current_group;
    max_frequency = curr_frequency; //TODO provjeriti je li ova linija potrebna
  }

  return selected_group;
}

int Hera::MaxFrequencyIndex(std::vector<Group> groups){
  int max_frequency = groups[0].GetMaxFrequency();
  int max_index = 0;

  for(int i=1, end=groups.size(); i < end; i++){
    int frequency = groups[i].GetMaxFrequency();
    if(frequency > max_frequency){
      max_frequency = frequency;
      max_index = i;
    }
  }
  return max_index;
}


std::vector<Group> Hera::GroupPaths(std::vector<Path> paths){

}