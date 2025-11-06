/*
File: Remove_K_Digits.cpp
Date: 2025-11-06 12:25

Problem: Remove K Digits
Link: https://leetcode.com/problems/remove-k-digits/description/

Problem Statement:
Given a non-negative integer `num` represented as a string, remove `k` digits from 
the number so that the new number is the smallest possible. The resulting number 
must not have leading zeros (except for the number 0 itself).

-------------------------------------------------
❌ Brute Force
- Idea: Generate all possible subsequences of `num` that remain after removing `k` 
  digits. Convert each subsequence to a number and find the minimum among them.
- Time complexity: O(C(N, K) * N). Where C(N, K) is the binomial coefficient $\binom{N}{K}$. 
  This is infeasibly slow for large N.
- Space complexity: O(N * C(N, K)).
- Limitations: Exponential time complexity.

✅ Optimized Approachs
- Idea: This is a **greedy** problem. To minimize a number, we must ensure the most 
  significant digits (leftmost) are as small as possible. This means if we see a 
  digit smaller than the preceding digit, the preceding digit should be removed. 
  This structure is perfectly handled by a Monotonic Stack.
- Approach: **Greedy Monotonic Stack (implemented via Deque)**.
- Algorithm: 
  1. Initialize a deque/stack `dq` to store the resulting digits.
  2. Iterate through each character `c` in the input string `num`.
  3. **Greedy Removal:** While the deque is not empty, `k > 0`, and the last digit 
     in the deque (`dq.back()`) is greater than the current digit `c`: 
     - Pop the larger digit (`dq.pop_back()`).
     - Decrement $k$. This digit is successfully removed.
  4. **Leading Zero Prevention:** Before pushing `c`, check if we are pushing a '0' 
     and the deque is currently empty. If so, skip pushing the '0' to avoid leading zeros.
  5. **Push:** Otherwise, push `c` onto the back of the deque.
  6. **Final Removals:** After the loop, if $k > 0$ (meaning we had an increasing 
     sequence like "1234"), remove the remaining $k$ digits from the back of the deque.
  7. **Result Construction:** Construct the final string from the deque. If the result 
     is empty, return "0".
- Time complexity: **O(N)**. Each digit is pushed and popped at most once.
- Space complexity: **O(N)** for the deque (which holds the result).

💡 Key Pattern:
- **Monotonic Stack for Optimal Subsequences:** Used when building an optimal 
  sequence (like the smallest number or longest subarray) where the decision to 
  keep the current element depends on its value relative to the previously kept 
  elements, and removal/replacement is allowed.

ℹ️ Keywords: 
- Greedy, Monotonic Stack, Deque, Smallest Number.

🗒️ Notes
- The two crucial edge cases are: 1) handling leading zeros, and 2) handling the 
  case where $k$ is not fully exhausted (e.g., input "12345" and k=2). Both are handled 
  correctly in the provided solution.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
    * @brief Removes K digits from a string representation of a number to form the smallest possible new number.
    * @param num The string representation of the non-negative integer.
    * @param k The number of digits to remove.
    * @return The smallest possible number string after removal.
    */
    std::string removeKdigits(std::string num, int k) {
        // Deque acts as a Monotonic Stack to build the smallest number sequence.
        std::deque<char> dq; 
        
        for (char c : num) {
            // Greedy Step (Monotonic Check): 
            // While the stack top is greater than the current digit 'c' and we still have removals left (k > 0),
            // remove the larger digit (dq.back()) to ensure a smaller prefix.
            while (!dq.empty() && k > 0 && dq.back() > c) {
                dq.pop_back();
                k--;
            }
            
            // Leading Zero Check: 
            // Only push 'c' if the deque is not empty OR 'c' is not '0'.
            // This prevents sequences like "050" from being created.
            if (!dq.empty() || c != '0') {
                dq.push_back(c);
            }
            // If it's a leading zero and dq is empty, we skip pushing it.
        }
        
        // Final Removals: If k is still greater than 0, it means the remaining digits are
        // in non-decreasing order (e.g., "12345"), so we remove from the end.
        while (!dq.empty() && k--) {
            dq.pop_back();
        }
        
        // Handle the case where the result is empty (all digits removed).
        if (dq.empty()) {
            return "0";
        }
        
        // Build the final result string from the deque.
        std::string res = "";
        while (!dq.empty()) {
            res += dq.front();
            dq.pop_front();
        }
        
        return res;
    }

};

int main() {
    Solution sol;
    
    cout << "--- Remove K Digits Test Cases ---\n";
    
    // Test Case 1: Standard removal
    // "1432219", k=3. 4, 3, 2 removed. Result: "1219"
    cout << "Test 1 (\"1432219\", k=3): Expected \"1219\", Got " << sol.removeKdigits("1432219", 3) << endl;
    
    // Test Case 2: Leftover removals (increasing sequence)
    // "10200", k=1. 2 is removed, leaving "100".
    cout << "Test 2 (\"10200\", k=1): Expected \"200\", Got " << sol.removeKdigits("10200", 1) << endl;
    
    // Test Case 3: All digits removed
    // "10", k=2. 1 removed, then 0 removed. Result: "0"
    cout << "Test 3 (\"10\", k=2): Expected \"0\", Got " << sol.removeKdigits("10", 2) << endl;

    // Test Case 4: Complex leading zero handling
    // "10001", k=4. 1 removed, then 0s are pushed, then 1 removed. Wait, "1" removed by the next '0'. "0001". remove 3 more. "0"
    // Process: dq: [], c='1'. push -> [1].
    // c='0'. dq.back() > '0'. pop 1, k=2. dq: []. push '0' is skipped (leading zero).
    // c='0'. push '0' skipped.
    // c='0'. push '0' skipped.
    // c='1'. push -> [1].
    // Loop ends. dq: [1]. k=2. pop back (1), k=1. dq: [].
    // Result: "0". (Mistake in logic above, the provided solution seems right)
    // Let's trace using the solution's logic for "10001", k=4:
    // 1. c='1'. dq empty, push '1'. dq: [1]
    // 2. c='0'. dq.back()='1' > '0'. Pop 1, k=3. dq: [].
    //    dq empty, c='0'. Skip push (leading zero prevention).
    // 3. c='0'. dq empty, c='0'. Skip push.
    // 4. c='0'. dq empty, c='0'. Skip push.
    // 5. c='1'. dq empty, c!='0'. Push '1'. dq: [1].
    // Loop ends. dq: [1]. k=3.
    // Final removals: pop 1, k=2. dq: [].
    // Result: "0". This is correct.
    cout << "Test 4 (\"10001\", k=4): Expected \"0\", Got " << sol.removeKdigits("10001", 4) << endl;
    
    return 0;
}