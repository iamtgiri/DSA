/*
File: Library_Book_Tracker.cpp
Date: 2025-11-05 00:57

Problem: Library Book Tracker
Problem Statement:
A library maintains an inventory of books divided into categories.
Each book has a category (e.g., Fiction, Science) and a price (value).
Operations: Acquire (A), Checkout (C, remove cheapest), Reclassify (R).

-------------------------------------------------

✅ Approachs
- Idea: We need a data structure that groups books by category,
        and within each category, efficiently tracks book counts
        by price while allowing fast retrieval of the minimum price.
- Approach: Use a nested map structure. Outer map for categories
            and an inner `std::map<int, int>` to store
            {price: count}.
- Algorithm:
    - A/C (Acquire/Checkout) utilize the inner map's sorted keys.
    - C uses `map::begin()` to find the lowest price in O(1) time
      after category lookup.
    - R (Reclassify) iterates and merges all entries from one
      category map to another, then clears the source map.
- Time complexity:
    - A (Acquire): O(log P), where P is the number of unique prices
      in the category.
    - C (Checkout): O(log P), dominated by the category lookup.
      `map::begin()` is O(1).
    - R (Reclassify): O(U_from * log U_to), where U_from and U_to
      are the number of unique prices in the source and destination
      categories.
- Space complexity: O(C * U), where C is the number of categories
                    and U is the total number of unique prices.

💡 Key Pattern:
- Using `std::map` (which keeps keys sorted) as a frequency
  counter allows us to efficiently find the minimum element
  (`map::begin()`) in addition to tracking counts.

ℹ️ Keywords:
- Sorted Map, Frequency Counter, Minimum Element Retrieval,
  Inventory Management, Nested Map.

🗒️ Notes
- `std::map::begin()` always points to the element with the
  smallest key (the cheapest price).
-------------------------------------------------
*/
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Main structure: Category -> {Price -> Count}
// The inner map is sorted by price, cheapest first.
using Inventory = map<string, map<int, int>>;

void process_operations(Inventory &library, const vector<vector<string>> &ops)
{
    for (const auto &op : ops)
    {
        const string &type = op[0];

        if (type == "A")
        { // Acquire (Add)
            const string &cat = op[1];
            int price = stoi(op[2]);
            // Increment count for this price in the category
            library[cat][price]++;
            cout << "[A] Acquired 1 book in " << cat
                 << " at $" << price << endl;
        }
        else if (type == "C")
        { // Checkout (Remove cheapest)
            const string &cat = op[1];

            if (library.count(cat) == 0 || library[cat].empty())
            {
                cout << "[C] Category " << cat
                     << " is empty. Operation ignored.\n";
                continue;
            }

            // Get iterator to the cheapest price (map::begin())
            auto it = library[cat].begin();
            int price = it->first;

            // Decrement the count
            it->second--;
            cout << "[C] Checked out 1 book in " << cat
                 << " at cheapest price $" << price << endl;

            // If count hits zero, remove the price entry entirely
            if (it->second == 0)
            {
                library[cat].erase(it);
            }
        }
        else if (type == "R")
        { // Reclassify (Move all)
            const string &from_cat = op[1];
            const string &to_cat = op[2];

            if (library.count(from_cat) == 0 || library[from_cat].empty())
            {
                cout << "[R] Source category " << from_cat
                     << " is empty. Nothing moved.\n";
                continue;
            }

            // Move all price/count pairs from 'from' to 'to'
            for (const auto &pair : library[from_cat])
            {
                int price = pair.first;
                int count = pair.second;
                library[to_cat][price] += count;
            }

            // Clear the source category
            library[from_cat].clear();
            cout << "[R] Reclassified all books from " << from_cat
                 << " to " << to_cat << endl;
        }
    }
}

void print_inventory(const Inventory &library)
{
    cout << "\n--- FINAL LIBRARY INVENTORY ---\n";
    if (library.empty())
    {
        cout << "The library is empty.\n";
        return;
    }

    for (const auto &[cat, books] : library)
    {
        // Skip categories that exist but are now empty
        if (books.empty())
            continue;

        int total_count = 0;
        for (const auto &[price, count] : books)
        {
            total_count += count;
        }

        cout << "Category: " << cat << " ("
             << total_count << " total books)\n";

        for (const auto &[price, count] : books)
        {
            cout << "  - Price $" << price << ": "
                 << count << " book(s)\n";
        }
    }
    cout << "-------------------------------\n";
}

int main()
{
    // map<string, map<int, int>> library;
    Inventory library;

    // Example operations: Category, Price (for A), or To_Category (for R)
    vector<vector<string>> ops = {
        {"A", "Fiction", "300"},
        {"A", "Fiction", "200"},
        {"A", "Science", "400"},
        {"A", "Science", "150"},
        {"A", "Fiction", "200"},     // Added one more $200 book
        {"C", "Fiction"},            // Checkout cheapest in Fiction ($200)
        {"R", "Science", "Fiction"}, // Move all from Science -> Fiction
        {"C", "Fiction"},            // Checkout cheapest again ($150)
        {"C", "Science"}             // Checkout from now-empty Science
    };

    process_operations(library, ops);

    print_inventory(library);

    return 0;
}
