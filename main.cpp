#include <bits/stdc++.h>
#include "Board.h"
using namespace std;

int main() {
    Board game;
    game.setBoard();
    game.printBoard();
    while(true) {
        int x1, y1, x2, y2;
        while(true) {
            cout << "Piece to move (X Y): ";
            cin >> x1 >> y1;
            cout << "Place to move (X Y): ";
            cin  >> x2 >> y2;
            if(game.isValidMove(x1, y1, x2, y2)) {
                game.finalMove(x1, y1, x2, y2);
                break;
            }
            else {
                cout << "Try again.\n";
            }
        }
        game.printBoard();
        if(game.over()) {
            break;
        }
        game.AIMove();
        game.printBoard();
        if(game.over()) {
            break;
        }
    }
}