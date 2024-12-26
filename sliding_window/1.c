//https://leetcode.com/problems/minimum-size-subarray-sum/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an array of positive integers nums and a positive integer target, return the minimal length of a
subarray
 whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
*/

#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    if (a>=b) {
        return b;
    }
    else return a;
}

int minSubArrayLen(int target, int* nums, int numsSize) {
    int p_left = 0;
    int p_right = 1;
    int sum = nums[p_left];
    int curr_length = 1;
    int min_length = numsSize+1;

    while (p_left<numsSize) {
        if (sum>=target) {
            min_length = min(min_length, curr_length);
            sum -= nums[p_left];
            p_left++;
            curr_length--;
        }
        else {
            if (p_right<numsSize) {
                sum += nums[p_right];
                curr_length++;
                p_right++;
            }
            else break;
        }
    }

    if (min_length>numsSize){
        return 0;
    }
    else return min_length;
}

int main(){
    int nums[] = {2,3,1,2,4,3};
    int target = 7;
    int numsSize = (int)(sizeof(nums)/sizeof(nums[0]));
    int result = minSubArrayLen(target, nums, numsSize);
    printf("the result is %d\n", result);
}