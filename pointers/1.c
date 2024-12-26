//https://leetcode.com/problems/valid-palindrome/?envType=study-plan-v2&envId=top-interview-150
/*
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void prepare(char* s) {
    //removes spaces, punctuation and lowercases s
    char* d = s;
    do {
        // Check if the character is not a space or punctuation
        if (!isspace((unsigned char)*d) && !ispunct((unsigned char)*d)) {
            *s++ = tolower((unsigned char)*d); // Convert to lowercase and copy
        }
        ++d; // Move source pointer
    } while (*d);
    *s = '\0'; // Null-terminate the result
}

int isPalindrome(char* s) {
    // Prepare the string in place
    prepare(s);

    // Calculate the length after preparation
    size_t len = strlen(s);
    int step = (int)(len / 2);

    // Compare characters from both ends
    for (int i = 0; i < step; i++) {
        if (s[i] != s[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char s[] = "hahahaah";
    int res = isPalindrome(s);
    printf("%d\n", res);
}