//https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the head of a linked list, remove the nth node from the end of the list and return its head.


Example 1:


Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Example 2:

Input: head = [1], n = 1
Output: []
Example 3:

Input: head = [1,2], n = 1
Output: [1]

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz

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

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {

    if (!head){
        return NULL;
    }


    struct ListNode* dummy = createNode(0);
    dummy->next = head;

    //A->B->C->D->|E|->F->G, n=3, n=8?

    struct ListNode* p1 = dummy->next;
    struct ListNode* p2 = dummy->next;
    struct ListNode* prev = dummy;

    for (int i=1; i<n; i++){
        p2 = p2->next;
    }

    while (p2->next){
        prev = p1;
        p1 = p1->next;
        p2 = p2->next;
    }

    prev->next->next = p1->next;


    struct ListNode* result = dummy->next;
    free (dummy);
    return result;
}