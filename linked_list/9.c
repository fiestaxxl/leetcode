//https://leetcode.com/problems/partition-list/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.



Example 1:


Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Example 2:

Input: head = [2,1], x = 2
Output: [1,2]


Constraints:

The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200
*/

struct ListNode {
     int val;
     struct ListNode *next;
 };

#include <stdlib.h>
#include <stdbool.h>

struct ListNode* createNode(int val){
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* partition(struct ListNode* head, int x) {
    if (!head){
        return NULL;
    }

    if (x<=-100 || x>=100){
        return head;
    }

    struct ListNode* dummyGreat = createNode(0);
    struct ListNode* dummyLess = createNode(0);

    struct ListNode* great = dummyGreat;
    struct ListNode* less = dummyLess;

    struct ListNode* current = head;

    while(current){
        if (current->val>=x){
            great->next = current;
            great = great->next;
        }
        else {
            less->next = current;
            less = less->next;
        }
        current = current->next;
    }

    great->next = NULL;
    less->next = dummyGreat->next;
    struct ListNode* result = dummyLess->next;
    free(dummyGreat);
    free(dummyLess);
    return result;
}