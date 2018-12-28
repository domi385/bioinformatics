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
