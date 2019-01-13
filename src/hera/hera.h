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

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "file_structures/paf_entry.h"
#include "graph_structures/sequence_node.h"
#include "graph_structures/path.h"
#include "graph_structures/group.h"
#include "graph_structures/path_selection/node_selection.h"
#include "graph_structures/connection_node.h"

#ifndef SRC_HERA_HERA_H_
#define SRC_HERA_HERA_H_
/**
 * Class contain HERA algorithm methods.
 */
class Hera {
 private:
  /**
   * Method maps conting id to conting sequence node.
   */
  std::unordered_map<std::string, SequenceNode> conting_nodes_;
  /**
   * Method maps read id to read sequence node.
   */
  std::unordered_map<std::string, SequenceNode> read_nodes_;
  /**
   * Max conflict index in connection graph resolving.
   */
  double max_conflict_index_;
  /**
   * Max node count in a path.
   */
  int max_node_count_;
  /**
   * Number of monte carlo iterations.
   */
  int n_monte_carlo_;
  /**
   * Method generates path to given path using given starting edge and given
   * node selection instance.
   * @param path path to which to add nodes.
   * @param conting_node starting conting node
   * @param edge starting edge
   * @param selection node selection instance for path expansion
   * @return reference to generated path
   */
  Path *GeneratePath(Path *path,
                     SequenceNode &conting_node,
                     Edge* edge,
                     NodeSelection *selection);
  /**
   * Method obtains seuence node reference given node id.
   * @param node_id node identificator
   * @return sequence node reference
   */
  SequenceNode *GetNode(std::string &node_id);
  /**
   * Method adds edges from given paf entries to overlap graph.
   * @param entries paf entries describing overlaps
   */
  void AddEdges(std::vector<PafEntry> &entries);
  /**
   * Method calcualtes index of group with maximal frequency.
   * @param groups vector of path groups
   * @return index of group with max frequency
   */
  int MaxFrequencyIndex(std::vector<Group *> &groups);
  /**
   * Method generates group representing consensus sequence from given vector
   * containing paths to given target.
   * @param paths paths from which a consensus needs to be calculated
   * @param target_id target node id
   * @return consensus sequence group
   */
  Group *GenerateConsenzusSequence(std::vector<Path *> &paths,
                                   std::string &target_id);
  /**
   * Method generates consenzus sequences for one conting node.
   * @param paths paths from one conting node
   * @return vector containing consensus sequences from origin node
   */
  std::vector<Group *> GenerateConsenzusSequencesForNode(
      std::vector<Path *> &paths);
  /**
   * Method creates connection nodes for connection graph.
   * @param conting_consensus_sequences map that maps conting id to consensus
   *        sequences
   * @return collection of initial connection nodes
   */
  std::vector<ConnectionNode *> CreateConnectionNodes(
      std::unordered_map<std::string,
        std::vector<Group *>> &conting_consensus_sequences);
  /**
   * Method creates conesus sequences for connection graph from path groups.
   * @param groups collection of consensus path groups
   * @param origin origin conting node
   * @return collection of consensus sequences for origin node
   */
  std::vector<ConsensusSequence *> CreateConsensusSequenceFromGroups(
      std::vector<Group *> &groups, SequenceNode *origin);
  /**
   * Method tries to connect given origin node to one of the nodes given in
   * targets.
   * @param origin origin connection node
   * @param targets collection of possible targets
   * @return Connection node to which origin node has been connected or NULL if
   *    connection hasn't been made
   */
  ConnectionNode *ConnectNode(ConnectionNode *origin,
                              std::unordered_set<ConnectionNode *> targets);

 public:
  /**
   * Constructor initializes HERA with conting and read nodes maps.
   * @param conting_nodes map mapping conting nodes id to conting sequence nodes
   * @param read_nodes map mapping read ids to read sequence nodes
   * @param max_conflict_index maximal conflict index in connection graph
   * @param max_node_count maximal node count in path generation
   * @param n_monte_carlo number of monte carlo iterations
   */
  Hera(std::unordered_map<std::string, SequenceNode> &conting_nodes,
       std::unordered_map<std::string, SequenceNode> &read_nodes,
       double max_conflict_index, int max_node_count, int n_monte_carlo
       );
  /**
   * Method construct overlap graph.
   * @param conting_read_paf_entries PAF entries calculated with conting read
   *    overlaps
   * @param read_read_paf_entries PAF entries calculated with read read overlaps
   */
  void ConstructOverlapGraph(std::vector<PafEntry> &conting_read_paf_entries,
                             std::vector<PafEntry> &read_read_paf_entries);
  /**
   * Method generates paths starting with given conting.
   * @param conting_id start conting node id
   * @return generated paths from given node
   */
  std::vector<Path *> GeneratePaths(std::string &conting_id);
  /**
   * Method groups given paths.
   * @param paths collection of paths with given target
   * @param target_id target conting node id
   * @return collection of path groups
   */
  std::vector<Group *> GroupPaths(std::vector<Path *> &paths,
                                  std::string &target_id);
  /**
   * Method generates consesus sequences in overlap graph.
   * @param paths map mapping conting id to collection of paths from conting
   * @return map mapping conting id to collection of consensus groups
   */
  std::unordered_map<std::string,
                     std::vector<Group *>> GenerateConsenzusSequences(
      std::unordered_map<std::string, std::vector<Path *>> &paths);
  /**
   * Getter method for obtaining conting nodes map. Method is used for testing
   * purposes.
   * @return map mapping conting id to conting sequence node
   */
  std::unordered_map<std::string, SequenceNode> GetContingNodesMap();

  /**
   * Method constructs connection graph which is used to obtain HERA scaffolding
   * result.
   * @param conting_consensus_sequences map mapping conting id to collection of
   * consensus groups
   * @return collection of resulting connection nodes
   */
  std::vector<ConnectionNode *> ConstructConnectionGraph(
      std::unordered_map<std::string,
        std::vector<Group *>> &conting_consensus_sequences);
};
#endif  // SRC_HERA_HERA_H_
