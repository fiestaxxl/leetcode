// https://leetcode.com/problems/valid-sudoku/description/?envType=study-plan-v2&envId=top-interview-150

/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

Example 1:

Input: board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    // Arrays of sets for rows, columns, and 3x3 subgrids
    bool rows[9][9] = {false};  // rows[i][num] means number num is present in row i
    bool cols[9][9] = {false};  // cols[j][num] means number num is present in column j
    bool subgrids[9][9] = {false};  // subgrids[k][num] means number num is present in subgrid k


    for (int i=0; i<boardSize; i++){
        for (int j=0; j<boardSize; j++){
            if (board[i][j]!='.'){
                int num = board[i][j] - '1';
                // Check if the number is already in the current row, column, or subgrid
                if (rows[i][num] || cols[j][num] || subgrids[(i / 3) * 3 + (j / 3)][num]) {
                    return false;
                }

                // Mark the number as seen in the row, column, and subgrid
                rows[i][num] = true;
                cols[j][num] = true;
                subgrids[(i / 3) * 3 + (j / 3)][num] = true;
            }
        }
    }
    return true;
}

int main() {
    // Example board to test
    char* board[9] = {
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... .....",
        "..... ..... ..... ..... ..... ..... ..... ..... ....."
    };
    int boardSize = 9;
    int boardColSize[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    if (isValidSudoku(board, boardSize, boardColSize)) {
        printf("The Sudoku board is valid.\n");
    } else {
        printf("The Sudoku board is invalid.\n");
    }

    return 0;
}