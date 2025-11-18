"""
File: 1-bit_and_2-bit_Characters.py
Date: 2025-11-19 00:24

Problem: 1-bit and 2-bit Characters
Link: https://leetcode.com/problems/1-bit-and-2-bit-characters/description/

Problem Statement:
We have two special characters:
1. A 1-bit character encoded as '0'.
2. A 2-bit character encoded as '10' or '11' (starts with '1').
Given a string of bits that always ends with a '0' (the array 'bits'), determine if the final '0' must be a 1-bit character.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Standard Dynamic Programming (DP) or Recursive approach. Start from the beginning (index 0) and use DP[i] to determine if index 'i' is a valid start of a character.
- Time complexity: O(N)
- Space complexity: O(N) for the DP array/memoization table.
- Limitations: More complex than necessary, as the final state depends only on the suffix.

Current/Optimized Approach
- Idea: The status of the final '0' (as a standalone 1-bit character or the second part of a 2-bit character) is determined solely by the number of consecutive '1's immediately preceding it.
- Approach: **Greedy Suffix Analysis / Linear Scan**
- Algorithm:
  1. Initialize an index `i` to the second-to-last position (`len(bits) - 2`).
  2. Count the number of consecutive **trailing ones** (`count`) by iterating backward while `bits[i]` is 1.
  3. The result is **True** if the `count` of trailing ones is **even** (e.g., 0, 2, 4). An even count means the '1's can be paired up perfectly into 2-bit characters, leaving the final '0' to be a free 1-bit character.
  4. The result is **False** if the `count` of trailing ones is **odd** (e.g., 1, 3, 5). An odd count means the last remaining '1' must pair with the final '0' (since the final '0' must belong to *some* character), forcing the final '0' to be the second bit of a 2-bit character ('10').
- Time complexity: O(N) (Single backward pass).
- Space complexity: O(1) auxiliary space.

💡 Key Pattern:
- **Greedy Parity Check:** When decoding a string where one symbol can take 1 or 2 units and the other takes 1 unit, the final outcome often simplifies to checking the parity (even/odd) of the ambiguous symbols in the suffix.

ℹ️ Keywords:
- Greedy Algorithm, Suffix Analysis, Parity, Linear Scan, Ambiguity Resolution.

🗒️ Notes
- This greedy approach works because the '0' character is unambiguous (always 1-bit). Ambiguity only arises from the '1' characters, which can start a 2-bit sequence.
-------------------------------------------------
"""

from typing import List, Optional, Any

class Solution:
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        # Start checking from the second-to-last bit.
        i = len(bits) - 2
        count = 0
        
        # Count consecutive trailing '1's
        while i >= 0 and bits[i] == 1:
            count += 1
            i -= 1
            
        # If the count of trailing ones is even (0, 2, 4, ...), 
        # they can be perfectly paired up, leaving the last '0' as a 1-bit char.
        # If the count is odd (1, 3, 5, ...), the last '1' must pair with the final '0'.
        return count % 2 == 0


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: [1, 0, 0] -> Trailing 1s: 0 (Even) -> True
    bits1 = [1, 0, 0]
    print(f"Input: {bits1}, Result: {sol.isOneBitCharacter(bits1)} (Expected: True)")
    
    # Test Case 2: [1, 1, 1, 0] -> Trailing 1s: 3 (Odd) -> False
    bits2 = [1, 1, 1, 0]
    print(f"Input: {bits2}, Result: {sol.isOneBitCharacter(bits2)} (Expected: False)")
    
    # Test Case 3: [0] -> Trailing 1s: 0 (Even) -> True (Base case)
    bits3 = [0]
    print(f"Input: {bits3}, Result: {sol.isOneBitCharacter(bits3)} (Expected: True)")
    
    # Test Case 4: [1, 1, 0] -> Trailing 1s: 1 (Odd) -> False
    bits4 = [1, 1, 0]
    print(f"Input: {bits4}, Result: {sol.isOneBitCharacter(bits4)} (Expected: False)")