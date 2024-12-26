// https://leetcode.com/problems/container-with-most-water/?envType=study-plan-v2&envId=top-interview-150
/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.
*/

#include <stdio.h>
#include <stdlib.h>

int move_p(int* height, int* pleft, int* pright) {
    if (height[*pleft]>height[*pright]) {
        (*pright)--;
        return 1;
    }
    else {
        (*pleft)++;
        return 1;
    }
}

int max(int a, int b) {
    if (a>b) {
        return a;
    }
    else {
        return b;
    }
}

int min(int a, int b) {
    if (a>b) {
        return b;
    }
    else {
        return a;
    }
}

int maxArea(int* height, int heightSize) {
    int p_left = 0;
    int p_right = heightSize-1;
    int max_water = min(height[p_left], height[p_right])*(p_right-p_left);

    //printf("After init left: %d, right: %d, value: %d\n", p_left, p_right, max_water);
    for (int i=0; i<heightSize-1; i++) {
        move_p(height, &p_left, &p_right);
        int cur_water = min(height[p_left], height[p_right])*(p_right-p_left);
        max_water = max(cur_water, max_water);
        //printf("After %d step: %d, right: %d, value: %d\n", i+1, p_left, p_right, max_water);
    }

    return max_water;
}

int main(){
    //int* height = calloc(heightSize, sizeof(int));
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int n = 9;
    int res = maxArea(height, n);
    printf("RESULT: %d\n", res);
    return 1;
}