#include <bits/stdc++.h>
using namespace std;

class ChessBoard {
private:
    int rows { };
    int colums { };
    int OUT_OF_BOUNDS { };
    vector<vector<int>> board;

public:
    ChessBoard(const int &rows, const int &colums) : rows(rows), colums(colums) {
        // Much better resizing methods on dr's solution.
        board.resize(rows);
        for(auto &row : board) {
            row.resize(colums);
            for(auto &cell : row)
                cell = 0;
        }
    }

    void Print() const {
        for(auto &row : board) {
            for(auto &cell : row)
                cout << cell << ' ';
            cout << '\n';
        }
    }

    int Get(const int &x, const int &y) const {
        if(IsValid(x, y))
            return board[x][y];
        return -1;
    }

    int& Get(const int &x, const int &y) {
        if(IsValid(x, y))
            return board[x][y];
        return OUT_OF_BOUNDS;
    }

    void Set(const int &x, const int &y, const int &num) {
        if(IsValid(x, y))
            board[x][y] = num;
    }

    bool IsValid(const int &x, const int &y) const {
        if(x >= 0 && x < rows && y >= 0 && y < colums)
            return true;
        return false;
    }

    int operator() (const int &x, const int &y) const {
        return Get(x, y);
    }

    int& operator() (const int &x, const int &y) {
        return Get(x, y);
    }

    // No protection for this one, didn't do a const one as that would mean copying entire vector.
    vector<int>& operator[] (const int &x) {
        return board[x];
    }
};

int main() {
    ChessBoard board(2, 3);
    // board.Print(); TOOK ME A GOOOOOOOD LONG WHILE.
    // board[2][3]; == board.Operator[](2).Opeartor[](3);

    // Zero indexed.
    board(0, 0) = 10;
    board[0][1] = 20;
    cout << board[0][0] << " " << board(0, 1);

    // Stopped here. revise solutions, compare to dr's ones.
    cout << "\n\n Bye :) \n\n";
    return 0;
}