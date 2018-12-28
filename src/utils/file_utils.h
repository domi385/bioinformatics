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

#include <vector>
#include <string>

#include "file_structures/fasta_entry.h"
#include "file_structures/paf_entry.h"
#include "graph_structures/connection_node.h"
#include "utils/project_utils.h"

#ifndef SRC_UTILS_FILE_UTILS_H_H_
#define SRC_UTILS_FILE_UTILS_H_H_

namespace file_utils {

/**
 * Function loads FASTA file to unordered map that maps fasta enrty id to fasta entry object.
 *
 * @param filename fasta file name
 * @param is_conting_file true if given file contains contings, false otherwise
 *
 * @returns unordered map that maps fasta entry id to fasta entry object
 */
std::vector<FastaEntry> LoadFromFasta(std::string &filename,
                                      bool is_conting_file);

/**
 * Function loads PAF file to vector of paf entries, it also filters PAF entries using filterPafEntries function.
 *
 * @param file_name paf file name
 *
 * @returns vector of filtered paf entries
 */
std::vector<PafEntry> LoadFromPAF(std::string &file_name);

/**
* Function decides should you filter given paf entry.
* @param entry paf entry for which to decide if it should be filtered
* @return true if the entry should be filtered
*/
bool FilterPafEntries(PafEntry &entry);

void SaveFastaFile(
    std::string& file_name, std::vector<ConnectionNode *>& connection_graph,
    std::unordered_map<std::string, FastaEntry*> fasta_map);

std::string EdgeToString(
    Edge* prevEdge,
    Edge* edge, std::unordered_map<std::string, FastaEntry*> fasta_map);
std::string EdgeEndToString(
    Edge* edge,
    std::unordered_map<std::string, FastaEntry*> fasta_map);
std::string EdgeBeginningToString(
    Edge* edge,
    std::unordered_map<std::string, FastaEntry*> fasta_map);
};  // namespace file_utils

#endif  // SRC_UTILS_FILE_UTILS_H_H_
