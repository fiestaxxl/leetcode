// https://leetcode.com/problems/set-matrix-zeroes/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void zeros(int** matrix, int col, int row, int matrixSize, int* matrixColSize) {
    for (int i=0; i<matrixSize; i++){
        matrix[i][col] = 0;
    }

    for (int i=0; i<*matrixColSize; i++){
        matrix[row][i] = 0;
    }
}


void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int size = matrixSize * (*matrixColSize);

    bool* zeros_arr = calloc(size, sizeof(bool));
    for (int i=0; i<size; i++){
        zeros_arr[i] = false;
    }

    int index = 0;
    for (int i=0; i<matrixSize; i++){
        for (int j=0; j<*matrixColSize; j++){
            if (matrix[i][j]==0){
                zeros_arr[index]=true;
            }
            index++;
        }
    }

    index = 0;
    for (int i=0; i<matrixSize; i++){
        for (int j=0; j<*matrixColSize; j++){
            if (zeros_arr[index]){
                zeros(matrix, j, i, matrixSize, matrixColSize);
            }
            index++;
        }
    }

    free(zeros_arr);
}

int main(){

    int cols = 5;
    int rows = 8;

    int **arr = (int **)malloc(cols * sizeof(int *));
    for (int i = 0; i < cols; i++)
    {
        arr[i] = (int *)malloc(rows * sizeof(int));
    }

    // Initialize the 2D array
    int values[5][8] = {
        {1, 2, 3, 5, 6, 7, 8, 9},
        {10, 11, 12, 13, 14, 15, 16, 17},
        {18, 19, 20, 0, 22, 23, 24, 25},
        {26, 27, 28, 29, 30, 0, 32, 33},
        {0, 35, 36, 37, 38, 39, 40, 41}};

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            arr[i][j] = values[i][j];
        }
    }

    int returnSize;
    int matrixColSize = rows;

    setZeroes(arr, cols, &matrixColSize);

    for (int i=0; i<cols; i++){
        for (int j=0; j<matrixColSize; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < cols; i++)
    {
        free(arr[i]);
    }
    free(arr);
}