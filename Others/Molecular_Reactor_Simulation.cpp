/*
File: Molecular_Reactor_Simulation.cpp
Date: 2025-11-05 01:04

Problem: Molecular Reactor Simulation

Problem Statement:
A molecular reactor processes incoming samples one by one.
Each sample takes 300 seconds to process.

There is a cooling chamber that can hold a maximum of 10 samples
waiting to be processed.
When a new sample arrives:
If there are fewer than 10 waiting, the sample is accepted.
If the chamber already has 10 waiting, the sample is rejected.
A sample starts processing as soon as the reactor becomes free.

Given the arrival times of all samples, determine the time when the
last accepted sample finishes processing.
-------------------------------------------------
❌ Brute Force
- Idea: A simple simulation is inherently efficient here.
        Brute force is not meaningfully distinct from this approach.
- Time complexity: O(N)
- Space complexity: O(N)
- Limitations: None significant for this problem structure.

✅ Optimized Approachs
- Idea: Simulate the queue and reactor status using a
        First-In-First-Out (FIFO) queue structure.
- Approach: Use `std::queue<int>` to store the **finish times** of samples currently in the system (waiting or
            processing). This represents the cooling chamber.
- Algorithm:
    1. For each arrival time `t`, dequeue samples whose finish
       time (`chamber.front()`) is <= `t` (they are complete).
    2. If chamber size < 10, the sample is accepted.
    3. Calculate the sample's start time: `max(t, reactor_finish)`.
    4. Calculate its finish time: `start_time + 300`.
    5. Update `reactor_finish`, push the new finish time to the
       chamber, and update `last_finish`.
- Time complexity: O(N), where N is the number of samples. Each
                   sample is processed and enqueued/dequeued once.
- Space complexity: O(1) for the `chamber` queue (max size 10)
                    and O(N) for the input arrival times.

💡 Key Pattern:
- **Single-Server Queue Simulation:** Tracking the server's
  (reactor's) availability time (`reactor_finish`) and using a
  queue to manage limited waiting capacity.

ℹ️ Keywords:
- Queue, Simulation, FIFO, Reactor, Limited Buffer, Time Complexity.

🗒️ Notes
- The `chamber` queue stores finish times, which effectively lets
  us check how many slots are occupied *at the moment of arrival* (`t`).
- The condition `chamber.front() <= t` correctly removes items
  that have finished processing by time `t`.
-------------------------------------------------
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    // Disable synchronization for faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Example input: arrival times of samples (in seconds)
    vector<int> arrivals = {0, 50, 100, 150, 200, 250, 300, 350,
                            400, 450, 500, 550, 600, 650, 700};

    const int PROCESS_TIME = 300; // each sample takes 300s
    const int MAX_QUEUE = 10;     // chamber capacity

    // Stores finish times of accepted samples (waiting or processing)
    queue<int> chamber;
    // Time the reactor becomes free from the *last* sample assigned
    int reactor_finish = 0;
    // Finish time of the *last* accepted sample overall
    int last_finish = 0;

    for (int t : arrivals)
    {
        // 1. Remove samples that have finished processing by time 't'
        while (!chamber.empty() && chamber.front() <= t)
            chamber.pop();

        // 2. Check if the chamber has space (MAX_QUEUE = 10)
        if ((int)chamber.size() < MAX_QUEUE)
        {
            // Sample is accepted

            // Starts processing when it arrives (t) OR when the
            // reactor is free (reactor_finish), whichever is later.
            int start_time = max(t, reactor_finish);

            // Calculate when this sample will finish
            int finish_time = start_time + PROCESS_TIME;

            // Update state
            chamber.push(finish_time);
            reactor_finish = finish_time;
            last_finish = finish_time;

            // Optional: Print status
            // cout << "T=" << t << ": Accepted, Finishes at "
            //      << finish_time << endl;
        }
        // else: sample rejected
    }

    cout << "Last accepted sample finishes at: "
         << last_finish << " seconds\n";

    return 0;
}
