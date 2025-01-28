#define FILTERLOCK_H

#include <vector>
#include <atomic>

// FilterLock class to provide a fair lock mechanism for multithreaded synchronization.
class FilterLock {
public:
    // Constructor initializes lock state for a given number of threads.
    FilterLock(int numThreads);

    // Lock method: thread tries to acquire the lock by following the filter lock protocol.
    void lock(int threadId);

    // Unlock method: releases the lock for the given thread.
    void unlock(int threadId);

private:
    int numThreads;                // Number of threads participating in the lock mechanism.
    std::vector<int> level;        // Array storing the level each thread is trying to acquire.
    std::vector<int> victim;       // Array that tracks the thread that caused a conflict in each level.
};
