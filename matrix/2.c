//https://leetcode.com/problems/rotate-image/description/?envType=study-plan-v2&envId=top-interview-150

/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
*/

#include <stdio.h>
#include <stdlib.h>

void transpose(int** matrix, int matrixSize) {
    for (int i=0; i<matrixSize; i++){
        for (int j = i + 1; j < matrixSize; j++) { // Avoid double swaps
            int a = matrix[j][i];
            matrix[j][i] = matrix[i][j];
            matrix[i][j] = a;
        }
    }
}

void reverse(int** matrix, int matrixSize) {
    for (int i=0; i<matrixSize; i++){
        for (int j=0; j<matrixSize/2; j++){
            int a = matrix[i][matrixSize-j-1];
            matrix[i][matrixSize-j-1] = matrix[i][j];
            matrix[i][j] = a;
        }
    }
}

void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    transpose(matrix, matrixSize);
    reverse(matrix, matrixSize);
}

int main(){
    int matrixSize = 3;

    // Dynamically allocate the 2D array
    int** arr = (int**)malloc(matrixSize * sizeof(int*));
    for (int i = 0; i < matrixSize; i++) {
        arr[i] = (int*)malloc(matrixSize * sizeof(int));
    }

    // Initialize the 2D array
    int values[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            arr[i][j] = values[i][j];
        }
    }

    reverse(arr, 3);
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < matrixSize; i++) {
        free(arr[i]);
    }
    free(arr);
}
