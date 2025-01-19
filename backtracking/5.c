// https://leetcode.com/problems/generate-parentheses/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8
*/


#include <stdlib.h>

typedef struct {
    char** data;
    int cur_pos;
    int capacity;
} List;

List* initList(int initialCapacity) {
    List* list = (List*)malloc(sizeof(List));
    list->data = (char**)malloc(initialCapacity * sizeof(char*));
    list->cur_pos = 0;
    list->capacity = initialCapacity;
    return list;
}

void addToList(List* list, char* combination, int size){
    if (list->cur_pos == list->capacity){
        list->capacity *= 2;
        list->data = (char**)realloc(list->data, list->capacity * sizeof(char*));
    }

    list->data[list->cur_pos] = (char*)malloc((size + 1) * sizeof(char)); // +1 for null terminator
    memcpy(list->data[list->cur_pos], combination, size * sizeof(char));
    list->data[list->cur_pos][size] = '\0'; // Null-terminate the string
    list->cur_pos++;
}

void backtrack(char* current, int num_opened, int num_closed, int total_pairs, List* list){
    if (total_pairs == num_opened && total_pairs == num_closed){
        addToList(list, current, total_pairs*2);
        return;
    }

    if (num_opened>num_closed){
        current[num_opened+num_closed] = ')';
        backtrack(current, num_opened, num_closed+1, total_pairs, list);
    }

    if (num_opened<total_pairs){
        current[num_opened+num_closed] = '(';
        backtrack(current, num_opened+1, num_closed, total_pairs, list);
    }
    return;
}

char** generateParenthesis(int n, int* returnSize) {
    List* list = initList(n*2);

    char* current = (char*)malloc(n*2*sizeof(char));
    backtrack(current, 0, 0, n, list);
    free(current);

    *returnSize = list->cur_pos;
    char** result = list->data;
    free(list);

    return result;
}   