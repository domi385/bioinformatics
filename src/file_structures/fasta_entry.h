// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include <string>

#ifndef SRC_FILE_STRUCTURES_FASTA_ENTRY_H_
#define SRC_FILE_STRUCTURES_FASTA_ENTRY_H_

class FastaEntry {
 private:
  /**
   * Sequence id.
   */
  std::string entry_id_;
  /**
   * Sequence values.
   */
  std::string value_;
  /**
   * Bool flag that is true if current sequence is conting, false otherwise.
   */
  bool is_conting_;
  /**
   * Sequence length;
   */
  unsigned int length_;

 public:
  FastaEntry(std::string &node_id, std::string &value, bool is_conting);

  std::string GetEntryId();
  long GetLength();
  bool IsConting();
  std::string GetValue();
};

#endif  // SRC_FILE_STRUCTURES_FASTA_ENTRY_H_
