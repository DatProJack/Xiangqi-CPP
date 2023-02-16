#include <bits/stdc++.h>

using namespace std;

class Board {
    public:
        vector<vector<string>> board; // 10 by 9

        void setBoard() {
            board ={{"bR", "bH", "bE", "bA", "bG", "bA", "bE", "bH", "bR"},
                    {"  ","  ","  ","  ","  ","  ","  ","  ","  "},
                    {"  ","bC","  ","  ","  ","  ","  ","bC","  "},
                    {"bS","  ","bS","  ","bS","  ","bS","  ","bS"},
                    {"  ","  ","  ","  ","  ","  ","  ","  ","  "},
                    {"  ","  ","  ","  ","  ","  ","  ","  ","  "},
                    {"rS","  ","rS","  ","rS","  ","rS","  ","rS"},
                    {"  ","rC","  ","  ","  ","  ","  ","rC","  "},
                    {"  ","  ","  ","  ","  ","  ","  ","  ","  "},
                    {"rR", "rH", "rE", "rA", "rG", "rA", "rE", "rH", "rR"}};
        }

        void printBoard() {
            cout << "\n\n\n\n\n\n\n\n\n\n Y";
            int color;
            for(int x = 0; x < board[0].size(); x++) cout << "  " << x;
            cout << "\nX\n";
            for(int x = 0; x < board.size(); x++) {
                for(int y = 0; y <= board[0].size(); y++) {
                    if(y == 0) cout << x << "  ";
                    else {
                        string j = board[x][y-1];
                        color = j[0] == 'r' ? 31 : 30;
                        cout << "\033[" << color << "m " << j[1] << " \033[m";
                    }
                }
                cout << "\n";
            }
        }

        bool isValidMove(int x1, int y1, int x2, int y2) {
            //must make the move and then scan if the king is in check


            return true;
        }

        void move(int x1, int y1, int x2, int y2) {
            board[x2][y2] = board[x1][y1];
            board[x1][y1] = "  ";
        }

        vector<pair<int, int>> getMoves(int x, int y) {
            if(board[x][y] == "  ") return vector<pair<int, int>>{};
            //this should check for blockage
            return vector<pair<int, int>>{};
        }
        
        bool isOver() {//check if the game is over
            return false;
        }
};

int main() {
    Board game;
    game.setBoard();
    game.printBoard();
    while(!game.isOver()) {
        int x1, y1, x2, y2;
        cout << "What's the location of the piece you're moving?";
        cin >> x1 >> y1;
        cout << "Where are you moving it?";
        cin  >> x2 >> y2;
        game.move(x1, y1, x2, y2);
        game.printBoard();
    }
}