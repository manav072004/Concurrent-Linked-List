#include <iostream>
#include <thread>
#include <vector>
#include "ConcurrentLinkedList.h"

// Function that runs in each thread, performing inserts into the concurrent linked list.
void concurrentInsert(ConcurrentLinkedList& list, int numInserts, int threadId) {
    for (int i = 0; i < numInserts; ++i) {
        // Each thread inserts unique values based on threadId and iteration count.
        list.insert(threadId * 1000 + i, threadId);
    }
}

int main() {
    const int numThreads = 4;  // Number of threads performing inserts.
    const int numInserts = 10; // Number of inserts per thread.

    ConcurrentLinkedList list;  // Create an instance of the concurrent linked list.
    std::vector<std::thread> threads;  // Vector to store the threads.

    // Create threads for concurrent insert operations.
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(concurrentInsert, std::ref(list), numInserts, i));
    }

    // Wait for all threads to finish their operations.
    for (auto& t : threads) {
        t.join();
    }

    // Print the final linked list after all threads have completed their insertions.
    list.print();

    return 0;
}