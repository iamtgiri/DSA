/*
File: Reverse_a_Doubly_Linked_List.cpp
Date: 2025-10-24 22:56

Problem: Reverse a Doubly Linked List
Link: https://www.geeksforgeeks.org/problems/reverse-a-doubly-linked-list/1

Problem Statement:
Given a doubly linked list, reverse the list and return the head of the reversed list.

-------------------------------------------------
❌ Brute Force
- Idea: Traverse the entire list and copy all node values into an auxiliary structure (like a vector). Then, traverse the list again, replacing the existing node values with the values from the vector in reverse order.
- Time complexity: O(N) for two traversals.
- Space complexity: O(N) to store the values.
- Limitations: Requires O(N) extra space, which is typically avoided in linked list reversal problems.

✅ Optimized Approachs
- Idea: Reverse the doubly linked list in-place by swapping the `prev` and `next` pointers for every node.
- Approach: In-place Pointer Swap.
- Algorithm:
    1. Handle edge cases: If the list is empty or has only one node, return the head.
    2. Initialize `curr` to `head` (the current node being processed) and `temp` to `nullptr` (used to temporarily hold the old `prev` pointer).
    3. Iterate through the list using a `while (curr != nullptr)` loop.
    4. Inside the loop, store the current `prev` pointer in `temp`: `temp = curr->prev`.
    5. Swap the pointers for the current node: `curr->prev = curr->next;` and `curr->next = temp;`.
    6. Advance to the next node: `curr = curr->prev;`. Note that the next logical node in the *original* list is now stored in the *new* `prev` pointer.
    7. After the loop terminates, `curr` is `nullptr` and `temp` holds the `prev` pointer of the *last* node in the original list (which is the new head's `next` pointer). The new head is `temp->prev`.
- Time complexity: O(N), as each node is visited and its pointers are swapped exactly once.
- Space complexity: O(1), as only a few pointers (`curr`, `temp`) are used for in-place modification.

💡 Key Pattern:
- **Doubly Linked List Reversal:** This is the standard, most efficient way to reverse a DLL, requiring a temporary pointer to facilitate the simultaneous swap of `prev` and `next` pointers.

ℹ️ Keywords:
- Doubly Linked List, In-place Reversal, Pointer Swap, O(1) Space.

🗒️ Notes
- The key tricky line is `curr = curr->prev;`. Since `curr->prev` was just set to `curr->next` (the next node in the original list), this correctly advances the pointer.
- The final step, `return temp->prev;`, works because `temp` points to the *old head* when the loop finishes (because of the line `temp = curr->prev` on the last iteration), so `temp->prev` holds the new head.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for Doubly Linked List Node (DLLNode)
struct DLLNode
{
    int data;
    DLLNode *next;
    DLLNode *prev;
    DLLNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class Solution
{
public:
    /**
     * @brief Reverses a Doubly Linked List in-place.
     * @param head The head of the Doubly Linked List.
     * @return The head of the reversed list.
     */
    DLLNode *reverseDLL(DLLNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        DLLNode *curr = head;
        DLLNode *temp = nullptr; // Used to store the 'prev' pointer during the swap

        // Traverse and swap next and prev pointers
        while (curr != nullptr)
        {
            // 1. Store the original 'prev' pointer (will become the new 'next')
            temp = curr->prev;

            // 2. Swap 'prev' and 'next'
            curr->prev = curr->next;
            curr->next = temp;

            // 3. Move to the next node (which is currently stored in the new 'prev')
            curr = curr->prev;
        }

        // After the loop, the last node's (new head's) 'next' pointer is stored in 'temp'.
        // The last node's (new head's) 'prev' pointer is nullptr, but temp points to the
        // original second-to-last node. We need the original last node, which is
        // pointed to by the 'next' of the last non-null value of temp.

        // A simpler way: 'temp' holds the original `prev` of the node *after* the last one
        // processed, which is the original last node itself.
        // Return temp (which points to the last node of the original list).
        return temp->prev; // temp->prev is the new head (the old tail)
    }
};

// --- Helper Functions for Test Cases ---

// Helper function to create a Doubly Linked List from a vector
DLLNode *createDLL(const vector<int> &nums)
{
    if (nums.empty())
        return nullptr;
    DLLNode *head = new DLLNode(nums[0]);
    DLLNode *current = head;
    for (size_t i = 1; i < nums.size(); ++i)
    {
        DLLNode *newNode = new DLLNode(nums[i]);
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    return head;
}

// Helper function to print a Doubly Linked List forward and backward
void printDLL(DLLNode *head)
{
    DLLNode *current = head;
    cout << "Forward: ";
    while (current)
    {
        cout << current->data << (current->next ? " <-> " : "");
        if (!current->next)
            break; // Stop at the tail
        current = current->next;
    }
    cout << endl;

    cout << "Backward: ";
    DLLNode *tail = current; // tail from the forward pass
    current = tail;
    while (current)
    {
        cout << current->data << (current->prev ? " <-> " : "");
        current = current->prev;
    }
    cout << endl;
}

// Helper function to delete a Doubly Linked List
void deleteDLL(DLLNode *head)
{
    DLLNode *current = head;
    while (current)
    {
        DLLNode *next = current->next;
        delete current;
        current = next;
    }
}

int main()
{
    Solution sol;

    cout << "--- Reverse a Doubly Linked List ---\n";

    // Test Case 1: Standard case (Even length)
    // Input: 1 <-> 2 <-> 3 <-> 4
    // Expected: 4 <-> 3 <-> 2 <-> 1
    vector<int> nums1 = {1, 2, 3, 4};
    DLLNode *head1 = createDLL(nums1);
    cout << "Test 1 Input:\n";
    printDLL(head1);
    head1 = sol.reverseDLL(head1);
    cout << "Test 1 Output (Reversed):\n";
    printDLL(head1);
    deleteDLL(head1);
    cout << "--------------------------------\n";

    // Test Case 2: Odd length list
    // Input: 5 <-> 6 <-> 7
    // Expected: 7 <-> 6 <-> 5
    vector<int> nums2 = {5, 6, 7};
    DLLNode *head2 = createDLL(nums2);
    cout << "Test 2 Input:\n";
    printDLL(head2);
    head2 = sol.reverseDLL(head2);
    cout << "Test 2 Output (Reversed):\n";
    printDLL(head2);
    deleteDLL(head2);
    cout << "--------------------------------\n";

    // Test Case 3: Edge case (Single node)
    // Input: 10
    // Expected: 10
    vector<int> nums3 = {10};
    DLLNode *head3 = createDLL(nums3);
    cout << "Test 3 Input:\n";
    printDLL(head3);
    head3 = sol.reverseDLL(head3);
    cout << "Test 3 Output (Reversed):\n";
    printDLL(head3);
    deleteDLL(head3);
    cout << "--------------------------------\n";

    return 0;
}
