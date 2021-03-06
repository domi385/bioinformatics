/* Copyright 2018 Dunja Vesinger, Domagoj Pluščec
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "hera/hera.h"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>

#include "graph_structures/path_selection/extension_selection.h"
#include "graph_structures/path_selection/overlap_selection.h"
#include "graph_structures/path_selection/monte_carlo_selection.h"

Hera::Hera(std::unordered_map<std::string, SequenceNode> &conting_nodes,
           std::unordered_map<std::string, SequenceNode> &read_nodes,
           double max_conflict_index, int max_node_count, int n_monte_carlo) {
  conting_nodes_ = conting_nodes;
  read_nodes_ = read_nodes;
  max_conflict_index_ = max_conflict_index;
  max_node_count_ = max_node_count;
  n_monte_carlo_ = n_monte_carlo;
}

void Hera::ConstructOverlapGraph(
      std::vector<PafEntry> &conting_read_paf_entries,
      std::vector<PafEntry> &read_read_paf_entries) {
  AddEdges(conting_read_paf_entries);
  AddEdges(read_read_paf_entries);
}

void Hera::AddEdges(std::vector<PafEntry> &entries) {
  for (int i = 0, end = entries.size(); i < end; i++) {
    Edge *edge = new Edge(entries.at(i));
    std::string curr_start_id = edge->GetStartId();
    SequenceNode *p_node = GetNode(curr_start_id);
    p_node->AddEdge(edge);
  }
}

SequenceNode *Hera::GetNode(std::string &node_id) {
  if (conting_nodes_.find(node_id) != conting_nodes_.end()) {
    return &conting_nodes_.find(node_id)->second;
  }
  if (read_nodes_.find(node_id) != read_nodes_.end()) {
    return &read_nodes_.find(node_id)->second;
  }
  throw "Should never happen! Thrown if a node "
        "id is not in conting and read maps.";
}

std::vector<Path *> Hera::GeneratePaths(std::string &conting_id) {
  SequenceNode *conting_node = GetNode(conting_id);
  std::vector<Edge*> edges = conting_node->GetEdges();
  std::vector<Path *> paths;

  std::vector<NodeSelection *> selections;
  selections.push_back(new ExtensionSelection());
  selections.push_back(new OverlapSelection());
  int monte_carlo_repetition = n_monte_carlo_;
  for (int i = 0; i < monte_carlo_repetition; i++) {
    selections.push_back(new MonteCarloSelection());
  }


  for (int j = 0, j_end = selections.size(); j < j_end; j++) {
    NodeSelection *selection = selections[j];

    for (int i = 0, end = edges.size(); i < end; i++) {
      Edge* edge = edges[i];
      Path *p = new Path(conting_node);
      Path *p_curr = GeneratePath(p, *conting_node, edge, selection);

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

Path *Hera::GeneratePath(Path* path,
                         SequenceNode &conting_node,
                         Edge* edge,
                         NodeSelection *selection) {
  std::unordered_set<std::string> traversed_nodes;
  traversed_nodes.insert(conting_node.GetId());
  int edge_count = 1;
  Edge* prev_edge = edge;

  std::string node_id = prev_edge->GetIdEnd();
  SequenceNode *node = GetNode(node_id);
  path->Add(node, prev_edge);

  while (true) {
    std::vector<Edge*> edges = node->GetEdges();
    Edge *next_edge = selection->SelectEdge(edges, traversed_nodes);
    if (next_edge == NULL) {
      return NULL;
    }

    edge_count++;
    if (edge_count > max_node_count_) {
      return NULL;
    }
    node_id = next_edge->GetIdEnd();
    node = GetNode(node_id);
    path->Add(node, next_edge);
    traversed_nodes.insert(node_id);
    if (node->IsConting()) {
      if (node->GetId() == conting_node.GetId()) {
        return NULL;
      }
      return path;
    }
    // prev_edge = next_edge;
  }
}

bool comparePaths(Path *a, Path *b) { return (*a < *b); }

Group *Hera::GenerateConsenzusSequence(std::vector<Path *> &paths,
                                       std::string &target_id) {
  std::sort(paths.begin(), paths.end(), comparePaths);
  std::vector<Group *> groups = GroupPaths(paths, target_id);

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
    max_frequency = curr_frequency;
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

std::vector<Group *> Hera::GenerateConsenzusSequencesForNode(
      std::vector<Path *> &paths) {
  std::vector<Group *> consensusGroups;
  std::unordered_map<std::string, std::vector<Path *>> target_paths_map;

  // GROUP PATHS BY TARGET
  for (int i = 0, end = paths.size(); i < end; i++) {
    Path *curr_path = paths.at(i);
    std::string target_id = curr_path->GetEndId();
    target_paths_map[target_id].push_back(curr_path);
  }

  // GENERATE CONSENSUS SEQUENCES
  for (auto iter = target_paths_map.begin();
       iter != target_paths_map.end(); ++iter) {
    std::vector<Path *> target_paths = iter->second;
    std::string target_id = iter->first;
    consensusGroups.push_back(GenerateConsenzusSequence(target_paths,
                                                        target_id));
  }

  return consensusGroups;
}

std::unordered_map<std::string,
                   std::vector<Group *>> Hera::GenerateConsenzusSequences(
    std::unordered_map<std::string, std::vector<Path *>> &paths) {
  std::unordered_map<std::string, std::vector<Group *>> consensus_sequences;
  for (auto iter = paths.begin(); iter != paths.end(); ++iter) {
    std::string origin_id = iter->first;
    consensus_sequences.emplace(
        origin_id,
        GenerateConsenzusSequencesForNode(iter->second));
  }

  return consensus_sequences;
}

std::vector<Group *> Hera::GroupPaths(std::vector<Path *> &paths,
                                      std::string &target_id) {
  long max_len = paths.back()->GetLength();
  long min_len = paths.front()->GetLength();

  std::vector<Group *> path_groups;

  if (max_len - min_len < 10000) {
    Group *curr_group = new Group(paths, target_id);
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
      path_groups.push_back(new Group(curr_paths, target_id));
      curr_paths = std::vector<Path *>();
      curr_paths.push_back(curr_path);
      curr_stat_len = curr_path->GetLength();
    }
  }
  path_groups.push_back(new Group(curr_paths, target_id));

  return path_groups;
}

std::unordered_map<std::string, SequenceNode> Hera::GetContingNodesMap() {
  return conting_nodes_;
}

std::vector<ConsensusSequence *> Hera::CreateConsensusSequenceFromGroups(
      std::vector<
    Group *> &groups,
      SequenceNode *origin) {
  std::vector<ConsensusSequence *> consensus_sequences;
  for (int i = 0, end = groups.size(); i < end; i++) {
    std::string target_id = groups.at(i)->GetTargetId();
    SequenceNode *target_node = GetNode(target_id);
    ConsensusSequence *new_sequence =
        new ConsensusSequence(groups.at(i), origin, target_node);
    consensus_sequences.push_back(new_sequence);
  }
  return consensus_sequences;
}

std::vector<ConnectionNode *> Hera::CreateConnectionNodes(
      std::unordered_map<std::string,
        std::vector<Group *>> &conting_consensus_sequences) {
  std::vector<ConnectionNode *> connection_nodes;

  for (auto it = conting_consensus_sequences.begin();
       it != conting_consensus_sequences.end(); ++it) {
    std::string origin_id = it->first;
    SequenceNode *origin_node = GetNode(origin_id);
    std::vector<Group *> currGroup = it->second;

    std::vector<ConsensusSequence *> consensus_sequences =
        CreateConsensusSequenceFromGroups(currGroup, origin_node);

    ConnectionNode
        *curr_node = new ConnectionNode(origin_node, consensus_sequences);
    connection_nodes.push_back(curr_node);
  }
  return connection_nodes;
}

std::vector<ConnectionNode *> Hera::ConstructConnectionGraph(
      std::unordered_map<
        std::string,
        std::vector<Group *>> &conting_consensus_sequences) {
  std::vector<ConnectionNode *>
      origins = CreateConnectionNodes(conting_consensus_sequences);
  std::unordered_set<ConnectionNode *> targets;

  for (int i = 0, end = origins.size(); i < end; i++) {
    targets.emplace(origins.at(i));
  }

  bool connection_made = true;

  while (connection_made) {
    std::unordered_set<ConnectionNode *> removed_nodes;

    connection_made = false;
    for (int i = 0, end = origins.size(); i < end; i++) {
      ConnectionNode *curr_node = origins.at(i);
      if (removed_nodes.find(curr_node) != removed_nodes.end()){
        continue;
      }
      double conflict_index = curr_node->GetConflictIndex();
      if (conflict_index > max_conflict_index_) {
        continue;
      }

      ConnectionNode *target = ConnectNode(curr_node, targets);
      if (target != NULL) {
        connection_made = true;
        targets.erase(target);
        removed_nodes.emplace(target);
      }
    }

    std::vector<ConnectionNode *> new_origins;
    for (int i = 0, end = origins.size(); i < end; i++) {
      if (removed_nodes.find(origins.at(i)) == removed_nodes.end()) {
        new_origins.push_back(origins.at(i));
      }
    }
    origins.clear();
    origins = new_origins;

    if (connection_made) {
      for (int i = 0, end = origins.size(); i < end; i++) {
        origins.at(i)->RecalculateConflictIndex(targets);
      }
    }
  }
  return origins;
}

ConnectionNode *Hera::ConnectNode(
      ConnectionNode *origin,
      std::unordered_set<ConnectionNode *> targets) {
  std::tuple<SequenceNode *, Path *> desired_target_info = origin->GetTarget();
  SequenceNode *desired_target = std::get < 0 > (desired_target_info);
  Path *path_to_desired_target = std::get < 1 > (desired_target_info);

  std::unordered_set<SequenceNode *> target_nodes;
  for (auto it = targets.begin(); it != targets.end(); ++it) {
    ConnectionNode *curr_target_node = *it;
    SequenceNode *available_target = curr_target_node->GetOriginNode();
    if (available_target == desired_target) {
      origin->ConnectNodes(curr_target_node, path_to_desired_target);
      return curr_target_node;
    }
  }
  return NULL;
}
