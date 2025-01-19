//https://leetcode.com/problems/word-search/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Example 2:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
Example 3:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
 

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.
*/


#include <stdbool.h>
#include <stdlib.h>


void backtrack(int cur_word, int word_len, int l_x, int l_y, char* word, char** board, int boardSize, int* boardColSize, bool* result, bool* visited){
    if(*result){
        return;
    }

    if (cur_word == word_len){
        *result = true;
        return;
    }

    int directions[4][2] = {{-1,0}, {1,0}, {0, -1}, {0, 1}};

    for (int i=0; i<4; i++){
        int newX = l_x + directions[i][0];
        int newY = l_y + directions[i][1];

        if (newX>=0 && newX<boardSize && newY>=0 && newY<boardColSize[0] && word[cur_word]==board[newX][newY] && !visited[newX*boardColSize[0]+ newY]){
            visited[newX*boardColSize[0]+ newY] = true;
            backtrack(cur_word+1, word_len, newX, newY, word, board, boardSize, boardColSize, result, visited);
            visited[newX*boardColSize[0]+ newY] = false;
        }
    }
    return;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    bool result = false;
    int word_len = strlen(word);
    int size = boardSize * boardColSize[0];
    bool* visited = (bool*)calloc(size, sizeof(bool));


    for (int i=0; i<boardSize; i++){
        for (int j=0; j<boardColSize[0]; j++){
            if (board[i][j]==word[0]){
                visited[i*boardColSize[0]+j] = true;
                backtrack(1, word_len, i, j, word, board, boardSize, boardColSize, &result, visited);
                visited[i*boardColSize[0]+j] = false;
            }
        }
    }

    free(visited);

    return result;

}