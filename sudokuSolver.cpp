// #include <math.h>
// #include <iostream>
#include <bits/stdc++.h>
using namespace std;

// CC => corner case
void Print(int board[][9], int n)
// passing i and j as the coordinates of the cell where we
// want to check
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isValid(int board[][9], int i, int j, int num, int n) {
    // First check row -> column -> Sub Grid (ith row and jth column)
    // √
    // Row Check
    // for(int x =0; x<n; x++){
    //     if(board[i][x]==num) return false;
    // }
    // // Column Check
    // for (int x = 0; x < n; x++) {
    //     if (board[x][j] == num) return false;
    // }
    // Row and Column Check
    for (int x = 0; x < n; x++) {
        if (board[i][x] == num || board[x][j] == num) {
            return false;
        }
    }

    // SubMatrix Check
    int rn = sqrt(n);
    int si = i - i % rn;
    int sj = j - j % rn;

    for (int x = si; x < si + rn; x++) {
        for (int y = sj; y < sj + rn; y++) {
            if (board[x][y] == num) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuSolver(int board[][9], int i, int j, int n) {
    // Base Case
    if (i == n) {
        Print(board, n);  // print the board
        return true;      // tells us that the que has been solved
    }

    // CC 2 check if we are not inside the board (out of coloms (i.e. onto the
    // 9th colomn)) This case should be before the 1st CC for obvious reasons
    if (j == n) {
        return SudokuSolver(
            board, i + 1, 0,
            n);  // moving to the next row (i) and 1st colums (j)
    }

    // CC 1 if cell is already filled -> just skip that and move ahead
    if (board[i][j] != 0) {
        return SudokuSolver(board, i, j + 1,
                            n);  // moving it to the next cell (next to it)
    }

    // we will try to fill the cell with n aprropriate number

    for (int num = 1; num <= 9; num++) {
        // First check if the number which we are going to fill [i] can be
        // filled in the cell
        if (isValid(board, i, j, num, n)) {
            board[i][j] =
                num;  // if true we place the number and then recursively call
                      // the same function for next iteration
            bool subAns = SudokuSolver(board, i, j + 1, n);
            if (subAns) {
                return true;
            }
            // else we have to backtrack to undo changes and fill appropriate
            // number
            board[i][j] = 0;
        }
    }

    return false;
}

int main() {
    int n = 9;
    int board[9][9] = {
        {0, 0, 7, 1, 0, 0, 0, 6, 0}, {1, 0, 5, 2, 0, 8, 0, 0, 0},
        {6, 0, 0, 0, 0, 7, 1, 2, 0}, {3, 1, 2, 4, 0, 5, 0, 0, 8},
        {0, 0, 6, 0, 9, 0, 2, 0, 0}, {0, 0, 0, 0, 0, 3, 0, 0, 1},
        {0, 0, 1, 0, 0, 4, 9, 8, 6}, {8, 0, 3, 9, 0, 6, 0, 0, 0},
        {0, 6, 0, 0, 8, 2, 7, 0, 3},
    };

    SudokuSolver(board, 0, 0, n);

    return 0;
}