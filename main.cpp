#include <bits/stdc++.h>

using namespace std;

class Board {
    public:
        vector<vector<string>> board; // 10 by 9
        char turn;//only used for player
        bool isOver;//re check whenver making an actual real move
        unordered_map<char, int> worth;

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
            turn = 'r';//should only check for whose turn very generally
            isOver = false;
            worth['S'] = 1;
            worth['R'] = 10;
            worth['H'] = 4;
            worth['C'] = 5;
            worth['G'] = 400;
            worth['A'] = 2;
            worth['E'] = 3;
        }

        bool takeable(int x, int y, char color) {
            return board[x][y][0] != color || board[x][y][1] == ' ';
        }

        void printBoard() {
            cout << "\n\n\n\n\n\n\n\n\n\n  Y ";
            int color;
            for(int x = 0; x < board[0].size(); x++) cout << x << "  ";
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

        set<pair<int, int>> getMoves(int x, int y) {
            if(board[x][y] == "  ") return set<pair<int, int>>{};
            char piece = board[x][y][1];
            set<pair<int, int>> toReturn;
            int direction = board[x][y][0] == 'r' ? -1 : 1;
            //this should check for blockage
            char color = board[x][y][0];
            switch (piece) {
                case 'S': //forwards. If crossed the river, left or right also
                    if(x + direction >= 0 && x + direction <= 9 && takeable(x + direction, y, color)) {
                        toReturn.insert({x + direction, y});
                    }
                    if(direction == -1 ? x <= 4 : x >= 5) {
                        if(y - 1 >= 0 && takeable(x, y - 1, color)) {
                            toReturn.insert({x, y - 1});
                        }
                        if (y + 1 <= 8 && takeable(x, y + 1, color)) {
                            toReturn.insert({x, y + 1});
                        }
                    }
                    break;
                case 'R':
                    for(int x2 = x + 1; x2 <= 9; x2++) {
                        if(board[x2][y] != "  ") {
                            if(takeable(x2, y, color)) {
                                toReturn.insert({x2, y});
                            }
                            break;
                        }
                        toReturn.insert({x2, y});
                    }
                    for(int x2 = x - 1; x2 >= 0; x2--) {
                        if(board[x2][y] != "  ") {
                            if(takeable(x2, y, color)) {
                                toReturn.insert({x2, y});
                            }
                            break;
                        }
                        toReturn.insert({x2, y});
                    }
                    for(int y2 = y + 1; y2 <= 8; y2++) {
                        if(board[x][y2] != "  ") {
                            if(takeable(x, y2, color)) {
                                toReturn.insert({x, y2});
                            }
                            break;
                        }
                        toReturn.insert({x, y2});
                    }
                    for(int y2 = y - 1; y2 >= 0; y2--) {
                        if(board[x][y2] != "  ") {
                            if(takeable(x, y2, color)) {
                                toReturn.insert({x, y2});
                            }
                            break;
                        }
                        toReturn.insert({x, y2});
                    }
                    break;
                case 'C':
                    for(int x2 = x + 1; x2 <= 9; x2++) {
                        if(board[x2][y] != "  ") {
                            for(x2++; x2 <= 9; x2++) {
                                if(board[x2][y] != "  ") {
                                    if(takeable(x2, y, color)) {
                                        toReturn.insert({x2, y});
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        toReturn.insert({x2, y});
                    }
                    for(int x2 = x - 1; x2 >= 0; x2--) {
                        if(board[x2][y] != "  ") {
                            for(x2--; x2 >= 0; x2--) {
                                if(board[x2][y] != "  ") {
                                    if(takeable(x2, y, color)) {
                                        toReturn.insert({x2, y});
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        toReturn.insert({x2, y});
                    }
                    for(int y2 = y + 1; y2 <= 8; y2++) {
                        if(board[x][y2] != "  ") {
                            for(y2++; y2 <= 8; y2++) {
                                if(board[x][y2] != "  ") {
                                    if(takeable(x, y2, color)) {
                                        toReturn.insert({x, y2});
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        toReturn.insert({x, y2});
                    }
                    for(int y2 = y - 1; y2 >= 0; y2--) {
                        if(board[x][y2] != "  ") {
                            for(y2--; y2 >= 0; y2--) {
                                if(board[x][y2] != "  ") {
                                    if(takeable(x, y2, color)) {
                                        toReturn.insert({x, y2});
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        toReturn.insert({x, y2});
                    }
                    break;
                case 'G':
                    if(!(x + 1 < 0 || (x + 1 >= 3 && x + 1 <=6) || x + 1 > 9) && takeable(x + 1, y, color)) {
                        toReturn.insert({x + 1, y});
                    }
                    if(!(x - 1 < 0 || (x - 1 >= 3 && x - 1 <=6) || x - 1 > 9) && takeable(x - 1, y, color)) {
                        toReturn.insert({x - 1, y});
                    }
                    if(y + 1 <= 5 && y + 1 >= 3 && takeable(x, y + 1, color)) {
                        toReturn.insert({x, y + 1});
                    }
                    if(y - 1 <= 5 && y - 1 >= 3 && takeable(x, y - 1, color)) {
                        toReturn.insert({x, y - 1});
                    }
                    break;
                case 'A':
                    if(!(x + 1 < 0 || (x + 1 >= 3 && x + 1 <=6) || x + 1 > 9) && y + 1 <= 5 && y + 1 >= 3 && takeable(x + 1, y + 1, color)) {
                        toReturn.insert({x + 1, y + 1});
                    }
                    if(!(x + 1 < 0 || (x + 1 >= 3 && x + 1 <=6) || x + 1 > 9) && y - 1 <= 5 && y - 1 >= 3 && takeable(x + 1, y - 1, color)) {
                        toReturn.insert({x + 1, y - 1});
                    }
                    if(!(x - 1 < 0 || (x - 1 >= 3 && x - 1 <=6) || x - 1 > 9) && y - 1 <= 5 && y - 1 >= 3 && takeable(x - 1, y - 1, color)) {
                        toReturn.insert({x - 1, y - 1});
                    }
                    if(!(x - 1 < 0 || (x - 1 >= 3 && x - 1 <=6) || x - 1 > 9) && y + 1 <= 5 && y + 1 >= 3 && takeable(x - 1, y + 1, color)) {
                        toReturn.insert({x - 1, y + 1});
                    }
                    break;
                case 'E':
                    if(x + 2 <= 9 && y + 2 <= 8 && board[x + 1][y + 1][0] == ' ' && takeable(x + 2, y + 2, color)) {
                        toReturn.insert({x + 2, y + 2});
                    }
                    if(x - 2 >= 0 && y + 2 <= 8 && board[x - 1][y + 1][0] == ' ' && takeable(x - 2, y + 2, color)) {
                        toReturn.insert({x - 2, y + 2});
                    }
                    if(x - 2 >= 0 && y - 2 >= 0 && board[x - 1][y - 1][0] == ' ' && takeable(x - 2, y - 2, color)) {
                        toReturn.insert({x - 2, y - 2});
                    }
                    if(x + 2 <= 9 && y - 2 >= 0 && board[x + 1][y - 1][0] == ' ' && takeable(x + 2, y - 2, color)) {
                        toReturn.insert({x + 2, y - 2});
                    }
                    break;
                
                case 'H':
                    if(x + 2 <= 9 && board[x + 1][y][0] == ' ') {
                        if(y + 1 <= 8 && takeable(x + 2, y + 1, color)) {
                            toReturn.insert({x + 2, y + 1});
                        }
                        if(y - 1 >= 0 && takeable(x + 2, y - 1, color)) {
                            toReturn.insert({x + 2, y - 1});
                        }
                    }
                    if(x - 2 >= 0 && board[x - 1][y][0] == ' ') {
                        if(y + 1 <= 8 && takeable(x - 2, y + 1, color)) {
                            toReturn.insert({x - 2, y + 1});
                        }
                        if(y - 1 >= 0 && takeable(x - 2, y - 1, color)) {
                            toReturn.insert({x - 2, y - 1});
                        }
                    }
                    if(y + 2 <= 8 && board[x][y + 1][0] == ' ') {
                        if(x + 1 <= 9 && takeable(x + 1, y + 2, color)) {
                            toReturn.insert({x + 1, y + 2});
                        }
                        if(x - 1 >= 0 && takeable(x - 1, y + 2, color)) {
                            toReturn.insert({x - 1, y + 2});
                        }
                    }
                    if(y - 2 >= 0 && board[x][y - 1][0] == ' ') {
                        if(x + 1 <= 9 && takeable(x + 1, y - 2, color)) {
                            toReturn.insert({x + 1, y - 2});
                        }
                        if(x - 1 >= 0 && takeable(x - 1, y - 2, color)) {
                            toReturn.insert({x - 1, y - 2});
                        }
                    }
                    break;
            }
            /* debugging
            for(auto v : toReturn) {// 1,0 2,0 3,0 4,0. should only be 1,0 2,0
                cout << v.first << " " << v.second << "\n";
            }*/
            return toReturn;
        }

        bool inCheck(int x1, int y1, int x2, int y2) {
            char color = board[x1][y1][0];
            string captured = trymove(x1, y1, x2, y2);

            int x, y;
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 9; j++) {
                    if(board[i][j][0] == color && board[i][j][1] == 'G') {
                        x = i;
                        y = j;
                    }
                }
            }
            
            int direction = board[x][y][0] == 'r' ? -1 : 1;
            if(soldiercheck(x, y + 1, color)||soldiercheck(x, y - 1, color)||soldiercheck(x + direction, y, color)) {
                undomove(x1, y1, x2, y2, captured);
                return true;
            }
            
            
            for(int i = x + 1; i <= 9; i++) {
                if(board[i][y] != "  ") {
                    if(directcheck(i, y, color)) {
                        undomove(x1, y1, x2, y2, captured);
                        return true;
                    }
                    else {
                        for(i++; i <= 9; i++) {
                            if(board[i][y] != "  ") {
                                if(cannoncheck(i, y, color)) {
                                    undomove(x1, y1, x2, y2, captured);
                                    return true;
                                }
                                break;
                            }
                        }
                    }
                    break;
                }
            }

            for(int i = x - 1; i >= 0; i--) {
                if(board[i][y] != "  ") {
                    if(directcheck(i, y, color)) {
                        undomove(x1, y1, x2, y2, captured);
                        return true;
                    }
                    else {
                        for(i--; i >= 0; i--) {
                            if(board[i][y] != "  ") {
                                if(cannoncheck(i, y, color)) {
                                    undomove(x1, y1, x2, y2, captured);
                                    return true;
                                }
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            for(int j = y - 1; j >= 0;j --) {
                if(board[x][j] != "  ") {
                    if(directcheck(x, j, color)) {
                        undomove(x1, y1, x2, y2, captured);
                        return true;
                    }
                    else {
                        for(j--; j >= 0; j--) {
                            if(board[x][j] != "  ") {
                                if(cannoncheck(x, j, color)) {
                                    undomove(x1, y1, x2, y2, captured);
                                    return true;
                                }
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            for(int j = y + 1; j <= 8; j++) {
                if(board[x][j] != "  ") {
                    if(directcheck(x, j, color)) {
                        undomove(x1, y1, x2, y2, captured);
                        return true;
                    }
                    else {
                        for(j++; j <= 8; j++) {
                            if(board[x][j] != "  ") {
                                if(cannoncheck(x, j, color)) {
                                    undomove(x1, y1, x2, y2, captured);
                                    return true;
                                }
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            undomove(x1, y1, x2, y2, captured);
            return false;
        }

        bool soldiercheck(int x, int y, char color) {//fix up these turn things
            if(board[x][y][0] == color) return false;
            char c = board[x][y][1];
            return c == 'S';
        }
        
        bool directcheck(int x, int y, char color) {
            if(board[x][y][0] == color) return false;
            char c = board[x][y][1];
            return c == 'R' || c == 'G';
        }

        bool cannoncheck(int x, int y, char color) {
            if(board[x][y][0] == color) return false;
            char c = board[x][y][1];
            return c == 'C';
        }

        vector<vector<int>> getLegalMoves(char player) {
            vector<vector<int>> toReturn;
            for(int x = 0; x <= 9; x++) {
                for(int y = 0; y <=8; y++) {
                    if(board[x][y][0] == player) {//for this piece, generate all possible moves and get the eval for each
                        for(auto p : getMoves(x, y)) {//doesnt check for checks
                            if(!inCheck(x, y, p.first, p.second)) { 
                                toReturn.push_back(vector<int>{x, y, p.first, p.second}); 
                            }
                        }
                    }
                }
            }
            return toReturn;
        }

        string trymove(int x1, int y1, int x2, int y2) {
            //cout << x1 << ", " << y1 << "->"<<x2<<", "<<y2<<"\n";//9, 7 TO 8, 9. OUT OF BOUNDS!!
            string piece = board[x1][y1];
            string captured = board[x2][y2];
            board[x2][y2] = piece;
            board[x1][y1] = "  ";
            return captured;
        }

        void undomove(int x1, int y1, int x2, int y2, string captured) {
            board[x1][y1] = board[x2][y2];
            board[x2][y2] = captured;
        }

        void finalMove(int x1, int y1, int x2, int y2) {
            board[x2][y2] = board[x1][y1];
            board[x1][y1] = "  ";
            turn = turn == 'r' ? 'b' : 'r';
        }

        //checkmate when alllegalmoves is 0 and inCheck(0, 0, 0, 0) is true
        //statemate is when alllegalmoves i 0 and inCheck(0,0,0,0) is false
        bool isValidMove(int x1, int y1, int x2, int y2) {//only for player input
            if(y1 < 0 || y1 > 8 || x1 < 0 || x1 > 9 || y2 < 0 || y2 > 8 || x2 < 0 || x2 > 9) {
                cout << "Out of bounds. ";
                return false;
            }
            if(board[x1][y1][0] != turn) {//wrong color to move, or is empty
                cout << "Wrong turn or empty square. ";
                return false;
            }
            set<pair<int, int>> possibleMoves = getMoves(x1, y1);
            for(auto s : possibleMoves) {//debugging
                cout << s.first << ", " << s.second << "\n";
            }
            //here?
            if(possibleMoves.find({x2, y2}) == possibleMoves.end()) {//isnt a possible move
                cout << "Unreachable spot !";
                return false;
            }
            if(inCheck(x1, y1, x2, y2)) {
                cout << "IN CHECK!";
                return false;
            }
            return true;
        }

        int evaluateBoard() {
            int ans = 0;
            for(auto &i : board) {
                for(auto &j : i) {
                    int multiplier = j[0] == 'r' ? 1 : -1;
                    if(j != "  ") {
                        ans += multiplier * worth[j[1]];
                    }
                }
            }
            return ans;
        }

        int minimax(int depth, int alpha, int beta, char player) {
            if(depth == 0) {
                return evaluateBoard();
            }
            else if(player == 'r') {
                int maxscore = INT_MIN;
                for(vector<int> move : getLegalMoves('r')) {
                    string captured = trymove(move[0], move[1], move[2], move[3]);
                    int score = minimax(depth - 1, alpha, beta, 'r');
                    undomove(move[0], move[1], move[2], move[3], captured);
                    maxscore = max(maxscore, score);
                    alpha = max(alpha, score);
                    if(beta <= alpha) {
                        break;
                    }
                }
                return maxscore;
            }
            else {
                int minscore = INT_MAX;
                for(vector<int> move : getLegalMoves('b')) {
                    string captured = trymove(move[0], move[1], move[2], move[3]);
                    int score = minimax(depth - 1, alpha, beta, 'b');
                    undomove(move[0], move[1], move[2], move[3], captured);
                    minscore = min(minscore, score);
                    beta = min(beta, score);
                    if(beta <= alpha) {
                        break;
                    }
                }
                return minscore;
            }

        }

        void AIMove() {
            int bestscore = INT_MAX;
            vector<int> bestmove;
            auto asdf = getLegalMoves('b');
            for(vector<int> move : getLegalMoves('b')) {//this dont run
                string captured = trymove(move[0], move[1], move[2], move[3]);
                int score = minimax(3, INT_MIN, bestscore, 'r');//length of 2 throws length error. NOT ANYMORE
                if(score < bestscore) {
                    bestscore = score;
                    bestmove = move;
                }
                undomove(move[0], move[1], move[2], move[3], captured);
            }
            finalMove(bestmove[0],bestmove[1],bestmove[2],bestmove[3]);
        }
};


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
        game.AIMove();
        game.printBoard();
    }
}