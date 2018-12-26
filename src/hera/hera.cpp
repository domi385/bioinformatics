#include <iostream>
#include <algorithm>
#include "hera.h"
#include "../graph_structures/path_selection/extension_selection.h"
#include "../graph_structures/path_selection/overlap_selection.h"

Hera::Hera(std::unordered_map<std::string, SequenceNode> &conting_nodes,
           std::unordered_map<std::string, SequenceNode> &read_nodes) {
  conting_nodes_ = conting_nodes;
  read_nodes_ = read_nodes;
}

void Hera::ConstructOverlapGraph(std::vector<PafEntry> &conting_read_paf_entries,
                                 std::vector<PafEntry> &read_read_paf_entries) {
  AddEdges(conting_read_paf_entries);
  AddEdges(read_read_paf_entries);

}
void Hera::AddEdges(std::vector<PafEntry> &entries) {
  for (int i = 0, end = entries.size(); i < end; i++) {
    Edge *edge = new Edge(entries.at(i));
    std::string curr_start_id = edge->GetStartId();
    SequenceNode *p_node = GetNode(curr_start_id);
    p_node->AddEdge(*edge);
  }
}

SequenceNode *Hera::GetNode(std::string &node_id) {
  if (conting_nodes_.find(node_id) != conting_nodes_.end()) {
    return &conting_nodes_.find(node_id)->second;
  }
  if (read_nodes_.find(node_id) != read_nodes_.end()) {
    return &read_nodes_.find(node_id)->second;
  }
  throw "Should never happen! Thrown if a node id is not in conting and read maps.";
}

std::vector<Path *> Hera::GeneratePaths(std::string &conting_id) {
  SequenceNode *conting_node = GetNode(conting_id);
  std::vector<Edge> edges = conting_node->GetEdges();
  std::vector<Path *> paths;
  std::vector<NodeSelection *> selections;
  selections.push_back(new ExtensionSelection());
  selections.push_back(new OverlapSelection()); //TODO add monte carlo

  for (int j = 0, j_end = selections.size(); j < j_end; j++) {
    NodeSelection *selection = selections[j];

    for (int i = 0, end = edges.size(); i < end; i++) {
      Edge edge = edges[i];
      Path *p = new Path(*conting_node);
      Path *p_curr = GeneratePath(*p, *conting_node, edge, selection);

      if (p_curr != NULL) {
        p_curr->Finalize();
        paths.push_back(p_curr);
      } else {
        delete p;
        delete p_curr;
      }
    }
  }
  selections.clear();
  return paths;
}

Path *Hera::GeneratePath(Path &path, SequenceNode &conting_node, Edge &edge, NodeSelection *selection) {
  std::unordered_set<std::string> traversed_nodes;
  traversed_nodes.insert(conting_node.GetId());
  int edge_count = 1;
  Edge prev_edge = edge;

  std::string node_id = prev_edge.GetIdEnd();
  SequenceNode *n = GetNode(node_id);
  path.Add(*n, prev_edge);

  while (true) {
    std::vector<Edge> edges = n->GetEdges();
    //std::cout<<"Edges size " <<conting_node.GetId()<<" "<< edges.size() <<std::endl;
    Edge *p_next_edge = selection->SelectEdge(edges, traversed_nodes);
    if (p_next_edge == NULL) {
      if (traversed_nodes.size() != -1) {
        //std::cout << traversed_nodes.size() << std::endl;
      }
      //std::cout << "exit because dead end";
      return NULL; //TODO povratak na prethodni cvor
    }
    Edge next_edge = *p_next_edge;
    edge_count++;
    if (edge_count > 2000) { //TODO definirati konstantu
      // std::cout << "exit because length"<<std::endl;
      return NULL;
    }
    node_id = prev_edge.GetIdEnd();
    n = GetNode(node_id); //TODO
    path.Add(*n, next_edge);
    traversed_nodes.insert(node_id);
    if (n->IsConting()) {
      //  std::cout << "exit because conting"<<std::endl;
      return &path;
    }
    prev_edge = next_edge;
  }
}

bool comparePaths(Path *a, Path *b) { return (*a < *b); }

Group *Hera::GenerateConsenzusSequence(std::vector<Path *> &paths) {
  std::sort(paths.begin(), paths.end(), comparePaths);
  std::vector<Group *> groups = GroupPaths(paths);

  for (int i = 0, end = groups.size(); i < end; i++) {
    Group *group = groups.at(i);
    group->FilterGroup();
  }

  if (groups.size() == 1) {
    return groups.at(0);
  }

  if (groups.size() == 2) {
    return groups.at(1);
  }

  int max_index = MaxFrequencyIndex(groups);
  Group *selected_group = groups.at(max_index);
  int max_frequency = selected_group->GetMaxFrequency();

  for (int i = max_index + 1, end = groups.size(); i < end; i++) {
    Group *current_group = groups.at(i);
    int curr_frequency = current_group->GetMaxFrequency();
    if (curr_frequency < 0.5 * max_frequency) {
      break;
    }
    selected_group = current_group;
    max_frequency = curr_frequency; //TODO provjeriti je li ova linija potrebna
  }

  return selected_group;
}

int Hera::MaxFrequencyIndex(std::vector<Group *> &groups) {
  int max_frequency = groups.at(0)->GetMaxFrequency();
  int max_index = 0;

  for (int i = 1, end = groups.size(); i < end; i++) {
    int frequency = groups.at(i)->GetMaxFrequency();
    if (frequency > max_frequency) {
      max_frequency = frequency;
      max_index = i;
    }
  }
  return max_index;
}

std::vector<Group *> Hera::GenerateConsenzusSequencesForNode(std::vector<Path *> &paths) {
  std::vector<Group *> consensusGroups;
  std::unordered_map<std::string, std::vector<Path *>> target_paths_map;

  //GROUP PATHS BY TARGET
  for (int i = 0, end = paths.size(); i < end; i++) {
    Path *curr_path = paths.at(i);
    std::string target_id = curr_path->GetEndId();
    target_paths_map[target_id].push_back(curr_path);
  }

  //GENERATE CONSENSUS SEQUENCES
  for (auto iter = target_paths_map.begin();
       iter != target_paths_map.end(); ++iter) {
    std::vector<Path *> target_paths = iter->second;
    consensusGroups.push_back(GenerateConsenzusSequence(target_paths));
  }

  return consensusGroups;

}

std::unordered_map<std::string, std::vector<Group *>> Hera::GenerateConsenzusSequences(
    std::unordered_map<std::string, std::vector<Path *>> &paths) {

  std::unordered_map<std::string, std::vector<Group *>> consensus_sequences;
  for (auto iter = paths.begin(); iter != paths.end(); ++iter) {
    std::string origin_id = iter->first;
    consensus_sequences.emplace(origin_id, GenerateConsenzusSequencesForNode(iter->second));
  }

  return consensus_sequences;
}

std::vector<Group *> Hera::GroupPaths(std::vector<Path *> &paths) {
  long max_len = paths.back()->GetLength();
  long min_len = paths.front()->GetLength();

  std::vector<Group *> path_groups;

  if (max_len - min_len < 10000) {
    Group *curr_group = new Group(paths);
    path_groups.push_back(curr_group);
    return path_groups;
  }

  std::vector<Path *> curr_paths;
  long curr_stat_len = min_len;
  for (int i = 0, end = paths.size(); i < end; i++) {
    Path *curr_path = paths.at(i);
    if (curr_path->GetLength() <= curr_stat_len + 1000) {
      curr_paths.push_back(curr_path);
    } else {
      path_groups.push_back(new Group(curr_paths));
      curr_paths = std::vector<Path *>();
      curr_paths.push_back(curr_path);
      curr_stat_len = curr_path->GetLength();
    }
  }
  path_groups.push_back(new Group(curr_paths));

  //TODO join widnow groups

  return path_groups;
}
std::unordered_map<std::string, SequenceNode> Hera::GetContingNodesMap() {
  return conting_nodes_;
}
