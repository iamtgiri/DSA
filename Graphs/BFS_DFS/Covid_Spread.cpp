/*
File: Covid_Spread.cpp
Date: 2025-10-26 10:34

Problem: Covid Spread
Link: https://www.geeksforgeeks.org/problems/covid-spread--141631/1

Problem Statement:
Given a 2D grid representing a hospital ward where 0 is an empty bed, 1 is a 
healthy patient, and 2 is an infected patient. An infected patient spreads the 
virus to adjacent healthy patients (up, down, left, right) in one unit of time.
Find the minimum time required to infect all healthy patients. If it's impossible, 
return -1.

-------------------------------------------------
❌ Brute Force
- Idea: Simulate the spread minute by minute. In each time unit, iterate through 
  the entire grid to find all newly infected patients from the previous step. 
  Repeat until no new patients are infected.
- Time complexity: O(T * R * C), where T is the maximum possible time (up to R*C).
- Space complexity: O(1) auxiliary space (if modifying the grid in place).
- Limitations: Can be inefficient if the maximum time T is large.

✅ Optimized Approachs
- Idea: This is a shortest path problem (minimum time to reach all 1s from the 
  nearest 2). Multi-source BFS is the ideal technique to solve this.
- Approach: Multi-Source Breadth-First Search (BFS).
- Algorithm:
    1. **Initialization:** Count total healthy patients (`uninfected`). Initialize 
       a queue with coordinates of all initially infected patients (2s).
    2. **BFS Traversal:** Process the queue layer by layer (time unit by time unit).
        a. Use the queue size at the start of a layer to delimit the current time step.
        b. For each infected patient, check its four neighbors. If a neighbor is 
           a healthy patient (1), infect them (change to 2), decrement 
           `uninfected` count, and add them to the queue.
        c. If any new patient was infected in this layer, increment the time.
    3. **Result:** After the queue is empty, if `uninfected` is 0, return `time`. 
       Otherwise, return -1.
- Time complexity: O(R * C). Each cell is visited and processed exactly once.
- Space complexity: O(R * C) to store the queue in the worst case.

💡 Key Pattern:
- **Multi-Source BFS:** Used for finding the shortest time/distance from any of 
  multiple starting points (all initial 2s) to all reachable targets (all 1s).

ℹ️ Keywords:
- BFS, Multi-Source, Grid Traversal, Shortest Time, Matrix.

🗒️ Notes
- The BFS structure naturally handles the "minimum time" requirement by processing 
  neighbors layer by layer.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the minimum time required to infect all healthy patients.
     * @param hospital The 2D grid representing the hospital ward.
     * @return Minimum time, or -1 if not all patients can be infected.
     */
    int helpaterp(vector<vector<int>> hospital) {
        int r = hospital.size(); // Number of rows
        int c = hospital[0].size(); // Number of columns
        
        // Queue stores {row, col} for infected patients (sources for BFS)
        queue<pair<int, int>> infected;
        int uninfected = 0, time = 0;
        
        // Step 1: Initialization (Find initial sources and total healthy count)
        for(int i = 0; i < r; ++i) {
           for(int j = 0; j < c; ++j) {
                if(hospital[i][j] == 1) {
                    ++uninfected; // Count healthy patients
                } else if(hospital[i][j] == 2) {
                    infected.push({i, j}); // Initialize BFS queue with infected
                }
           } 
        }
        
        // Directions for movement: Right, Down, Left, Up
        int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        // Step 2: BFS Traversal (Layer-by-Layer)
        while(!infected.empty()) {
             // Size of the queue at the start of the level is the number of 
             // patients spreading the infection in this time unit.
            int size = infected.size();
            bool newInfection = false; // Flag to check if any infection occurred
            
            for(int i = 0; i < size; ++i) {
                auto [x, y] = infected.front();
                infected.pop();
                
                // Spread infection to 4 adjacent neighbors
                for(auto d : dir) {
                    int nx = x + d[0];
                    int ny = y + d[1];
                    
                    // Check bounds and if the neighbor is a healthy patient (1)
                    if(nx >= 0 && nx < r && ny >= 0 && ny < c && hospital[nx][ny] == 1) {
                        hospital[nx][ny] = 2; // Infect the patient
                        infected.push({nx, ny}); // Add to the next time layer
                        uninfected--; // Decrement healthy count
                        newInfection = true; // Mark that infection spread this round
                    }
                }
            }
            // Increment time only if the infection successfully spread in this round
            if(newInfection) {
                ++time;
            }
        }

        // Step 3: Result
        // If uninfected > 0, some healthy patients were unreachable.
        return uninfected ? -1 : time; 
    }

};

// Helper function for clearer test output
template <typename T>
void printVectorOfVectors(const vector<vector<T>>& grid) {
    cout << "[\n";
    for (const auto& row : grid) {
        cout << "  [";
        for (size_t j = 0; j < row.size(); ++j) {
            cout << row[j] << (j == row.size() - 1 ? "" : ", ");
        }
        cout << "]\n";
    }
    cout << "]";
}

int main() {
    Solution sol;
    
    cout << "--- Covid Spread (Multi-Source BFS) ---\n";

    // Test Case 1: Simple spread
    // Should take 2 units of time.
    vector<vector<int>> hospital1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    int result1 = sol.helpaterp(hospital1);
    cout << "Test 1 | Initial Grid: "; printVectorOfVectors(hospital1);
    cout << "\nResult: " << result1 << " (Expected: 2)\n";
    cout << "--------------------------------\n";
    
    // Test Case 2: Impossible to infect (separated by empty beds 0)
    // Should return -1.
    vector<vector<int>> hospital2 = {
        {1, 1, 0},
        {0, 0, 0},
        {0, 1, 2}
    };
    int result2 = sol.helpaterp(hospital2);
    cout << "Test 2 | Initial Grid: "; printVectorOfVectors(hospital2);
    cout << "\nResult: " << result2 << " (Expected: -1)\n";
    cout << "--------------------------------\n";

    // Test Case 3: All infected initially
    // Should return 0.
    vector<vector<int>> hospital3 = {
        {2, 2},
        {2, 2}
    };
    int result3 = sol.helpaterp(hospital3);
    cout << "Test 3 | Initial Grid: "; printVectorOfVectors(hospital3);
    cout << "\nResult: " << result3 << " (Expected: 0)\n";
    cout << "--------------------------------\n";
    
    // Test Case 4: Single patient, needs 4 time units
    vector<vector<int>> hospital4 = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 2, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };
    int result4 = sol.helpaterp(hospital4);
    cout << "Test 4 | Initial Grid: "; printVectorOfVectors(hospital4);
    cout << "\nResult: " << result4 << " (Expected: 4)\n";
    cout << "--------------------------------\n";


    return 0;
}
