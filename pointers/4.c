// https://leetcode.com/problems/is-subsequence/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isSubsequence(char* s, char* t) {
    size_t s_len = strlen(s);
    size_t t_len = strlen(t);

    int s_point = 0;

    if (s_len == 0) {
        return true; // An empty string is a subsequence of any string
    }

    for (int i=0; i<t_len; i++){

        if (t[i]==s[s_point]){
            s_point++;
        }
        if (s_point==s_len){
            return true;
        }
    }
    return false;
}

void main(){
    char* a = "";
    printf("%zu\n", strlen(a));
}