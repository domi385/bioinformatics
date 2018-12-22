//
// Created by dplus on 20.12.2018..
//

#include <string>
#include <vector>

#ifndef SCAFFOLD_PAFENTRY_H
#define SCAFFOLD_PAFENTRY_H


class PafEntry {
private:
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


    //INITIALIZATION METHODS
    bool determine_order(long len1, long len2, long s1, long e1, long s2, long e2);
    void store(long el1, long ol1, long oh1, long oh2, long ol2, long el2);
    void calculate_scores();


public:

    //CONSTRUCTORS
    PafEntry(std::vector<std::string> paf_parts);

    //GETTERS

    long getTargetLen();

    long getTargetStart();

    long getQueryEnd();

    long getQueryLen();

    long getQueryStart();

    long getTargetEnd();

    long getNumMatchesWithoutGaps();
};


#endif //SCAFFOLD_PAFENTRY_H
