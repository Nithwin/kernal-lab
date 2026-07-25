# 🔒 Process Synchronization — Interview Questions & Answers

> These questions cover mutexes, semaphores, deadlocks, and classic synchronization problems — essential topics for OS interviews.

---

## Q1. What is a Race Condition?

**Answer:**
A **race condition** occurs when two or more threads access **shared data concurrently**, and the final result depends on the **unpredictable order** of execution.

```
Thread A: read counter (0) → add 1 → write (1)
Thread B: read counter (0) → add 1 → write (1)

Expected result: 2
Actual result: 1 (Thread B overwrote Thread A's work)
```

**Solution:** Use synchronization primitives (mutex, semaphore) to ensure only one thread accesses the shared resource at a time.

---

## Q2. What is a Critical Section?

**Answer:**
The **critical section** is the part of a program where shared resources are accessed. The critical section must satisfy three conditions:

1. **Mutual Exclusion** — Only one process can be in the critical section at a time.
2. **Progress** — If no process is in the critical section, the selection of the next process to enter must not be postponed indefinitely.
3. **Bounded Waiting** — There is a limit on how many times other processes can enter the critical section before a waiting process gets its turn.

---

## Q3. What is the difference between a Mutex and a Semaphore?

**Answer:**

| Feature | Mutex | Semaphore |
|---------|-------|-----------|
| Value | Binary (locked/unlocked) | Integer (0 to N) |
| Ownership | Only the locking thread can unlock | Any thread can signal |
| Purpose | Protect **one** resource | Control access to **N** resources |
| Analogy | Bathroom lock | Parking lot counter |

```
Mutex: Only 1 thread in the critical section
Semaphore(3): Up to 3 threads can access simultaneously
```

**Key interview point:** A **binary semaphore** (value 0 or 1) behaves similarly to a mutex, but **without ownership** — any thread can release it.

---

## Q4. What is a Deadlock? What are the four necessary conditions?

**Answer:**
A **deadlock** is a situation where two or more processes are **waiting for each other** to release resources, and none can proceed.

**Coffman's Four Necessary Conditions** (ALL must hold for deadlock to occur):

| Condition | Meaning |
|-----------|---------|
| 1. **Mutual Exclusion** | At least one resource is non-shareable |
| 2. **Hold and Wait** | A process holds resources while waiting for others |
| 3. **No Preemption** | Resources cannot be forcibly taken away |
| 4. **Circular Wait** | A circular chain of processes exists, each waiting for the next |

```
Deadlock Example:
  Process A holds Resource 1, waits for Resource 2
  Process B holds Resource 2, waits for Resource 1
  
  A → waits for → B → waits for → A  (Circular Wait!)
```

---

## Q5. How can you prevent deadlock?

**Answer:**
Break any **one** of the four Coffman conditions:

| Condition to Break | Strategy |
|-------------------|----------|
| Mutual Exclusion | Make resources shareable (not always possible) |
| Hold and Wait | Request all resources at once before starting |
| No Preemption | Allow OS to forcibly take resources |
| Circular Wait | **Resource ordering** — always request resources in a fixed order |

Our Dining Philosophers solution uses `std::scoped_lock` which internally breaks circular wait by locking all resources atomically.

---

## Q6. What is the Banker's Algorithm?

**Answer:**
The **Banker's Algorithm** is a deadlock **avoidance** algorithm. Before granting a resource request, the OS checks if the system will remain in a **safe state**.

**Safe State:** A state where there exists at least one sequence of processes that can all finish without deadlock.

```
Available: [3, 3, 2]

Process  Max Need  Allocated  Still Needs
P0       [7,5,3]   [0,1,0]    [7,4,3]
P1       [3,2,2]   [2,0,0]    [1,2,2]
P2       [9,0,2]   [3,0,2]    [6,0,0]

Safe sequence: P1 → P0 → P2 ← System is in a safe state ✅
```

---

## Q7. Explain the Producer-Consumer Problem.

**Answer:**
**Two types of processes** share a bounded buffer:
- **Producer:** Creates items and puts them in the buffer
- **Consumer:** Removes items from the buffer

**Constraints:**
- Producer must wait if buffer is **full**
- Consumer must wait if buffer is **empty**
- Both must not access the buffer simultaneously

**Solution:** Use a mutex (for buffer access) + two semaphores or condition variables (for full/empty signaling).

```
Pseudocode:
  Producer:                        Consumer:
    produce(item)                    wait(full)      // Wait if empty
    wait(empty)    // Wait if full   wait(mutex)     // Lock buffer
    wait(mutex)    // Lock buffer    item = buffer.pop()
    buffer.push(item)                signal(mutex)   // Unlock
    signal(mutex)  // Unlock         signal(empty)   // Signal producer
    signal(full)   // Signal consumer  consume(item)
```

---

## Q8. Explain the Dining Philosophers Problem and its solutions.

**Answer:**
5 philosophers sit at a round table with 5 forks. Each needs 2 forks (left and right) to eat. They alternate between thinking and eating.

**Problem:** If all philosophers pick up their left fork simultaneously, deadlock occurs (circular wait).

**Solutions:**

| Solution | How |
|----------|-----|
| Resource hierarchy | Always pick lower-numbered fork first |
| Limit diners | Allow only 4 to sit at once (semaphore) |
| Atomic acquisition | Lock both forks at once (`scoped_lock`) |
| Asymmetric | Even→left first, Odd→right first |

---

## Q9. What is a Spinlock? When is it better than a Mutex?

**Answer:**

| Feature | Spinlock | Mutex |
|---------|----------|-------|
| Waiting | **Busy-waits** (loops checking the lock) | **Sleeps** (blocks the thread) |
| CPU Usage | Wastes CPU while waiting | No CPU waste while waiting |
| Context Switch | None | Required (expensive) |
| Best for | Very short critical sections | Long critical sections |

**Rule of Thumb:** Use a spinlock when the critical section is **shorter than a context switch** (microseconds). Use a mutex for anything longer.

---

## Q10. What is Priority Inversion? How is it solved?

**Answer:**
**Priority Inversion** occurs when a high-priority process is blocked waiting for a resource held by a low-priority process, while a medium-priority process runs instead.

```
  High Priority (H)  → Needs Resource R (held by L) → BLOCKED
  Medium Priority (M) → Runs instead of H          → UNFAIR!
  Low Priority (L)    → Holds Resource R            → Can't finish because M runs
```

**Famous example:** Mars Pathfinder bug (1997) — a priority inversion caused the rover to repeatedly reset.

**Solutions:**
- **Priority Inheritance:** Temporarily boost L's priority to H's level so L can finish quickly.
- **Priority Ceiling:** Set the resource's priority to the highest possible requester.

---

## Q11. What is a Condition Variable? How is it different from a Semaphore?

**Answer:**

| Feature | Condition Variable | Semaphore |
|---------|-------------------|-----------|
| Has state? | No (stateless signal) | Yes (integer counter) |
| If signal sent with no waiter | Signal is **lost** | Counter is **incremented** (remembered) |
| Usage | Wait for a **condition** to be true | Control access to **N** resources |
| Needs mutex? | Yes, always paired with a mutex | No |

```cpp
// Condition Variable pattern:
std::unique_lock<std::mutex> lock(mtx);
cv.wait(lock, []{ return condition; });  // Sleep until condition is true
// ... do work ...
cv.notify_one();  // Wake up one waiter
```

---

## Q12. What are the differences between `lock_guard`, `unique_lock`, and `scoped_lock` in C++?

**Answer:**

| Feature | `lock_guard` | `unique_lock` | `scoped_lock` |
|---------|-------------|---------------|---------------|
| Locks | 1 mutex | 1 mutex | Multiple mutexes |
| Unlock early? | ❌ No | ✅ Yes | ❌ No |
| Works with CV? | ❌ No | ✅ Yes | ❌ No |
| Deadlock-safe? | N/A | Manual | ✅ Yes (uses `std::lock`) |
| Use when | Simple locking | Need flexibility | Locking multiple mutexes |

```cpp
// lock_guard: Simple, one mutex
std::lock_guard<std::mutex> lock(mtx);

// unique_lock: Flexible, needed for condition_variable
std::unique_lock<std::mutex> lock(mtx);
cv.wait(lock, predicate);

// scoped_lock: Lock multiple mutexes without deadlock
std::scoped_lock lock(mutex1, mutex2, mutex3);
```
