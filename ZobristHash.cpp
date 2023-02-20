#include <bits/stdc++.h>
#include "ZobristHash.h"

ZobristHash::ZobristHash() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, std::numeric_limits<uint64_t>::max());

    for (size_t i = 0; i < 10; i++) {
        std::vector<uint64_t> row;
        for (size_t j = 0; j < 9; j++) {
            uint64_t rand_num = dis(gen);
            row.push_back(rand_num);
        }
        keys_.push_back(row);
    }
}

uint64_t ZobristHash::hash(std::vector<std::vector<std::string>>& board) {
    uint64_t h = 0;
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[i].size(); j++) {
            if (board[i][j] != "  ") {
                uint64_t piece_key = get_piece_key(board[i][j]);
                h ^= keys_[i][j] ^ piece_key;
            }
        }
    }
    return h;
}

uint64_t ZobristHash::get_piece_key(std::string& piece) {
    // Assigns a unique key to each possible piece type (e.g. "K", "Q", "R", etc.)
    static std::unordered_map<std::string, uint64_t> piece_keys = {
        {"rR", 0},
        {"rH", 1},
        {"rS", 2},
        {"rA", 3},
        {"rG", 4},
        {"rE", 5},
        {"rC", 6},
        {"bR", 7},
        {"bH", 8},
        {"bS", 9},
        {"bA", 10},
        {"bG", 11},
        {"bE", 12},
        {"bC", 13},
    };
    auto it = piece_keys.find(piece);
    if (it != piece_keys.end()) {
        return it->second;
    }
    return 0;
}