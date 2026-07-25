/**
 * @file dining_philosophers.cpp
 * @brief Demonstrates the Dining Philosophers problem and deadlock prevention.
 *
 * THE PROBLEM:
 *   5 philosophers sit around a round table. Between each pair is ONE fork.
 *   A philosopher needs BOTH the left and right fork to eat.
 *
 *   Philosopher 0: needs Fork 0 (left) and Fork 1 (right)
 *   Philosopher 1: needs Fork 1 (left) and Fork 2 (right)
 *   ...
 *   Philosopher 4: needs Fork 4 (left) and Fork 0 (right)
 *
 * THE DEADLOCK SCENARIO (without proper locking):
 *   If every philosopher picks up their LEFT fork first:
 *     P0 grabs Fork 0, P1 grabs Fork 1, P2 grabs Fork 2, P3 grabs Fork 3, P4 grabs Fork 4
 *     Now everyone tries to grab their RIGHT fork... but it's held by their neighbor.
 *     Circular wait → DEADLOCK! Nobody can eat. Everyone starves forever.
 *
 * OUR SOLUTION: std::scoped_lock
 *   scoped_lock acquires BOTH forks ATOMICALLY (all-or-nothing).
 *   It uses an internal deadlock-avoidance algorithm (similar to std::lock)
 *   that tries to lock all mutexes. If it can't get all of them, it releases
 *   what it has and retries. This breaks the circular wait condition.
 *
 * BUILD & RUN:
 *   cmake -B build -S . && cmake --build build && ./build/test_sync_dining
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

// 5 forks, each represented as a mutex (a fork can only be held by one philosopher).
std::mutex forks[5];

/**
 * @brief Simulates a philosopher who thinks and eats 3 times.
 *
 * @param id The philosopher's ID (0-4).
 *
 * Each philosopher:
 *   1. Thinks for 500ms (no forks needed)
 *   2. Picks up BOTH forks atomically using scoped_lock
 *   3. Eats for 500ms
 *   4. Puts down both forks (automatic when scoped_lock goes out of scope)
 *   5. Repeats 3 times
 */
void philosopher(int id)
{
    int left = id;             // Left fork has the same index as the philosopher
    int right = (id + 1) % 5;  // Right fork is the next one (wraps around for P4)

    for (int i = 0; i < 3; i++)
    {
        // THINKING — no resources needed.
        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // EATING — needs both forks.
        // scoped_lock acquires BOTH mutexes atomically.
        // If it can't get both, it releases and retries → NO DEADLOCK!
        std::scoped_lock lock(forks[left], forks[right]);

        std::cout << "Philosopher " << id << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Both forks are automatically released here when scoped_lock
        // goes out of scope (RAII pattern).
    }
}

int main()
{
    // Create 5 philosopher threads.
    std::thread philosophers[5];

    for (int i = 0; i < 5; i++)
        philosophers[i] = std::thread(philosopher, i);

    // Wait for all philosophers to finish eating.
    for (int i = 0; i < 5; i++)
        philosophers[i].join();

    return 0;
}