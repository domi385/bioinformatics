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
/**
 * Class describes PAF file entry and overlap informations between two
 * sequences.
 */
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
  std::string sam_data_;  // TODO remove variable

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
  /**
   * Method determines order between two sequences in PAF format.
   * @param id1 first sequence id
   * @param id2 second sequence id
   * @param len1 first sequence length
   * @param len2 second sequence length
   * @param s1 overlap start coordinate on first sequence
   * @param e1 overlap end coordinate of first sequence
   * @param s2 overlap start coordinate on second sequence
   * @param e2 overlap end coordinate on second sequence
   * @return true if the order in the PAF file is such that second sequence
   *         extends first sequence, false otherwise
   */
  bool DetermineOrder(std::string &id1,
                      std::string &id2,
                      long len1,
                      long len2,
                      long s1,
                      long e1,
                      long s2,
                      long e2);

  /**
   * Method stores given overlap information in class variables. Order of
   * sequences is such that second sequence extends first sequence end.
   * @param id1 first sequence id
   * @param id2 second sequence id
   * @param len1 first sequence length
   * @param len2 second sequence length
   * @param el1 first sequence extension length
   * @param ol1 first sequence overlap length
   * @param oh1 first sequence overhang length
   * @param oh2 second sequence overhang length
   * @param ol2 second sequence overlap length
   * @param el2 second sequence extension length
   */
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
  /**
   * Constructor that initializes PAF entry.
   * @param paf_parts row from PAF file split by tab
   */
  explicit PafEntry(std::vector<std::string> &paf_parts);
  /**
   * Getter method for obtaining ovrlap origin id.
   * @return overlap origin id
   */
  std::string GetOriginId();
  /**
   * Getter method for obtaining overlap target id.
   * @return overlap target id
   */
  std::string GetTargetId();
  /**
   * Getter method for obtaining overlap score.
   * @return overlap score
   */
  double GetOverlapScore();
  /**
   * Getter method for obtaining extension score.
   * @return extension score
   */
  double GetExtensionScore();
  /**
   * Getter method for obtaining sequence identity.
   * @return sequence identity
   */
  double GetSequenceIdentity();
  /**
   * Getter method for obtaining overlap length.
   * @return overlap length
   */
  long GetOverlapLength();
  /**
   * Getter method for obtaining overhang origin length.
   * @return overhang origin length
   */
  long GetOverhangLenOrigin();
  /**
   * Getter method for obtaining overhang target length.
   * @return overhang target length
   */
  long GetOverhangLenTarget();
  /**
   * Getter method for obtaining extension origin length.
   * @return extension origin length
   */
  long GetExtensionLenOrigin();
  /**
   * Getter method for obtaining extension target length.
   * @return extension target length
   */
  long GetExtensionLenTarget();
  /**
   * Getter method for obtaining overlap origin length.
   * @return overlap origin length
   */
  long GetOverlapLenOrigin();
  /**
   * Getter method for obtaining overlap target length.
   * @return overlap target length
   */
  long GetOverlapLenTarget();
};

#endif  // SRC_FILE_STRUCTURES_PAF_ENTRY_H_
