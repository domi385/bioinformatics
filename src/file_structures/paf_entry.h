/* Copyright 2018 Dunja Vesinger, Domagoj Pluščec
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
  std::string origin_id_;
  long origin_length_;
  bool same_strand_;
  std::string target_id_;
  long target_length_;
  long num_matches_;
  long num_bases_;
  int map_quality_;
  std::string sam_data_;

  // OVERLAP ATTRIBUTES
  long el_1_;
  long ol_1_;
  long oh_1_;
  long oh_2_;
  long ol_2_;
  long el_2_;
  bool order_;  // true if the original order is satisfied, false otherwise

  // OVERLAP SCORES
  double sequence_identity_;
  double overlap_score_;
  double extension_score_;

  // INITIALIZATION METHODS
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
