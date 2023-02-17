#include <bits/stdc++.h>

using namespace std;

class Board {
    public:
        vector<vector<string>> board; // 10 by 9
        char turn;
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
            turn = 'r';
            worth['S'] = 1;
            worth['R'] = 10;
            worth['H'] = 4;
            worth['C'] = 5;
            worth['G'] = 400;
            worth['A'] = 2;
            worth['E'] = 3;
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

        bool isValidMove(int x1, int y1, int x2, int y2) {
            if(y1 < 0 || y1 > 8 || x1 < 0 || x1 > 9 || y2 < 0 || y2 > 8 || x2 < 0 || x2 > 9) {
                return false;
            }
            if(board[x1][y1][0] != turn) {//wrong color to move, or is empty
                return false;
            }
            set<pair<int, int>> possibleMoves = getMoves(x1, y1);
            /*for(auto s : possibleMoves) {//debugging
                cout << s.first << ", " << s.second << "\n";
            }*/
            if(possibleMoves.find({x2, y2}) == possibleMoves.end()) {//isnt a possible move
                return false;
            }
            if(inCheck(x1, y1, x2, y2)) {
                cout << "IN CHECK!\n";
                return false;
            }
            return true;
        }

        void move(int x1, int y1, int x2, int y2) {
            board[x2][y2] = board[x1][y1];
            board[x1][y1] = "  ";
            turn = turn == 'r' ? 'b' : 'r';
        }

        bool takeable(int x, int y) {
            return board[x][y][0] != turn || board[x][y][1] == ' ';
        }

        set<pair<int, int>> getMoves(int x, int y) {
            if(board[x][y] == "  ") return set<pair<int, int>>{};
            set<pair<int, int>> toReturn;
            int direction = board[x][y][0] == 'r' ? -1 : 1;
            //this should check for blockage
            char piece = board[x][y][1];
            switch (piece) {
                case 'S': //forwards. If crossed the river, left or right also
                    if(x + direction >= 0 && x + direction <= 9 && takeable(x + direction, y)) {
                        toReturn.insert({x + direction, y});
                    }
                    if(direction == -1 ? x <= 4 : x >= 5) {
                        if(y - 1 >= 0 && takeable(x, y - 1)) {
                            toReturn.insert({x, y - 1});
                        }
                        if (y + 1 <= 8 && takeable(x, y + 1)) {
                            toReturn.insert({x, y + 1});
                        }
                    }
                    break;
                case 'R':
                    for(int x2 = x + 1; x2 <= 9; x2++) {
                        if(board[x2][y] != "  ") {
                            if(takeable(x2, y)) {
                                toReturn.insert({x2, y});
                            }
                            break;
                        }
                        toReturn.insert({x2, y});
                    }
                    for(int x2 = x - 1; x2 >= 0; x2--) {
                        if(board[x2][y] != "  ") {
                            if(takeable(x2, y)) {
                                toReturn.insert({x2, y});
                            }
                            break;
                        }
                        toReturn.insert({x2, y});
                    }
                    for(int y2 = y + 1; y2 <= 8; y2++) {
                        if(board[x][y2] != "  ") {
                            if(takeable(x, y2)) {
                                toReturn.insert({x, y2});
                            }
                            break;
                        }
                        toReturn.insert({x, y2});
                    }
                    for(int y2 = y - 1; y2 >= 0; y2--) {
                        if(board[x][y2] != "  ") {
                            if(takeable(x, y2)) {
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
                                    if(takeable(x2, y)) {
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
                                    if(takeable(x2, y)) {
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
                                    if(takeable(x, y2)) {
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
                                    if(takeable(x, y2)) {
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
                    if(!(x + 1 < 0 || (x + 1 >= 3 && x + 1 <=6) || x + 1 > 9) && takeable(x + 1, y)) {
                        toReturn.insert({x + 1, y});
                    }
                    if(!(x - 1 < 0 || (x - 1 >= 3 && x - 1 <=6) || x - 1 > 9) && takeable(x - 1, y)) {
                        toReturn.insert({x - 1, y});
                    }
                    if(y + 1 <= 5 && y + 1 >= 3 && takeable(x, y + 1)) {
                        toReturn.insert({x, y + 1});
                    }
                    if(y - 1 <= 5 && y - 1 >= 3 && takeable(x, y - 1)) {
                        toReturn.insert({x, y - 1});
                    }
                    break;
                case 'A':
                    if(!(x + 1 < 0 || (x + 1 >= 3 && x + 1 <=6) || x + 1 > 9) && y + 1 <= 5 && y + 1 >= 3 && takeable(x + 1, y + 1)) {
                        toReturn.insert({x + 1, y + 1});
                    }
                    if(!(x + 1 < 0 || (x + 1 >= 3 && x + 1 <=6) || x + 1 > 9) && y - 1 <= 5 && y - 1 >= 3 && takeable(x + 1, y - 1)) {
                        toReturn.insert({x + 1, y - 1});
                    }
                    if(!(x - 1 < 0 || (x - 1 >= 3 && x - 1 <=6) || x - 1 > 9) && y - 1 <= 5 && y - 1 >= 3 && takeable(x - 1, y - 1)) {
                        toReturn.insert({x - 1, y - 1});
                    }
                    if(!(x - 1 < 0 || (x - 1 >= 3 && x - 1 <=6) || x - 1 > 9) && y + 1 <= 5 && y + 1 >= 3 && takeable(x - 1, y + 1)) {
                        toReturn.insert({x - 1, y + 1});
                    }
                    break;
                case 'E':
                    if(x + 2 <= 9 && y + 2 <= 8 && board[x + 1][y + 1][0] == ' ' && takeable(x + 2, y + 2)) {
                        toReturn.insert({x + 2, y + 2});
                    }
                    if(x - 2 >= 0 && y + 2 <= 8 && board[x - 1][y + 1][0] == ' ' && takeable(x - 2, y + 2)) {
                        toReturn.insert({x - 2, y + 2});
                    }
                    if(x - 2 >= 0 && y - 2 >= 0 && board[x - 1][y - 1][0] == ' ' && takeable(x - 2, y - 2)) {
                        toReturn.insert({x - 2, y - 2});
                    }
                    if(x + 2 <= 9 && y - 2 >= 0 && board[x + 1][y - 1][0] == ' ' && takeable(x + 2, y - 2)) {
                        toReturn.insert({x + 2, y - 2});
                    }
                    break;
                
                case 'H':
                    if(x + 2 <= 9 && board[x + 1][y][0] == ' ') {
                        if(y + 1 <= 8 && takeable(x + 2, y + 1)) {
                            toReturn.insert({x + 2, y + 1});
                        }
                        if(y - 1 >= 0 && takeable(x + 2, y - 1)) {
                            toReturn.insert({x + 2, y - 1});
                        }
                    }
                    if(x - 2 >= 0 && board[x - 1][y][0] == ' ') {
                        if(y + 1 <= 8 && takeable(x - 2, y + 1)) {
                            toReturn.insert({x - 2, y + 1});
                        }
                        if(y - 1 >= 0 && takeable(x - 2, y - 1)) {
                            toReturn.insert({x - 2, y - 1});
                        }
                    }
                    if(y + 2 <= 8 && board[x][y + 1][0] == ' ') {
                        if(x + 1 <= 9 && takeable(x + 1, y + 2)) {
                            toReturn.insert({x + 1, y + 2});
                        }
                        if(x - 1 >= 0 && takeable(x - 1, y + 2)) {
                            toReturn.insert({x - 1, y + 2});
                        }
                    }
                    if(y - 2 >= 0 && board[x][y - 1][0] == ' ') {
                        if(x + 1 <= 9 && takeable(x + 1, y - 2)) {
                            toReturn.insert({x + 1, y - 2});
                        }
                        if(x - 1 >= 0 && takeable(x - 1, y - 2)) {
                            toReturn.insert({x - 1, y + 2});
                        }
                    }
                    break;
            }
            return toReturn;
        }

        bool inCheck(int x1, int y1, int x2, int y2) {
            string og1 = board[x1][y1];
            string og2 = board[x2][y2];
            board[x2][y2] = board[x1][y1];
            board[x1][y1] = "  ";

            int x, y;
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 9; j++) {
                    if(board[i][j][0] == turn && board[i][j][1] == 'G') {
                        x = i;
                        y = j;
                    }
                }
            }

            int direction = board[x][y][0] == 'r' ? -1 : 1;
            if(soldiercheck(x, y + 1)||soldiercheck(x, y - 1)||soldiercheck(x + direction, y)) {
                return true;
            }

            for(int i = x + 1; i <= 9; i++) {
                if(board[i][y] != "  ") {
                    if(directcheck(i, y)) {
                        board[x1][y1] = og1;
                        board[x2][y2] = og2;
                        return true;
                    }
                    else {
                        for(i++; i <= 9; i++) {
                            if(board[i][y] != "  ") {
                                if(cannoncheck(i, y)) {
                                    board[x1][y1] = og1;
                                    board[x2][y2] = og2;
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
                    if(directcheck(i, y)) {
                        board[x1][y1] = og1;
                        board[x2][y2] = og2;
                        return true;
                    }
                    else {
                        for(i--; i >= 0; i--) {
                            if(board[i][y] != "  ") {
                                if(cannoncheck(i, y)) {
                                    board[x1][y1] = og1;
                                    board[x2][y2] = og2;
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
                    if(directcheck(x, j)) {
                        board[x1][y1] = og1;
                        board[x2][y2] = og2;
                        return true;
                    }
                    else {
                        for(j--; j >= 0; j--) {
                            if(board[x][j] != "  ") {
                                if(cannoncheck(x, j)) {
                                    board[x1][y1] = og1;
                                    board[x2][y2] = og2;
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
                    if(directcheck(x, j)) {
                        board[x1][y1] = og1;
                        board[x2][y2] = og2;
                        return true;
                    }
                    else {
                        for(j++; j <= 8; j++) {
                            if(board[x][j] != "  ") {
                                if(cannoncheck(x, j)) {
                                    board[x1][y1] = og1;
                                    board[x2][y2] = og2;
                                    return true;
                                }
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            board[x1][y1] = og1;
            board[x2][y2] = og2;
            return false;
        }

        bool soldiercheck(int x, int y) {
            if(board[x][y][0] == turn) return false;
            char c = board[x][y][1];
            return c == 'S';
        }
        
        bool directcheck(int x, int y) {
            if(board[x][y][0] == turn) return false;
            char c = board[x][y][1];
            return c == 'R' || c == 'G';
        }

        bool cannoncheck(int x, int y) {
            if(board[x][y][0] == turn) return false;
            char c = board[x][y][1];
            return c == 'C';
        }

        bool isOver() {//check if the game is over
            return false;
        }

        int evalposition() {
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

        int evalposition(vector<vector<string>>& board) {
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

        //we need minimax to get the best val of a certain position
        int minimax(char player, int depth, vector<vector<string>>& board) {// length error idk why
            if(depth == 0) {//fix up the turn order and checks
                return evalposition(board);
            }
            if(player == 'b') {
                int lowest = 10000;
                for(auto v : allmoves(board, 'b')) {// {x1, y1, x2, y2}
                    string og1 = board[v[0]][v[1]];
                    string og2 = board[v[2]][v[3]];
                    board[v[2]][v[3]] = og1;
                    board[v[0]][v[1]] = "  ";
                    lowest = min(lowest, minimax('r', depth - 1, board));
                    board[v[0]][v[1]] = og1;
                    board[v[2]][v[3]] = og2;
                }
                return lowest;
            }
            else if(player == 'r') {
                int highest = -10000;
                for(auto v : allmoves(board, 'r')) {// {x1, y1, x2, y2}
                    string og1 = board[v[0]][v[1]];//its gonna get rly messy w turns too. 
                    string og2 = board[v[2]][v[3]];
                    board[v[2]][v[3]] = og1;
                    board[v[0]][v[1]] = "  ";
                    highest = max(highest, minimax('b', depth - 1, board));
                    board[v[0]][v[1]] = og1;
                    board[v[2]][v[3]] = og2;
                }
                return highest;
            }
            return -1;
        }

        vector<vector<int>> allmoves(vector<vector<string>>& board, char player) {
            vector<vector<int>> toReturn;
            for(int x = 0; x <= 9; x++) {
                for(int y = 0; y <=8; y++) {
                    if(board[x][y][0] == player) {//for this piece, generate all possible moves and get the eval for each
                        for(auto p : getMoves(x, y)) {//doesnt check for checks
                            toReturn.push_back(vector<int>{x, y, p.first, p.second});
                        }
                    }
                }
            }
            return toReturn;
        }

        void aimove() {
            vector<int> moves;
            int lowest = 10000;
            for(auto v : allmoves(board, 'b')) {
                string og1 = board[v[0]][v[1]];
                string og2 = board[v[2]][v[3]];
                board[v[2]][v[3]] = og1;
                board[v[0]][v[1]] = "  ";
                int temp = minimax('r', 3, board);
                if(temp < lowest) {
                    moves = v;
                }
                board[v[0]][v[1]] = og1;
                board[v[2]][v[3]] = og2;
            }
            move(moves[0], moves[1], moves[2], moves[3]);
        }
};

int main() {
    Board game;
    game.setBoard();
    game.printBoard();
    while(!game.isOver()) {
        int x1, y1, x2, y2;
        while(true) {
            cout << "Piece to move (X Y): ";
            cin >> x1 >> y1;
            cout << "Place to move (X Y): ";
            cin  >> x2 >> y2;
            if(game.isValidMove(x1, y1, x2, y2)) {
                game.move(x1, y1, x2, y2);
                break;
            }
            else {
                cout << "Invalid move, try again.\n";
            }
        }
        game.printBoard();
        game.aimove();
        game.printBoard();
    }
}