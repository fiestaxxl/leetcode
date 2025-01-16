// https://leetcode.com/problems/letter-combinations-of-a-phone-number/?envType=study-plan-v2&envId=top-interview-150

/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.


Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Example 2:

Input: digits = ""
Output: []
Example 3:

Input: digits = "2"
Output: ["a","b","c"]
 

Constraints:

0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <string.h>
#include <stdlib.h>


const char* digitToLetter[] = {
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

int calculateTotalCombinations(char* digits){
    int total = 1;

    for (int i=0; digits[i]!='\0'; i++){
        int digit = digits[i] - '0';
        total *= strlen(digitToLetter[digit]);
    }

    return total;
}

char** letterCombinations(char* digits, int* returnSize) {
    int num_digits = strlen(digits);

    if (num_digits==0){
        *returnSize=0;
        return NULL;
    }

    *returnSize = calculateTotalCombinations(digits);
    char** output = (char**)malloc(*returnSize*sizeof(char*));
    for (int i=0; i<*returnSize; i++){
        output[i] = (char*)malloc((num_digits+1)*sizeof(char));
    }

    int repeat = *returnSize;

    for (int i=0; i<num_digits; i++){
        int digit = digits[i] - '0';

        const char* letters = digitToLetter[digit];
        int num_letters = strlen(letters);
        repeat /= num_letters;

        //2 -> abc
        // [a, b, c]

        //22 
        // [aa, ab, ac, ba, bb, bc, ca, cb, cc]
        for (int j=0; j<*returnSize; j++){
            int idx = (j/repeat)%num_letters;
            output[j][i] = letters[idx]; 
        }
    }

    for (int i=0; i<*returnSize; i++){
        output[i][num_digits] = '\0';
    }

    return output;
}
