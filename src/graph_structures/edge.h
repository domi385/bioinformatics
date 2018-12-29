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
#include "file_structures/paf_entry.h"

#ifndef SRC_GRAPH_STRUCTURES_EDGE_H_
#define SRC_GRAPH_STRUCTURES_EDGE_H_

/**
 * Class describes edge in overlap graph connecting two sequence nodes.
 */
class Edge {
 private:
  /**
   * Edge origin node id.
   */
  std::string id_start_;
  /**
   * Edge target node id.
   */
  std::string id_end_;
  /**
   * Edge overlap score.
   */
  double overlap_score_;
  /**
   * Edge extension score.
   */
  double extension_score_;
  /**
   * Edge sequence identity.
   */
  double sequence_identity_;
  /**
   * Edge overlap length.
   */
  long overlap_length_;
  /**
   * Edge origin overhang length.
   */
  long overhang_origin_;  // oh1
  /**
   * Edge target overhang length.
   */
  long overhang_target_;  // oh2
  /**
   * Edge origin extension length.
   */
  long extension_len_origin_;  // el1
  /**
   * Edge target extension length.
   */
  long extension_len_target_;  // el2
  /**
   * Edge origin overlap length.
   */
  long overlap_len_origin_;  // ol1
  /**
   * Edge target overlap length.
   */
  long overlap_len_target_;  // ol2

 public:
  /**
   * Constructor initializes edge with data from PAF file entry.
   * @param entry PAF file entry
   */
  explicit Edge(PafEntry entry);
  /**
   * Getter method for obtaining sequence start id.
   * @return sequence start id
   */
  std::string GetStartId();
  /**
   * Getter method for obtaining sequence end id.
   * @return sequence end id
   */
  std::string GetIdEnd();
  /**
   * Getter method for obtaining edge overlap score.
   * @return edge overlap score
   */
  double GetOverlapScore();
  /**
   * Getter method for obtaining edge extension score.
   * @return edge extension score
   */
  double GetExtensionScore();
  /**
   * Getter method for obtaining edge sequence identity.
   * @return edge sequence identity
   */
  double GetSequenceIdentity();  // TODO why is sequence identity not used ?
  /**
   * Getter method for obtaining edge overlap length.
   * @return edge overlap length
   */
  long GetOverlapLength();
  /**
   * Getter method for obtaining edge origin overhang length.
   * @return edge origin overhang length
   */
  long GetOverhangOrigin();
  /**
   * Getter method for obtaining edge target overhang length.
   * @return edge target overhang length
   */
  long GetOverhangTarget();
  /**
   * Getter method for obtaining edge origin extension length.
   * @return edge origin extension length
   */
  long GetExtensionLenOrigin();
  /**
   * Getter method for obtaining edge target extension length.
   * @return edge target extension length
   */
  long GetExtensionLenTarget();
  /**
   * Getter method for obtaining edge origin overlap length.
   * @return edge origin overlap length
   */
  long GetOverlapLenOrigin();
  /**
   * Getter method for obtaining edge target overlap length.
   * @return edge target overlap length
   */
  long GetOverlapLenTarget();
};

#endif  // SRC_GRAPH_STRUCTURES_EDGE_H_
