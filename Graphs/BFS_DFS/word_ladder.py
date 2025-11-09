"""
File: word_ladder.py
Date: 2025-11-09 21:13

Problem: Word Ladder
Link: https://leetcode.com/problems/word-ladder/description/

Problem Statement:
Given two words (beginWord and endWord), and a dictionary's word list, find 
the length of the shortest transformation sequence from beginWord to endWord,
such that:
1. Only one letter can be changed at a time.
2. Each transformed word must exist in the word list.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Try all possible permutations of words.
- Time complexity: Exponential.
- Space complexity: O(N)
- Limitations: Impractical for larger word lists.

Current/Optimized Approach
- Idea: Use Breadth-First Search (BFS) to find the shortest path in an
  unweighted graph.
- Approach: BFS
- Algorithm:
  1. Convert wordList to a set.
  2. Use a queue (deque) to store (word, steps).
  3. Generate all one-letter neighbors; if valid, mark as visited (by
     removing from set) and enqueue. Stop when endWord is found.
- Time complexity: O(L^2 * N), where L is word length, N is list size.
  (L positions * 25 changes * N words)
- Space complexity: O(L * N) for the word set and the queue.

💡 Key Pattern:
- Shortest path in an unweighted graph -> BFS.

ℹ️ Keywords:
- BFS, Shortest Path, Graph Traversal, Transformation.

🗒️ Notes
- Used `collections.deque` for O(1) queue operations.
- Removing words from the set marks them as visited.
-------------------------------------------------
"""

from typing import List, Any
from collections import deque

class Solution:
    def Word_Ladder(
        self,
        beginWord: str,
        endWord: str,
        wordList: List[str]
    ) -> int:
        """
        Finds the length of the shortest transformation sequence using BFS.

        Args:
            beginWord (str): The starting word.
            endWord (str): The target word.
            wordList (List[str]): The dictionary of valid words.

        Returns:
            int: The length of the shortest sequence, or 0 if none exists.
        """
        # Convert list to a set for O(1) average time lookups
        word_set = set(wordList)
        if endWord not in word_set:
            return 0

        # Queue stores tuples of (word, steps)
        queue = deque([(beginWord, 1)])
        L = len(beginWord)
        
        while queue:
            # Use popleft for O(1) dequeue operation
            word, steps = queue.popleft() 
            
            if word == endWord:
                return steps

            # Iterate through all possible one-letter transformations
            for i in range(L):
                for c in 'abcdefghijklmnopqrstuvwxyz':
                    # Create the new word string
                    new_word = word[:i] + c + word[i+1:]
                    
                    if new_word in word_set:
                        # Found an unvisited word in the dictionary
                        word_set.remove(new_word) # Mark as visited
                        queue.append((new_word, steps + 1))

        return 0


if __name__ == "__main__":
    sol = Solution()
    
    # Example 1
    beginWord1 = "hit"
    endWord1 = "cog"
    wordList1 = ["hot", "dot", "dog", "lot", "log", "cog"]
    result1 = sol.Word_Ladder(beginWord1, endWord1, wordList1)
    print(f"Example 1: {beginWord1} -> {endWord1} = {result1}")
    # Expected output: 5 (hit -> hot -> dot -> dog -> cog)

    # Example 2 (No solution)
    beginWord2 = "hit"
    endWord2 = "cog"
    wordList2 = ["hot", "dot", "dog", "lot", "log"]
    result2 = sol.Word_Ladder(beginWord2, endWord2, wordList2)
    print(f"Example 2: {beginWord2} -> {endWord2} = {result2}")
    # Expected output: 0

    # Example 3 (Shortest path is 2)
    beginWord3 = "a"
    endWord3 = "c"
    wordList3 = ["a", "b", "c"]
    result3 = sol.Word_Ladder(beginWord3, endWord3, wordList3)
    print(f"Example 3: {beginWord3} -> {endWord3} = {result3}")
    # Expected output: 2