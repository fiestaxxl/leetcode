//faster version

#include <stdbool.h>
#include <string.h>

bool backtrack(int cur_word, int word_len, int x, int y, char* word, char** board, int boardSize, int* boardColSize) {
    if (cur_word == word_len) return true;

    // Temporarily mark the cell as visited
    char temp = board[x][y];
    board[x][y] = '#';

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
    for (int d = 0; d < 4; d++) {
        int newX = x + directions[d][0];
        int newY = y + directions[d][1];

        if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardColSize[x] &&
            board[newX][newY] == word[cur_word]) {
            if (backtrack(cur_word + 1, word_len, newX, newY, word, board, boardSize, boardColSize)) {
                return true;
            }
        }
    }

    // Restore the cell after backtracking
    board[x][y] = temp;
    return false;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int word_len = strlen(word);

    // Early termination: Count character frequencies
    int boardFreq[128] = {0}, wordFreq[128] = {0};
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            boardFreq[(int)board[i][j]]++;
        }
    }
    for (int i = 0; i < word_len; i++) {
        wordFreq[(int)word[i]]++;
        if (wordFreq[(int)word[i]] > boardFreq[(int)word[i]]) {
            return false; // Early termination: Not enough characters
        }
    }

    // Search for the word starting from matching cells
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            if (board[i][j] == word[0]) {
                if (backtrack(1, word_len, i, j, word, board, boardSize, boardColSize)) {
                    return true;
                }
            }
        }
    }
    return false;
}

