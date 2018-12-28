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
#include <unordered_map>

#include "graph_structures/sequence_node.h"
#include "file_structures/fasta_entry.h"

#ifndef SRC_UTILS_PROJECT_UTILS_H_
#define SRC_UTILS_PROJECT_UTILS_H_

namespace project_utils {
/**
 * Function outputs vector of strings to standard output in following form
 * 'member1' 'member2' 'member3' ...
 * @param collection vector of strings that needs to be printed
 */
void OutputStringVector(std::vector<std::string> &collection);

/**
 * Function for splitting strings by a given delimiter into a vector.
 * 'aba' splitted by 'a' -> ['', 'b', '']
 * 'aba' splitted by 'b' -> ['a','a']
 * @param s string that needs to be splitted
 * @param delimiter delimiter for splitting
 * @return vector of string parts
 */
std::vector<std::string> SplitString(std::string &s, std::string &delimiter);

/**
 * Function for converting fasta entry map to map of sequence nodes.
 * @param entries map that maps fasta entry id to fasta entry
 * @return map that maps fasta entry id to sequence node
 */
std::unordered_map<std::string, SequenceNode> ConvertFastaToNodeMap(std::vector<
    FastaEntry> &entries);
}  // namespace project_utils

#endif  // SRC_UTILS_PROJECT_UTILS_H_
