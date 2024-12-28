//https://leetcode.com/problems/add-two-numbers/?envType=study-plan-v2&envId=top-interview-150

/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.



Example 1:


Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.
Example 2:

Input: l1 = [0], l2 = [0]
Output: [0]
Example 3:

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdlib.h>

struct ListNode* createNode(int val){
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummy = createNode(0);
    struct ListNode* current = dummy;

    int carry = 0;

    while(l1 || l2 || carry){
        int sum = carry;

        if(l1){
            sum += l1->val;
            l1 = l1->next;
        }

        if(l2){
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum/10;
        current->next = createNode(sum%10);
        current = current->next;
    }

    struct ListNode* result = dummy->next;
    free(dummy);
    return result;

}