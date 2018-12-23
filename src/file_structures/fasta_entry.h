#include <string>

#ifndef SCAFFOLD_ANCHORN_NODE_H
#define SCAFFOLD_ANCHORN_NODE_H

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
  long length_;

 public:
  FastaEntry(std::string node_id, std::string value, bool is_conting);

};

#endif //SCAFFOLD_ANCHORN_NODE_H
