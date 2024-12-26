//https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strStr(char* haystack, char* needle) {
    size_t len_hay = strlen(haystack);
    size_t len_need = strlen(needle);

    for (int i=0; i<len_hay; i++) {
        if ((haystack[i]==needle[0]) && (i+len_need<=len_hay)){
            int cntr = 1;

            for (int j=i+1; j<i+len_need; j++) {

                if (haystack[j]==needle[cntr]) {
                    cntr++;
                }
                else {
                    break;
                }
            }

            if (cntr == len_need){
                    return i;
                }
        }
    }
    return -1;
}

int main(){
    char* haystack = "a";
    char* needle = "a";
    int out = strStr(haystack, needle);
    printf("result is: %d\n", out);
    return 0;
}