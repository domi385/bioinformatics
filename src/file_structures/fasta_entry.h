#include <string>

#ifndef SCAFFOLD_FASTA_ENTRY_H
#define SCAFFOLD_FASTA_ENTRY_H

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
};

#endif //SCAFFOLD_FASTA_ENTRY_H
