/*
File: Deleting_a_node_in_a_LinkedList.cpp
Date: 2025-10-24 22:53

Problem: Deleting a node in LinkedList
Link: https://leetcode.com/problems/delete-node-in-a-linked-list/description/

Problem Statement:
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
The node to be deleted is guaranteed not to be the tail.

-------------------------------------------------
❌ Brute Force
- Idea: This problem fundamentally requires access to the preceding node to perform a true deletion (changing the predecessor's `next` pointer). Since the problem constraints *prevent* this, a brute-force approach (standard deletion) is impossible under the given setup.
- Time complexity: N/A
- Space complexity: N/A
- Limitations: Cannot access the head or previous node.

✅ Optimized Approachs
- Idea: Since we cannot change the `next` pointer of the node *before* the target node, we must overwrite the target node's data with the data of the next node, effectively deleting the *next* node in the chain. The target node itself becomes a copy of its successor.
- Approach: Overwrite and Bypass.
- Algorithm:
    1. Identify the node immediately following the target node: `nextNode = node->next`.
    2. Copy the value of `nextNode` into the target node: `node->val = nextNode->val`. This visually 'deletes' the target node's original value.
    3. Bypass `nextNode` by setting the target node's `next` pointer to point to the node *after* `nextNode`: `node->next = nextNode->next`.
    4. Free the memory of the actual node that was bypassed (`nextNode`). (Although LeetCode environments usually omit the explicit `delete nextNode` for simplicity, it's good practice in C++).
- Time complexity: O(1). Only a few pointer reassignments and one data copy are performed.
- Space complexity: O(1). No extra memory is allocated proportional to the input size.

💡 Key Pattern:
- **Linked List Deletion Without Predecessor:** This is a specific trick for linked list deletion when you are *only* given the target node, leveraging the constraint that the target is never the tail.

ℹ️ Keywords:
- Linked List, In-place, O(1) Time, Node Deletion, Pointer Manipulation.

🗒️ Notes
- This technique is an exception to standard linked list operations. It doesn't truly delete the memory of the original node; instead, it deletes the data/links of the *next* node and frees its memory, while logically presenting the desired result. The original node is still present but now holds the successor's data.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    /**
     * @brief Deletes a given node (which is not the tail) in a singly linked list in O(1) time.
     * The solution works by copying the value of the next node into the current node
     * and then bypassing the next node.
     * @param node The node to be deleted (must not be the tail).
     * @return void
     */
    void deleteNode(ListNode *node)
    {
        // Since we cannot access the previous node, we overwrite the current node's
        // value with the next node's value, and then skip the next node.
        ListNode *nextNode = node->next;

        // 1. Copy the value of the next node to the current node
        node->val = nextNode->val;

        // 2. Bypass the next node (effectively deleting it)
        node->next = nextNode->next;

        // 3. Free the memory of the bypassed node (essential in production code)
        delete nextNode;
        // In some online judges, this explicit delete might be omitted or handled by the test runner.
    }
};

// --- Helper Functions for Test Cases ---

// Helper function to create a linked list from a vector and return the head
ListNode *createList(const vector<int> &nums)
{
    if (nums.empty())
        return nullptr;
    ListNode *head = new ListNode(nums[0]);
    ListNode *current = head;
    for (size_t i = 1; i < nums.size(); ++i)
    {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }
    return head;
}

// Helper function to find a node by its value for testing purposes
ListNode *findNode(ListNode *head, int val)
{
    ListNode *current = head;
    while (current)
    {
        if (current->val == val)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Helper function to print a linked list (for verification)
void printList(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        cout << current->val << (current->next ? " -> " : "");
        current = current->next;
    }
    cout << endl;
}

// Helper function to delete a linked list
void deleteList(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        ListNode *next = current->next;
        delete current;
        current = next;
    }
}

int main()
{
    Solution sol;

    cout << "--- Deleting a Node in a Linked List (O(1) Trick) ---\n";

    // Test Case 1: Delete a middle node
    // Input: 4 -> 5 -> 1 -> 9. Delete node with value 5 (i.e., the second node).
    // The target node is the one *after* the head.
    vector<int> nums1 = {4, 5, 1, 9};
    ListNode *head1 = createList(nums1);
    ListNode *target1 = findNode(head1, 5); // Node '5' is the target

    cout << "Input 1: ";
    printList(head1);
    if (target1)
    {
        sol.deleteNode(target1);
        cout << "Output 1 (After deleting node '5'): ";
        printList(head1); // Expected: 4 -> 1 -> 9
        // Note: The original node that held '5' now holds '1', and the original node that held '1' is deleted.
    }
    else
    {
        cout << "Error: Target node '5' not found." << endl;
    }
    deleteList(head1);

    cout << "--------------------------------\n";

    // Test Case 2: Delete a node near the tail (third of four nodes)
    // Input: 0 -> 1 -> 2 -> 3. Delete node with value 2 (i.e., the third node).
    vector<int> nums2 = {0, 1, 2, 3};
    ListNode *head2 = createList(nums2);
    ListNode *target2 = findNode(head2, 2); // Node '2' is the target

    cout << "Input 2: ";
    printList(head2);
    if (target2)
    {
        sol.deleteNode(target2);
        cout << "Output 2 (After deleting node '2'): ";
        printList(head2); // Expected: 0 -> 1 -> 3
    }
    else
    {
        cout << "Error: Target node '2' not found." << endl;
    }
    deleteList(head2);

    return 0;
}
