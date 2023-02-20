#ifndef ZOBRIST_HASH_H
#define ZOBRIST_HASH_H

#include <bits/stdc++.h>

class ZobristHash {
public:
    ZobristHash();

    uint64_t hash(std::vector<std::vector<std::string>>& board);

private:
    std::vector<std::vector<uint64_t>> keys_;

    uint64_t get_piece_key(std::string& piece);
};

#endif