// https://leetcode.com/problems/spiral-matrix/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an m x n matrix, return all elements of the matrix in spiral order.



Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:


Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int bot = matrixSize-1;
    int top = 0;
    int left = 0;
    int right = *matrixColSize-1;
    int el = 0;

    *returnSize = matrixSize*(*matrixColSize);

    int* result = (int*)calloc(*returnSize, sizeof(int));

    while ((top<=bot) && (left<=right)) {
        //top row from left to right
        for (int i=left; i<=right; i++){
            result[el] = matrix[top][i];
            el++;
        }
        top++;

        //right col from top to bot
        for (int i=top; i<=bot; i++){
            result[el] = matrix[i][right];
            el++;
        }
        right--;

        //bot row from right to left
        if (top<=bot){
            for (int i=right; i>=left; i--){
                result[el] = matrix[bot][i];
                el++;
            }
            bot--;
        }

        //left col from bot to top
        if (left<=right){
            for (int i=bot; i>=top; i--){
                result[el] = matrix[i][left];
                el++;
            }
            left++;
        }
    }
    return result;
}

void main()
{
    int cols = 5;
    int rows = 8;

    // Dynamically allocate the 2D array
    int **arr = (int **)malloc(cols * sizeof(int *));
    for (int i = 0; i < cols; i++)
    {
        arr[i] = (int *)malloc(rows * sizeof(int));
    }

    // Initialize the 2D array
    int values[5][8] = {
        {1, 2, 3, 5, 6, 7, 8, 9},
        {10, 11, 12, 13, 14, 15, 16, 17},
        {18, 19, 20, 21, 22, 23, 24, 25},
        {26, 27, 28, 29, 30, 31, 32, 33},
        {34, 35, 36, 37, 38, 39, 40, 41}};

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            arr[i][j] = values[i][j];
        }
    }

    int returnSize;
    int matrixColSize = rows;

    int* result = spiralOrder(arr, cols, &matrixColSize, &returnSize);

    for (int i=0; i<returnSize; i++){
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free the dynamically allocated memory
    for (int i = 0; i < cols; i++)
    {
        free(arr[i]);
    }
    free(arr);
    free(result);
}