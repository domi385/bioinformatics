#include <string>

#ifndef SCAFFOLD_ANCHORN_NODE_H
#define SCAFFOLD_ANCHORN_NODE_H


class FastaEntry {

private:
    std::string entry_id_;
    std::string value_;
    bool is_conting_;
    long length_;

public:
    FastaEntry(std::string node_id, std::string value, bool is_conting);

};


#endif //SCAFFOLD_ANCHORN_NODE_H
