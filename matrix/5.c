// https://leetcode.com/problems/game-of-life/description/?envType=study-plan-v2&envId=top-interview-150

/*
According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The next state of the board is determined by applying the above rules simultaneously to every cell in the current state of the m x n grid board. In this process, births and deaths occur simultaneously.

Given the current state of the board, update the board to reflect its next state.

Note that you do not need to return anything.

Example 1:

Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]

*/

#include <stdio.h>
#include <stdlib.h>

void convolve2D(int** board, int boardSize, int boardColSize, int*** grid){
    // Kernel
    int kernelRows = 3, kernelCols = 3;
    int **kernel = (int **)malloc(kernelRows * sizeof(int *));
    int kernelData[3][3] = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    for (int i = 0; i < kernelRows; i++) {
        kernel[i] = (int *)malloc(kernelCols * sizeof(int));
        for (int j = 0; j < kernelCols; j++) {
            kernel[i][j] = kernelData[i][j];
        }
    }

    // Calculate padding
    int padX = kernelRows / 2;
    int padY = kernelCols / 2;

    // Perform convolution
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize; j++) {
            int sum = 0;

            // Convolve the kernel over the padded matrix
            for (int ki = 0; ki < kernelRows; ki++) {
                for (int kj = 0; kj < kernelCols; kj++) {
                    int ni = i + ki - padX; // Corresponding row in matrix
                    int nj = j + kj - padY; // Corresponding column in matrix

                    // Check boundaries and apply kernel
                    if (ni >= 0 && ni < boardSize && nj >= 0 && nj < boardColSize) {
                        sum += board[ni][nj] * kernel[ki][kj];
                    }
                }
            }

            // Store the result
            (*grid)[i][j] = sum;
        }
    }

    for (int i = 0; i < kernelRows; i++) {
        free(kernel[i]);
    }
    free(kernel);
}



void gameOfLife(int** board, int boardSize, int* boardColSize) {
    int** grid = (int**)malloc(boardSize * sizeof(int*));
    for (int i=0; i<boardSize; i++){
        grid[i] = calloc(*boardColSize, sizeof(int));
    }

    convolve2D(board, boardSize, *boardColSize, &grid); //compute grid

    for (int i=0; i<boardSize; i++){
        for (int j=0; j<*boardColSize; j++){
            if (grid[i][j]<2){
                board[i][j]=0;
            }
            else if (grid[i][j]==2) {
                continue;
            }
            else if (grid[i][j]==3){
                board[i][j]=1;
            }
            else {
                board[i][j]=0;
            }
        }
    }


    for (int i=0; i<boardSize; i++){
        free(grid[i]);
    }
    free(grid);
}

// Helper function to print a 2D matrix
void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Main function for testing
int main() {
    // Input matrix
    int rows = 4, cols = 4;
    int **matrix = (int **)malloc(rows * sizeof(int *));
    int input[4][4] = {
        {0, 1, 0, 1},
        {1, 1, 0, 0},
        {1, 0, 1, 0},
        {1, 0, 0, 1}
    };
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = input[i][j];
        }
    }

    // Print result
    printf("Input Matrix:\n");
    printMatrix(matrix, rows, cols);

    gameOfLife(matrix, rows, &cols);

    printf("\nConvolution Result:\n");
    printMatrix(matrix, rows, cols);

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}