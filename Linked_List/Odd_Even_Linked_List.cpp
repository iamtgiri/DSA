/*
File: Odd_Even_Linked_List.cpp
Date: 2025-10-24 22:50

Problem: Odd Even Linked List
Link: https://leetcode.com/problems/odd-even-linked-list/description/

Problem Statement:
Given the head of a singly linked list, group all the nodes with odd indices together followed
by the nodes with even indices. The first node is considered odd, and the second node is even,
and so on. The relative order inside both the odd and even groups should remain as it was in the
input. You must solve the problem in O(1) extra space complexity and O(n) time complexity.

-------------------------------------------------
❌ Brute Force
- Idea: Traverse the list and store all node values in a secondary data structure (like an array). Reorder the array by placing odd-indexed elements first, followed by even-indexed elements. Finally, reconstruct a new linked list from the ordered array.
- Time complexity: O(N)
- Space complexity: O(N) to store node values in the auxiliary array.
- Limitations: Violates the O(1) extra space complexity constraint.

✅ Optimized Approachs
- Idea: Maintain two separate lists (one for odd-indexed nodes, one for even-indexed nodes) by manipulating the `next` pointers in-place. After separating all nodes, connect the tail of the odd list to the head of the even list.
- Approach: In-place Linked List Manipulation.
- Algorithm:
    1. Handle edge cases: return `head` if the list is empty or has only one node.
    2. Initialize `evenHead` to mark the start of the even list (i.e., `head->next`).
    3. Use two pointers, `curr_odd` (starting at `head`) and `curr_even` (starting at `head->next`), to traverse and build the two sub-lists.
    4. In a loop, redirect the `next` pointers: `curr_odd` jumps over `curr_even` to the next odd node, and `curr_even` jumps over the new odd node to the next even node.
    5. After the loop, the odd list ends at `curr_odd`. Connect the tail of the odd list to the stored `evenHead`.
    6. Return the original `head`.
- Time complexity: O(N), as the list is traversed exactly once.
- Space complexity: O(1), as only a few pointers are used for linking.

💡 Key Pattern:
- **List Partitioning:** This technique is a common and efficient way to partition a linked list in-place based on a condition (in this case, node position parity).

ℹ️ Keywords:
- Linked List, In-place, O(1) Space, Two Pointers, List Rearrangement.

🗒️ Notes
- The final step, `curr_odd->next = evenHead;`, is crucial for merging the two sub-lists back into a single list.
- The loop termination condition (`curr_even && curr_even->next`) correctly handles both even and odd total lengths of the list.
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
     * @brief Groups all nodes with odd indices followed by even indices in-place.
     * @param head The head of the linked list.
     * @return The head of the reordered linked list.
     */
    ListNode *oddEvenList(ListNode *head)
    {
        // Edge cases: 0 or 1 node
        if (!head || !head->next)
            return head;

        // Store the head of the even list for the final connection
        ListNode *evenHead = head->next;

        // Pointers for the tails of the odd and even lists
        ListNode *curr_odd = head;
        ListNode *curr_even = head->next;

        // Iterate and weave the two lists together
        // Loop continues as long as there is at least one pair of nodes left (even and next odd)
        while (curr_even && curr_even->next)
        {
            // 1. Link current odd node to the next odd node (which is curr_even->next)
            curr_odd->next = curr_even->next;
            curr_odd = curr_odd->next;

            // 2. Link current even node to the next even node (which is curr_odd->next)
            // Note: curr_odd is now the next odd node. Its next pointer points to the next even node.
            curr_even->next = curr_odd->next;
            curr_even = curr_even->next;
        }

        // Final step: Connect the tail of the odd list to the head of the even list
        curr_odd->next = evenHead;

        return head;
    }
};

// --- Helper Functions for Test Cases ---

// Helper function to create a linked list from a vector
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

    cout << "--- Odd Even Linked List Reordering ---\n";

    // Test Case 1: Odd length list (5 nodes)
    // Input: 1 -> 2 -> 3 -> 4 -> 5
    // Odd (1, 3, 5), Even (2, 4)
    // Expected: 1 -> 3 -> 5 -> 2 -> 4
    vector<int> nums1 = {1, 2, 3, 4, 5};
    ListNode *head1 = createList(nums1);
    cout << "Input 1: ";
    printList(head1);
    head1 = sol.oddEvenList(head1);
    cout << "Output 1: ";
    printList(head1); // Expected: 1 -> 3 -> 5 -> 2 -> 4
    deleteList(head1);

    // Test Case 2: Even length list (6 nodes)
    // Input: 2 -> 1 -> 3 -> 5 -> 6 -> 4
    // Odd (2, 3, 6), Even (1, 5, 4)
    // Expected: 2 -> 3 -> 6 -> 1 -> 5 -> 4
    vector<int> nums2 = {2, 1, 3, 5, 6, 4};
    ListNode *head2 = createList(nums2);
    cout << "\nInput 2: ";
    printList(head2);
    head2 = sol.oddEvenList(head2);
    cout << "Output 2: ";
    printList(head2); // Expected: 2 -> 3 -> 6 -> 1 -> 5 -> 4
    deleteList(head2);

    // Test Case 3: Smallest valid list (2 nodes)
    // Input: 10 -> 20
    // Expected: 10 -> 20
    vector<int> nums3 = {10, 20};
    ListNode *head3 = createList(nums3);
    cout << "\nInput 3: ";
    printList(head3);
    head3 = sol.oddEvenList(head3);
    cout << "Output 3: ";
    printList(head3); // Expected: 10 -> 20
    deleteList(head3);

    // Test Case 4: Edge case (1 node)
    // Input: 99
    // Expected: 99
    vector<int> nums4 = {99};
    ListNode *head4 = createList(nums4);
    cout << "\nInput 4: ";
    printList(head4);
    head4 = sol.oddEvenList(head4);
    cout << "Output 4: ";
    printList(head4); // Expected: 99
    deleteList(head4);

    return 0;
}
