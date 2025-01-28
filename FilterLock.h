#pragma once

#include <atomic>
#include <thread>

class FilterLock {
public:
    FilterLock() : numThreads(0), level(nullptr), victim(nullptr) {}

    ~FilterLock() {
        delete[] level;
        delete[] victim;
    }

    void init(int num_threads) {
        numThreads = num_threads;
        level = new std::atomic<int>[numThreads];
        victim = new std::atomic<int>[numThreads];

        for (int x = 0; x < numThreads; x++) {
            level[x].store(0, std::memory_order_relaxed);
            victim[x].store(0, std::memory_order_relaxed);
        }
    }

    void lock(int thread_id) {
        for (int x = 1; x < numThreads; x++) {
            level[thread_id].store(x, std::memory_order_release);  // Release at this level
            victim[x].store(thread_id, std::memory_order_relaxed);  // Mark this thread as the victim for this level

            // Ensure that a higher level thread is not competing
            for (int y = 0; y < numThreads; y++) {
                while (y != thread_id && level[y].load(std::memory_order_acquire) >= x && victim[x].load(std::memory_order_relaxed) == thread_id) {
                    std::this_thread::yield();  // Yield CPU if lock can't be acquired
                }
            }
        }
    }

    void unlock(int thread_id) {
        level[thread_id].store(0, std::memory_order_release);  // Set thread's level to 0 to release the lock
    }

private:
    int numThreads;  // Number of threads
    std::atomic<int>* level;   // Atomic array for tracking each thread's level
    std::atomic<int>* victim;  // Atomic array for tracking the victim at each level
};