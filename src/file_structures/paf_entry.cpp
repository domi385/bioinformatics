//
// Created by dplus on 20.12.2018..
//
#include <string>
#include "paf_entry.h"


PafEntry::PafEntry(std::vector<std::string> paf_parts) {
    origin_id_ = paf_parts.at(0);
    origin_length_ = stol(paf_parts.at(1));
    query_start_coord_ = stol(paf_parts.at(2));
    query_end_coord_ = stol(paf_parts.at(3));
    same_strand_ = paf_parts.at(4)=="+";
    target_id_ = paf_parts.at(5);
    target_length_ = stol(paf_parts.at(6));
    target_start_coord_ = stol(paf_parts.at(7));
    target_end_coord_ = stol(paf_parts.at(8));
    num_matches_ = stol(paf_parts.at(9));
    num_bases_=stol(paf_parts.at(10));
    map_quality_=stoi(paf_parts.at(11));
    sam_data_ = paf_parts.at(12);
}

long PafEntry::getTargetLen() {
    return target_length_;
}

long PafEntry::getTargetStart() {
    return target_start_coord_;
}

long PafEntry::getQueryEnd() {
    return query_end_coord_;
}

long PafEntry::getQueryLen() {
    return origin_length_;
}

long PafEntry::getQueryStart() {
    return query_start_coord_;
}

long PafEntry::getTargetEnd() {
    return target_end_coord_;
}

long PafEntry::getNumMatchesWithoutGaps() {
    return num_matches_;
}
