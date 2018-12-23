//
// Created by dplus on 20.12.2018..
//
#include <string>
#include "paf_entry.h"

PafEntry::PafEntry(std::vector<std::string> paf_parts) {
    std::string id1 = paf_parts.at(0);
    long len1 = stol(paf_parts.at(1));
    long s1 = stol(paf_parts.at(2));
    long e1 = stol(paf_parts.at(3));
    same_strand_ = paf_parts.at(4) == "+"; //TODO handle same_strand depented on sequence order
    std::string id2 = paf_parts.at(5);
    long len2 = stol(paf_parts.at(6));
    long s2 = stol(paf_parts.at(7));
    long e2 = stol(paf_parts.at(8));
    num_matches_ = stol(paf_parts.at(9));
    num_bases_ = stol(paf_parts.at(10));
    map_quality_ = stoi(paf_parts.at(11));
    sam_data_ = paf_parts.at(12);

    bool order = determine_order(id1, id2, len1, len2, s1, e1, s2, e2);

}

bool determine_order(long len1, long len2, long s1, long e1, long s2, long e2) {

}

void store(std::string id1, std::string id2, long el1, long ol1, long oh1, long oh2, long ol2, long el2) {
    this->origin_id_=id1;
    this->target_id_=id2;
    this->el_1_ = el1;
    this->ol_1_ = ol1;
    this->oh_1_ = oh1;
    this->oh2_2_ = oh2;
    this->ol_2_ = ol2;
    this->el_2_ = el2;
}
void calculate_scores() {

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
