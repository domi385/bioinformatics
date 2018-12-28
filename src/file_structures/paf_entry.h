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

#ifndef SRC_FILE_STRUCTURES_PAF_ENTRY_H_
#define SRC_FILE_STRUCTURES_PAF_ENTRY_H_

class PafEntry {
 private:
  // FILE ATTRIBUTES
  /**
   * Origin_id entry from PAF format.
   */
  std::string origin_id_;
  /**
   * Origin_length entry from PAF format.
   */
  long origin_length_;
  /**
   * Same_strand entry from PAF format.
   */
  bool same_strand_;
  /**
   * Target_id entry from PAF format.
   */
  std::string target_id_;
  /**
   * Target_length entry from PAF format.
   */
  long target_length_;
  /**
   * Num_matches entry from PAF format
   * Number of matching bases in the mapping.
   */
  long num_matches_;
  /**
   * Num_bases entry from PAF format.
   * Number of bases, including gaps in the mapping.
   */
  long num_bases_;
  /**
   * Mapping quality from PAF format. (0-255, 255 missing)
   */
  int map_quality_;
  /**
   * SAM formated data from PAF format.
   */
  std::string sam_data_; //TODO remove variable

  // OVERLAP ATTRIBUTES
  /**
   * First sequence extension length.
   */
  long el_1_;
  /**
   * Fist sequence overlap length.
   */
  long ol_1_;
  /**
   * First sequence overhang length.
   */
  long oh_1_;
  /**
   * Second sequence overhang length.
   */
  long oh_2_;
  /**
   * Second sequence overlap length.
   */
  long ol_2_;
  /**
   * Second sequence extension length.
   */
  long el_2_;
  /**
   * Variable for storing sequences order.
   * True if the original PAF order is conserved, false otherwise.
   */
  bool order_;

  // OVERLAP SCORES
  /**
   * Sequence identity score.
   */
  double sequence_identity_;
  /**
   * Overlap score between origin and target.
   */
  double overlap_score_;
  /**
   * Extension score between origin and target.
   */
  double extension_score_;

  // INITIALIZATION METHODS
  //TODO continue doc
  /**
   * Method determines order between two sequences in PAF format.
   * @param id1
   * @param id2
   * @param len1
   * @param len2
   * @param s1
   * @param e1
   * @param s2
   * @param e2
   * @return
   */
  bool DetermineOrder(std::string &id1,
                      std::string &id2,
                      long len1,
                      long len2,
                      long s1,
                      long e1,
                      long s2,
                      long e2);

  void Store(std::string &id1,
             std::string &id2,
             long len1,
             long len2,
             long el1,
             long ol1,
             long oh1,
             long oh2,
             long ol2,
             long el2);
  /**
   * Method calculate scores between two sequences: overlap_score, extension_score and sequence_identity.
   */
  void CalculateScores();

 public:
  // CONSTRUCTORS
  explicit PafEntry(std::vector<std::string> &paf_parts);

  // GETTERS
  std::string GetTargetId();
  double GetOverlapScore();
  double GetExtensionScore();
  double GetSequenceIdentity();

  long GetOverlapLength();
  long GetOverhangLenOrigin();
  long GetOverhangLenTarget();
  long GetExtensionLenOrigin();
  long GetExtensionLenTarget();
  long GetOverlapLenOrigin();
  long GetOverlapLenTarget();
  std::string GetOriginId();
};

#endif  // SRC_FILE_STRUCTURES_PAF_ENTRY_H_
