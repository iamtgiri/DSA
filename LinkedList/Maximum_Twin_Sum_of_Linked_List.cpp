/*
File: Maximum_Twin_Sum_of_Linked_List.cpp
Date: 2025-10-24 22:46

Problem: Maximum Twin Sum of a Linked List
Link: https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/description/

Problem Statement:
In a linked list of size n, where n is even, the i-th node (0-indexed) of the list
is paired with the (n - 1 - i)-th node. These are called twin nodes.
The twin sum is the sum of a node's value and its twin's value.
Return the maximum twin sum of the linked list.

-------------------------------------------------
❌ Brute Force
- Idea: Traverse the list once to store all node values in an array or vector. Then, iterate from $i=0$ up to $n/2 - 1$, calculate `arr[i] + arr[n - 1 - i]`, and track the maximum sum.
- Time complexity: O(N) for traversal and $O(N)$ for sum calculation $\implies$ O(N).
- Space complexity: O(N) to store all node values in the auxiliary array.
- Limitations: Requires extra space proportional to the input size, violating the goal of an in-place solution.

✅ Optimized Approachs
- Idea: Solve the problem **in-place** using a three-step process: find the middle, reverse the second half, and traverse both halves simultaneously to calculate the maximum twin sum.
- Approach: Two Pointers + In-place Reversal (O(1) Space).
- Algorithm:
    1. **Find Middle:** Use a **slow** and **fast** pointer. When the `fast` pointer reaches the end (or `nullptr`), the `slow` pointer is at the start of the second half (node $n/2$).
    2. **Reverse:** Reverse the second half of the list starting from the `slow` pointer's position.
    3. **Calculate Twin Sum:** Traverse the original head (`head`, representing the first half) and the reversed second half (`slow`) simultaneously. Calculate the twin sum (`head->val + slow->val`) at each step and track the **maximum** value.
- Time complexity: O(N). $O(N)$ to find the middle, $O(N/2)$ to reverse, and $O(N/2)$ to calculate the sum.
- Space complexity: O(1) (excluding the output). We only use a few pointers for the reversal and traversal.

💡 Key Pattern:
- **Two Pointers and List Modification:** This is a classic pattern for problems involving symmetry or the middle of a linked list, where reversing one half allows for simultaneous, in-place traversal.

ℹ️ Keywords:
- Linked List, Two Pointers (Slow/Fast), List Reversal, In-place Algorithm, Twin Sum.

🗒️ Notes
- Since $n$ is guaranteed to be even, the slow pointer will stop exactly at the $n/2$ node, which is the start of the second half.
- The `reverse` function implementation is a standard iterative linked list reversal.
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
     * @brief Finds the maximum twin sum in a linked list of even length.
     * @param head The head of the linked list.
     * @return The maximum twin sum.
     */
    int pairSum(ListNode *head)
    {
        // Step 1: Find the start of the second half (n/2 node) using two pointers
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next; // slow is now at the n/2 node
        }

        // Step 2: Reverse the second half of the list
        // 'slow' becomes the new head of the reversed second half
        slow = reverse(slow);

        int twinsum = INT_MIN;

        // Step 3: Traverse the original first half (head) and the reversed second half (slow)
        while (slow)
        { // We only need to traverse half the list
            twinsum = max(twinsum, head->val + slow->val);
            head = head->next;
            slow = slow->next;
        }

        // Note: The list is permanently modified (second half is reversed).

        return twinsum;
    }

private:
    /**
     * @brief Helper function to reverse a singly linked list.
     * @param head The head of the list to reverse.
     * @return The new head (the old tail).
     */
    ListNode *reverse(ListNode *head)
    {
        ListNode *prev = nullptr;
        while (head)
        {
            ListNode *temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
        }
        return prev;
    }
};

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

    cout << "--- Maximum Twin Sum of a Linked List ---\n";

    // Test Case 1: Standard case
    // List: 5 -> 4 -> 2 -> 1 (n=4)
    // Pairs: (5, 1) = 6, (4, 2) = 6
    // Expected: 6
    vector<int> nums1 = {5, 4, 2, 1};
    ListNode *head1 = createList(nums1);
    cout << "Test 1: List [5, 4, 2, 1] -> Max Twin Sum: " << sol.pairSum(head1) << " (Expected: 6)" << endl;
    // Note: The list is destroyed in the process (or reversed), so cleanup is done after use.
    // However, if we delete the original head after pairSum, we might run into issues
    // since the list structure is modified. We will skip explicit cleanup for simplicity
    // in this test harness, assuming a single run.

    // Test Case 2: Max sum in the middle
    // List: 4 -> 2 -> 2 -> 3 (n=4)
    // Pairs: (4, 3) = 7, (2, 2) = 4
    // Expected: 7
    vector<int> nums2 = {4, 2, 2, 3};
    ListNode *head2 = createList(nums2);
    cout << "Test 2: List [4, 2, 2, 3] -> Max Twin Sum: " << sol.pairSum(head2) << " (Expected: 7)" << endl;

    // Test Case 3: Longer list with varied values
    // List: 10 -> 8 -> 6 -> 4 -> 2 -> 0 (n=6)
    // Pairs: (10, 0) = 10, (8, 2) = 10, (6, 4) = 10
    // Expected: 10
    vector<int> nums3 = {10, 8, 6, 4, 2, 0};
    ListNode *head3 = createList(nums3);
    cout << "Test 3: List [10, 8, 6, 4, 2, 0] -> Max Twin Sum: " << sol.pairSum(head3) << " (Expected: 10)" << endl;

    // Test Case 4: Max sum at the ends
    // List: 1 -> 100000 -> 100000 -> 1 (n=4)
    // Pairs: (1, 1) = 2, (100000, 100000) = 200000
    // Expected: 200000
    vector<int> nums4 = {1, 100000, 100000, 1};
    ListNode *head4 = createList(nums4);
    cout << "Test 4: List [1, 100000, 100000, 1] -> Max Twin Sum: " << sol.pairSum(head4) << " (Expected: 200000)" << endl;

    return 0;
}
