/*
File: 1-bit_and_2-bit_Characters.cpp
Date: 2025-11-19 00:19

Problem: 1-bit and 2-bit Characters
Link: https://leetcode.com/problems/1-bit-and-2-bit-characters/description/

Problem Statement:
We have two special characters:
1. A 1-bit character encoded as '0'.
2. A 2-bit character encoded as '10' or '11' (starts with '1').
Given a string of bits that always ends with a '0' (the array 'bits'), determine if the final '0' must be a 1-bit character.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Recursive parsing (Top-Down DP). Start from the beginning and explore all valid decoding paths.
- Time complexity: O(N) in practice, but exponential in the worst case if not memoized, though this is rare for this problem's constraints.
- Space complexity: O(N) for recursion depth.
- Limitations: Overkill, as the problem can be solved by only looking at the suffix.

Current/Optimized Approachs
- Idea: The crucial observation is that the validity of the final character only depends on the sequence of '1's immediately preceding it. The rest of the string can be decoded greedily, and the final outcome will be the same.
- Approach: **Greedy Suffix Analysis / Linear Scan**
- Algorithm:
  1. **Remove Final Bit:** The last bit (which is always 0) is temporarily ignored, as we check how the preceding sequence is parsed.
  2. **Count Trailing Ones:** Scan backward from the second-to-last position and count the number of consecutive '1's (let this be `k`).
  3. **Parity Check:**
     - If `k` is **even** (0, 2, 4...), the '1's can be perfectly paired up as 2-bit characters. The sequence ends with a valid character *before* the final '0', allowing the final '0' to start a new 1-bit character. **Result: True.**
     - If `k` is **odd** (1, 3, 5...), the last remaining '1' must be paired with the final '0' to form a 2-bit character ('10'). In this case, the final '0' is the *second bit* of a 2-bit character and cannot stand alone. **Result: False.**
- Time complexity: O(N). The worst case is a full scan of the array (e.g., `[1, 1, 1, ..., 1, 0]`).
- Space complexity: O(1) auxiliary space.

💡 Key Pattern:
- **Greedy Parity Check:** For sequencing problems where the local decoding decision depends on the current bit, checking the parity (even/odd count) of trailing elements is often a simplification shortcut.

ℹ️ Keywords:
- Greedy Algorithm, Suffix Analysis, Parity, Linear Scan.

🗒️ Notes
- The clever bitwise check `~ones & 1` is equivalent to checking if `ones` is even (`ones % 2 == 0`).
- The logic relies on the problem constraint that the array always ends with a '0'.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines if the last bit (which is '0') must be a 1-bit character.
     * @param bits The array of 0s and 1s representing the encoded string.
     * @return true if the last character is a 1-bit character, false otherwise.
     */
    bool isOneBitCharacter(vector<int> &bits)
    {
        // We temporarily remove the final '0' to analyze the preceding sequence.
        // We are checking how the remaining bits can be parsed to determine
        // the status of the final character.
        bits.pop_back();
        int n = bits.size(); // N is now the index of the second-to-last bit

        // Short-circuit: If the remaining sequence is empty (original was [0]),
        // or if the bit immediately preceding the final '0' is another '0',
        // the decoding is unambiguous, and the last '0' must be a 1-bit character.
        if (n == 0 || bits.back() == 0)
            return true;

        // Count the number of consecutive 1s immediately before the final 0 (trailing ones)
        int ones = 0;
        for (int i = n - 1; i >= 0 && bits[i] == 1; i--)
            ones++;

        // The core logic:
        // If 'ones' is even, the final '0' is a 1-bit character (True).
        // If 'ones' is odd, the final '0' is the second bit of a 2-bit character (False).

        // The expression '~ones & 1' is a compact way to check if 'ones' is even.
        // It returns 1 (True) if 'ones' is even, and 0 (False) if 'ones' is odd.
        return ~ones & 1;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: [1, 0, 0] -> Expected: true (Parsed as [1,0], [0])
    vector<int> bits1 = {1, 0, 0};
    cout << "Input: [1, 0, 0], Result: " << (sol.isOneBitCharacter(bits1) ? "true" : "false") << " (Expected: true)" << endl;

    // Test Case 2: [1, 1, 1, 0] -> Expected: false (Parsed as [1,1], [1,0])
    vector<int> bits2 = {1, 1, 1, 0};
    cout << "Input: [1, 1, 1, 0], Result: " << (sol.isOneBitCharacter(bits2) ? "true" : "false") << " (Expected: false)" << endl;

    // Test Case 3: [0] -> Expected: true
    vector<int> bits3 = {0};
    cout << "Input: [0], Result: " << (sol.isOneBitCharacter(bits3) ? "true" : "false") << " (Expected: true)" << endl;

    // Test Case 4: [1, 1, 0] -> Expected: false (Parsed as [1,1], [0] - Wait, [1,1] is a 2-bit char, last '0' is free.
    // The problem constraint is that the '1' must be the start of a 2-bit char.
    // [1, 1, 0] -> [1,1] (2-bit), [0] (1-bit). Trailing '1's = 1 (odd). Result must be FALSE.
    // Wait, the decoding must be valid. The greedy analysis works:
    // [1, 1, 0] -> Trailing 1s: 1. Odd count forces the final '0' to pair with the '1'. (1,0) is a 2-bit char. The last bit is the second bit. FALSE.
    vector<int> bits4 = {1, 1, 0};
    cout << "Input: [1, 1, 0], Result: " << (sol.isOneBitCharacter(bits4) ? "true" : "false") << " (Expected: false)" << endl;

    return 0;
}