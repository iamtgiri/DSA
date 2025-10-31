/*
File: Ancestral_Names.cpp
Date: 2025-10-25 18:34

Problem: Ancestral Names
Link: URL

Problem Statement:
Given a list of strings where each string is a name followed by a Roman numeral,
sort the list first by name alphabetically, then by the decimal value of the
Roman numeral. Return the sorted list with the original Roman numerals.


Example:
Input: ['Steven XL', 'Steven XVI', 'David IX', 'Mary XV', 'Mary XIII', 'Mary XX']
Output: ['David IX', 'Mary XIII', 'Mary XV', 'Mary XX', 'Steven XVI', 'Steven XL']
-------------------------------------------------
❌ Brute Force
- Idea: For every pair of strings during the sort, manually compare the name parts. If names
  are equal, iterate through all possible Roman numeral values (I, II, III, ...) to find a match
  for the two Roman numerals being compared to determine their order.
- Time complexity: O(N log N * (R + V)), where N is the number of names, R is the max length of
  the Roman numeral, and V is the maximum Roman value (e.g., 50). The complexity comes from string
  operations and repeated, non-optimized lookups/conversions inside the sort comparison.
- Space complexity: O(1) auxiliary space, excluding recursion stack.
- Limitations: Highly inefficient due to lack of pre-computation and non-optimized comparison logic.

✅ Optimized Approachs
- Idea: Utilize a **custom comparator** with C++'s `std::sort`. The comparator must implement
  the two-level sorting logic: primary sort on name, secondary sort on the decimal value of the
  Roman numeral, which is computed by a fast lookup-based helper function.
- Approach: In-place Sorting with Custom Roman-to-Decimal Comparator.
- Algorithm:
    1. **Implement `romanToDecimal(string)`:** A helper function to convert Roman numerals
       to integers using a hash map for efficient symbol value lookup. It handles subtractive
       notation (e.g., IV, IX) by checking if the current symbol's value is less than the next one.
    2. **Implement `sortRoman(vector<string>&)`:** Use `std::sort` with a lambda function.
    3. **Comparator Logic:** The lambda splits the full name string (`"Name Numeral"`) into
       `namePart` and `romanPart` for both strings (`a` and `b`).
    4. **Primary Key:** If `nameA` is not equal to `nameB`, return the result of the standard
       lexicographical comparison (`nameA < nameB`).
    5. **Secondary Key:** If the names are equal, compare the decimal values obtained from
       `romanToDecimal(romanA)` and `romanToDecimal(romanB)`.
- Time complexity: O(N log N * R). O(N log N) for the sort operation, where each comparison
  involves string splitting and Roman conversion, both of which take time proportional to the
  Roman numeral length (R).
- Space complexity: O(1) auxiliary space (in-place sort).

💡 Key Pattern:
- **Multi-criteria Sorting:** Using a custom comparison function to implement layered sorting logic,
  where comparison moves to the secondary key only when the primary keys are equal.

ℹ️ Keywords:
- Sorting, Custom Comparator, Roman Numerals, String Parsing, Two-level Sort.

🗒️ Notes
- The `romanToDecimal` function here is simplified and optimized for typical ancestral names
  (I to L or so, usually) but works for larger standard Roman numerals too.
- The use of `std::sort` on the reference to the input vector ensures the sort is done in-place.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for Roman numeral mapping (assuming up to L, or 50, is sufficient for typical ancestral names)
// The provided implementation includes mappings up to 1000 (M).
class Solution
{
private:
    // Helper function to convert Roman numeral string to its decimal integer value.
    int romanToDecimal(const string &roman) const
    {
        // Only Roman numerals needed for this problem typically go up to L (50),
        // but providing full map for robustness.
        unordered_map<char, int> romanMap = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

        int n = roman.size();
        int result = 0;
        for (int i = 0; i < n; ++i)
        {
            // Check for subtractive notation (e.g., IV = 4, IX = 9)
            if (i + 1 < n && romanMap[roman[i]] < romanMap[roman[i + 1]])
            {
                // Add the difference (e.g., 5 - 1 = 4)
                result += romanMap[roman[i + 1]] - romanMap[roman[i]];
                ++i; // Skip the next character as it's already processed
            }
            else
            {
                // Add the value of the current symbol
                result += romanMap[roman[i]];
            }
        }
        return result;
    }

public:
    /**
     * @brief Sorts a list of names, first by name alphabetically, then by the decimal value of the Roman numeral.
     * @param names A vector of strings, each containing "Name RomanNumeral". Sorted in-place.
     * @return The sorted vector of strings.
     */
    vector<string> sortRoman(vector<string> &names)
    {
        // Custom comparator for multi-criteria sorting
        sort(names.begin(), names.end(), [this](const string &a, const string &b)
             {
            // 1. Split string A: Find the first space to separate name and numeral
            size_t spaceA = a.find(' ');
            string nameA = a.substr(0, spaceA);
            string romanA = a.substr(spaceA + 1);

            // 2. Split string B
            size_t spaceB = b.find(' ');
            string nameB = b.substr(0, spaceB);
            string romanB = b.substr(spaceB + 1);
            
            // 3. Primary Sort Key: Compare Names Alphabetically
            if (nameA != nameB) {
                return nameA < nameB; // True if A comes before B
            }

            // 4. Secondary Sort Key: If names are equal, compare Roman numeral values
            // We reuse the romanToDecimal helper function.
            return romanToDecimal(romanA) < romanToDecimal(romanB); });

        return names;
    }
};

// --- Helper Functions for Test Cases ---

void printVector(const vector<string> &vec)
{
    cout << "['";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i < vec.size() - 1)
        {
            cout << "', '";
        }
    }
    cout << "']" << endl;
}

int main()
{
    Solution sol;

    cout << "--- Ancestral Names Sorting ---\n";

    // Test Case 1: Example from problem statement
    // Input: ['Steven XL', 'Steven XVI', 'David IX', 'Mary XV', 'Mary XIII', 'Mary XX']
    // Expected: ['David IX', 'Mary XIII', 'Mary XV', 'Mary XX', 'Steven XVI', 'Steven XL']
    vector<string> names1 = {"Steven XL", "Steven XVI", "David IX", "Mary XV", "Mary XIII", "Mary XX"};
    cout << "Test 1 Input: ";
    printVector(names1);
    sol.sortRoman(names1);
    cout << "Test 1 Output: ";
    printVector(names1);
    cout << "--------------------------------\n";

    // Test Case 2: Only Roman numeral sorting needed
    // Input: ['George I', 'George V', 'George II']
    // Expected: ['George I', 'George II', 'George V']
    vector<string> names2 = {"George I", "George V", "George II"};
    cout << "Test 2 Input: ";
    printVector(names2);
    sol.sortRoman(names2);
    cout << "Test 2 Output: ";
    printVector(names2);
    cout << "--------------------------------\n";

    // Test Case 3: Only name sorting needed
    // Input: ['Zoe III', 'Adam II', 'Beth I']
    // Expected: ['Adam II', 'Beth I', 'Zoe III']
    vector<string> names3 = {"Zoe III", "Adam II", "Beth I"};
    cout << "Test 3 Input: ";
    printVector(names3);
    sol.sortRoman(names3);
    cout << "Test 3 Output: ";
    printVector(names3);
    cout << "--------------------------------\n";

    // Test Case 4: Larger Romans (up to L/50, in this case XL=40)
    // Input: ['King XL', 'King XX', 'King L']
    // Expected: ['King XX', 'King XL', 'King L'] (20, 40, 50)
    vector<string> names4 = {"King XL", "King XX", "King L"};
    cout << "Test 4 Input: ";
    printVector(names4);
    sol.sortRoman(names4);
    cout << "Test 4 Output: ";
    printVector(names4);
    cout << "--------------------------------\n";

    return 0;
}
