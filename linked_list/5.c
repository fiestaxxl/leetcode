//https://leetcode.com/problems/reverse-linked-list-ii/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.



Example 1:


Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]
*/

#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* createNode(int val){
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    if (left==right || head == NULL){
        return head;
    }

    struct ListNode* dummy = createNode(0);
    dummy->next = head;

    // Traverse to the node before `left`
    struct ListNode* left_prev = dummy;
    for (int i = 1; i < left; i++) {
        left_prev = left_prev->next;
    }
    // Start reversing the sublist
    struct ListNode* prev = NULL;                   //a->A->B->C->D->E->f
    struct ListNode* current = left_prev->next;

    for (int i = 0; i <= right - left; i++) {
        struct ListNode* temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }

    // Reconnect the reversed sublist
    left_prev->next->next = current; // Connect the tail of the reversed sublist to the remaining list
    left_prev->next = prev;          // Connect the head of the reversed sublist to `left_prev`

    // Return the new head
    struct ListNode* new_head = dummy->next;
    free(dummy); // Free the dummy node
    return new_head;
}