# Process Synchronization Module

This module provides practical demonstrations of classic concurrency problems and synchronization mechanisms. 

## Demonstrations

1. **Mutex Demo (`mutex_demo.cpp`)**
   - Shows how race conditions occur when multiple threads increment a counter simultaneously.
   - Uses `std::mutex` and `std::lock_guard` to protect the critical section, ensuring the final counter value is correct.

2. **Semaphore Demo (`semaphore_demo.cpp`)**
   - Demonstrates controlling access to a pool of resources.
   - A `std::counting_semaphore` is used to simulate a parking lot with a fixed number of spaces. Cars (threads) wait if the lot is full and enter when a space opens.

3. **Producer-Consumer Problem (`producer_consumer.cpp`)**
   - Classic multi-process synchronization problem.
   - Producers create items and place them in a buffer; consumers take items out.
   - Uses `std::condition_variable` and `std::unique_lock` to coordinate between producer and consumer threads without active waiting.

4. **Dining Philosophers Problem (`dining_philosophers.cpp`)**
   - Demonstrates issues of deadlock and resource sharing.
   - Five philosophers sit at a table with forks between them. A philosopher needs both forks to eat.
   - We use `std::scoped_lock` to acquire both forks (mutexes) simultaneously, preventing deadlocks (like the classic "everyone picks up the left fork and waits forever" scenario).

## Running Tests
Each of these files is compiled into its own executable, for example: `./build/test_sync_dining`.
