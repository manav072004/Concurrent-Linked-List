#include "FilterLock.h"

// Constructor initializes the filter lock arrays for a given number of threads.
FilterLock::FilterLock(int numThreads)
    : numThreads(numThreads), level(numThreads, -1), victim(numThreads, -1) {}

// Lock method follows the filter lock protocol to acquire the lock for the thread.
void FilterLock::lock(int threadId) {
    for (int i = 1; i < numThreads; ++i) {
        // Mark the level this thread is trying to acquire.
        level[threadId] = i;
        victim[i] = threadId;

        // Wait until no other thread is at the same level or the victim is not this thread.
        for (int j = 0; j < numThreads; ++j) {
            if (j != threadId) {
                // Busy-wait loop to ensure fairness and prevent starvation.
                while (level[j] >= i && victim[i] == threadId) {
                    // Thread waits here if another thread is at the same level or it's the victim.
                }
            }
        }
    }
}

// Unlock method releases the lock by resetting the level of the thread.
void FilterLock::unlock(int threadId) {
    level[threadId] = -1;  // Reset the level of the thread once it finishes its critical section.
}