/**
 * @file mutex_demo.cpp
 * @brief Demonstrates how a Mutex prevents Race Conditions.
 *
 * THE PROBLEM:
 *   Two threads both increment a shared counter 100,000 times each.
 *   Without synchronization, the final value is unpredictable because
 *   both threads can read/write the counter simultaneously (race condition).
 *
 * THE SOLUTION:
 *   A std::mutex ensures only one thread can access the counter at a time.
 *   std::lock_guard is an RAII wrapper — it locks in the constructor and
 *   automatically unlocks in the destructor (even if an exception occurs).
 *
 * EXPECTED OUTPUT:
 *   Counter = 200000  (always correct with the mutex)
 *
 * TRY THIS:
 *   Comment out the lock_guard line and run again. You'll see the counter
 *   is less than 200000, proving the race condition exists.
 *
 * BUILD & RUN:
 *   cmake -B build -S . && cmake --build build && ./build/test_sync_mutex
 */

#include <iostream>
#include <thread>
#include <mutex>

// A mutex (MUTual EXclusion) — only one thread can lock it at a time.
std::mutex mutexCounter;

// Shared resource — both threads will increment this.
int counter = 0;

/**
 * @brief Increments the shared counter 100,000 times.
 *
 * Each increment is protected by a lock_guard, which:
 *   1. Locks the mutex when created (entering critical section)
 *   2. Unlocks the mutex when destroyed (leaving critical section)
 */
void increment()
{
    for (int i = 0; i < 100000; i++)
    {
        // lock_guard: Acquires the lock here. Released at end of scope (}).
        std::lock_guard<std::mutex> lock(mutexCounter);

        // CRITICAL SECTION — only one thread executes this at a time.
        counter++;

    }
}

int main()
{
    // Create two threads, both running the increment function.
    std::thread t1(increment);
    std::thread t2(increment);

    // Wait for both threads to finish before reading the result.
    t1.join();
    t2.join();

    // With the mutex, this is guaranteed to be 200000.
    std::cout << "Counter = " << counter << std::endl;
}