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

#include "graph_structures/group.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "graph_structures/path.h"

Group::Group(std::vector<Path *> &paths, std::string &target_id) {
  this->paths_ = paths;
  this->target_id_ = target_id;
  min_length_ = paths.at(0)->GetLength();
  max_length_ = paths.at(0)->GetLength();
  for (int i = 0, end = paths_.size(); i < end; i++) {
    Path *curr_path = paths.at(i);
    if (curr_path->GetLength() > max_length_) {
      max_length_ = curr_path->GetLength();
    }
    if (curr_path->GetLength() < min_length_) {
      min_length_ = curr_path->GetLength();
    }
  }
}

int Group::GetMaxFrequency() {
  return max_frequency_;
}

void Group::FilterGroup() {
  CalculateFrequencies();
  std::vector<Path *> filtered_paths;

  for (int i = 0, end = paths_.size(); i < end; i++) {
    int index = paths_[i]->GetLength() - min_length_;
    int frequency = frequencies_[index];
    if (frequency >= 0.5 * max_frequency_) {
      filtered_paths.push_back(paths_.at(i));
    } else {
      delete paths_.at(i);
    }
  }
  paths_ = filtered_paths;
}

void Group::CalculateFrequencies() {
  int n = max_length_ - min_length_ + 1;

  frequencies_.resize(n, 0);
  for (int i = 0, end = paths_.size(); i < end; i++) {
    int index = paths_.at(i)->GetLength() - min_length_;
    frequencies_.at(index)++;
  }
  int max_freq_index = 0;
  max_frequency_ = frequencies_.at(0);
  for (int i = 0; i < n; i++) {
    if (frequencies_.at(i) > max_frequency_) {
      max_freq_index = i;
      max_frequency_ = frequencies_.at(i);
    }
  }
  max_frequency_length_ = min_length_ + max_freq_index;
}
Path *Group::GetConsensusPath() {
  for (int i = 0, end = paths_.size(); i < end; i++) {
    if (paths_.at(i)->GetLength() == max_frequency_length_) {
      return paths_.at(i);
    }
  }
  return NULL;  // hopefully this should never happen
}

std::string Group::GetTargetId() {
  return target_id_;
}
