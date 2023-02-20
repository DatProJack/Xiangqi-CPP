#include <iostream>
#include "ZobristHash.h"
using namespace std;

int main() {
    ZobristHash zhash;

    vector<vector<string>> board(10, vector<string>(9, "bR"));

    cout << zhash.hash(board) << "\n";
    return 0;
}