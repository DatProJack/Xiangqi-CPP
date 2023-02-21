#ifndef BOARD_H
#define BOARD_H

#include <bits/stdc++.h>
#include "ZobristHash.h"
#include "TranspositionTable.h"
using namespace std;

class Board {
public:
    vector<vector<string>> board;
    char turn;
    bool isOver;
    unordered_map<char, int> worth;
    ZobristHash zhash;
    TranspositionTable ttable;

    void setBoard();

    bool takeable(int x, int y, char color);

    void printBoard();

    set<pair<int, int>> getMoves(int x, int y);

    bool over();

    bool inCheck(int x1, int y1, int x2, int y2);

    bool soldiercheck(int x, int y, char color);
    
    bool directcheck(int x, int y, char color);

    bool cannoncheck(int x, int y, char color);

    vector<vector<int>> getLegalMoves(char player);

    string trymove(int x1, int y1, int x2, int y2);

    void undomove(int x1, int y1, int x2, int y2, string captured);

    void finalMove(int x1, int y1, int x2, int y2);

    bool isValidMove(int x1, int y1, int x2, int y2);

    int evaluateBoard();
    
    int minimax(int depth, int alpha, int beta, char player);

    void AIMove();

    int MoveGenerationTest(int depth, char color);
};


#endif