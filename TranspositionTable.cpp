#include <bits/stdc++.h>
#include "TranspositionTable.h"


void TranspositionTable::store(uint64_t hash_value, int score, int depth) {
     table_[hash_value] = TableEntry{ hash_value, score, depth};
}

int TranspositionTable::lookup(uint64_t hash_value, int depth) {
    auto it = table_.find(hash_value);
    if (it != table_.end() && it->second.depth >= depth) {
        return it->second.score;
    }
    return INT_MIN;
}