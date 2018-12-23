//
// Created by dplus on 20.12.2018..
//

#include <string>
#include <vector>

#ifndef SCAFFOLD_PAFENTRY_H
#define SCAFFOLD_PAFENTRY_H

class PafEntry {
 private:

  //FILE ATTRIBUTES
  std::string origin_id_;
  long origin_length_;
  long query_start_coord_;
  long query_end_coord_;
  bool same_strand_;
  std::string target_id_;
  long target_length_;
  long target_start_coord_;
  long target_end_coord_;
  long num_matches_;
  long num_bases_;
  int map_quality_;
  std::string sam_data_;

  //OVERLAP ATTRIBUTES
  long el_1_;
  long ol_1_;
  long oh_1_;
  long oh_2_;
  long ol_2_;
  long el_2_;
  bool order_; //true if the original order is satisfied, false otherwise

  //OVERLAP SCORES
  double sequence_identity_;
  double overlap_score_;
  double extension_score_;

  //INITIALIZATION METHODS
  bool DetermineOrder(std::string& id1, std::string& id2, long len1, long len2, long s1,
                       long e1, long s2, long e2);
  void Store(std::string& id1, std::string& id2, long len1, long len2, long el1, long ol1, long oh1, long oh2,
             long ol2, long el2);
  void CalculateScores();

 public:

  //CONSTRUCTORS
  explicit PafEntry(std::vector<std::string>& paf_parts);

  //GETTERS

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
};

#endif //SCAFFOLD_PAFENTRY_H
