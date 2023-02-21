#ifndef TRANSPOSITION_TABLE_H
#define TRANSPOSITION_TABLE_H

#include <bits/stdc++.h>

struct TableEntry {
    uint64_t hash_value;
    int score;
    int depth;
};

class TranspositionTable {
public:
    void store(uint64_t hash_value, int score, int depth);

    int lookup(uint64_t hash_value, int depth);

private:
    std::unordered_map<uint64_t, TableEntry> table_;
};

#endif