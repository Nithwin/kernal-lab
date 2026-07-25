# 🔒 Process Synchronization Module

> **Source Code:** [`src/synchronization/`](../src/synchronization/) · **Tests:** `./build/test_sync_*`

## What is Process Synchronization?

When multiple processes (or threads) access **shared resources** (variables, files, memory) at the same time, things can go wrong. Process synchronization ensures that concurrent access doesn't corrupt data.

### The Race Condition Problem

A **race condition** occurs when the outcome depends on the unpredictable order in which threads execute.

```
  Shared Variable: counter = 0
  
  Thread A                          Thread B
  ─────────                         ─────────
  read counter (0)                  
                                    read counter (0)
  counter = 0 + 1 = 1              
                                    counter = 0 + 1 = 1
  write counter (1)                 
                                    write counter (1)
  
  Expected: counter = 2
  Actual:   counter = 1  ← BUG! 🐛
```

Both threads read the **old value** before either could write. This is a classic race condition.

### The Critical Section

A **critical section** is the part of code that accesses shared resources. We need to ensure:

```
  ┌──────────────────────────────────────────────────┐
  │  CRITICAL SECTION REQUIREMENTS                   │
  │                                                  │
  │  1. Mutual Exclusion   → Only one thread at a    │
  │                          time in the section      │
  │  2. Progress           → If no one is in the     │
  │                          section, someone can     │
  │                          enter without delay      │
  │  3. Bounded Waiting    → No thread waits forever │
  └──────────────────────────────────────────────────┘
```

---

## Demo 1: Mutex (Mutual Exclusion)

> 📂 **Code:** [`src/synchronization/mutex_demo.cpp`](../src/synchronization/mutex_demo.cpp) · **Run:** `./build/test_sync_mutex`

### What is a Mutex?

A **mutex** (mutual exclusion) is like a **lock on a bathroom door**. Only one person (thread) can be inside at a time. Others must wait.

```
  Thread A              Mutex              Thread B
  ────────              ─────              ────────
  lock() ───────► 🔒 LOCKED
  
  [uses counter]                           lock() → BLOCKED ⏳
  
  unlock() ──────► 🔓 UNLOCKED ──────────► UNBLOCKED → enters
  
                                           [uses counter]
  
                                           unlock() → 🔓 UNLOCKED
```

### Our Code Explained

```cpp
std::mutex mutexCounter;  // The lock
int counter = 0;          // Shared resource

void increment() {
    for (int i = 0; i < 100000; i++) {
        // lock_guard: Locks on creation, unlocks when scope ends
        std::lock_guard<std::mutex> lock(mutexCounter);
        counter++;  // SAFE — only one thread at a time
    }
    // lock automatically released here (RAII pattern!)
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join(); t2.join();
    // counter is guaranteed to be 200000 ✅
}
```

### Key C++ Concepts
- `std::mutex` — The lock primitive
- `std::lock_guard` — RAII wrapper: locks in constructor, unlocks in destructor
- **RAII (Resource Acquisition Is Initialization)** — Ensures cleanup even if exceptions occur

### Expected Output
```
Counter = 200000
```
Without the mutex, you'd see random values like 134829, 187421, etc.

---

## Demo 2: Semaphore

> 📂 **Code:** [`src/synchronization/semaphore_demo.cpp`](../src/synchronization/semaphore_demo.cpp) · **Run:** `./build/test_sync_semaphore`

### What is a Semaphore?

A **semaphore** is like a **parking lot counter**. It tracks how many "slots" are available:
- `acquire()` → Take a slot (decrement counter). If counter = 0, **wait**.
- `release()` → Return a slot (increment counter). Wake up a waiting thread.

```
  Parking Lot (capacity = 3)
  
  Semaphore count: 3
  
  Car 1 arrives → acquire() → count = 2 → 🅿️ PARKED
  Car 2 arrives → acquire() → count = 1 → 🅿️ PARKED
  Car 3 arrives → acquire() → count = 0 → 🅿️ PARKED
  Car 4 arrives → acquire() → count = 0 → ⏳ WAITING...
  
  Car 1 leaves  → release() → count = 1 → Car 4 enters! 🅿️
```

### Mutex vs Semaphore

| Mutex | Semaphore |
|-------|-----------|
| Binary (locked/unlocked) | Can count to N |
| Only the owner can unlock | Any thread can signal |
| Protects **one resource** | Controls **N resources** |
| Like a bathroom lock | Like a parking lot counter |

### Our Code Explained

```cpp
// Parking lot with 3 spaces
std::counting_semaphore<3> parkingLot(3);

void parkCar(int id) {
    std::cout << "Car " << id << " arrived.\n";
    
    parkingLot.acquire();  // Wait for a free space (blocks if full)
    
    std::cout << "Car " << id << " entered the parking lot.\n";
    
    // Simulate parking for 2-5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(randomDuration));
    
    std::cout << "Car " << id << " left the parking lot.\n";
    
    parkingLot.release();  // Free up the space for another car
}
```

---

## Demo 3: Producer-Consumer Problem

> 📂 **Code:** [`src/synchronization/producer_consumer.cpp`](../src/synchronization/producer_consumer.cpp) · **Run:** `./build/test_sync_producer`

### The Problem

Two types of threads share a **bounded buffer**:
- **Producer** — Creates items and puts them in the buffer
- **Consumer** — Takes items out of the buffer

Rules:
- Producer must **wait** if the buffer is full
- Consumer must **wait** if the buffer is empty
- Both must not access the buffer at the same time

```
  Producer ──► ┌─────────────────────┐ ──► Consumer
               │  [1] [2] [3] [ ] [ ]│
               │     Bounded Buffer  │
               └─────────────────────┘
  
  If full  → Producer waits  ⏳
  If empty → Consumer waits  ⏳
```

### Our Code Explained

```cpp
std::queue<int> buffer;           // Shared bounded buffer
std::mutex mtx;                   // Protects the buffer
std::condition_variable cv;       // Signals between producer/consumer

void producer() {
    for (int i = 1; i <= 5; i++) {
        {
            std::lock_guard<std::mutex> lock(mtx);  // Lock buffer
            buffer.push(i);                          // Produce item
            std::cout << "Produced: " << i << "\n";
        }
        cv.notify_one();  // Wake up consumer: "Hey, there's food!"
    }
}

void consumer() {
    for (int i = 1; i <= 5; i++) {
        std::unique_lock<std::mutex> lock(mtx);  // Lock buffer
        
        // Wait until buffer has items (releases lock while waiting!)
        cv.wait(lock, [] { return !buffer.empty(); });
        
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << "\n";
    }
}
```

### Key C++ Concepts

| Concept | Purpose |
|---------|---------|
| `std::condition_variable` | Allows threads to sleep until a condition is met |
| `cv.wait(lock, predicate)` | Releases lock, sleeps until predicate is true |
| `cv.notify_one()` | Wakes up one waiting thread |
| `std::unique_lock` | Required by `cv.wait()` (more flexible than `lock_guard`) |

### Expected Output
```
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
...
All work completed!
```

---

## Demo 4: Dining Philosophers Problem

> 📂 **Code:** [`src/synchronization/dining_philosophers.cpp`](../src/synchronization/dining_philosophers.cpp) · **Run:** `./build/test_sync_dining`

### The Problem

5 philosophers sit at a round table. Between each pair is **one fork**. A philosopher needs **both the left and right fork** to eat.

```
              P0
           🍴    🍴
        P4          P1
        🍴          🍴
           P3    P2
              🍴
              
  Each philosopher: Think → Pick up forks → Eat → Put down forks → Repeat
```

### The Deadlock Problem

If every philosopher picks up their **left fork first** at the same time:

```
  P0 picks up Fork 0    ✅
  P1 picks up Fork 1    ✅
  P2 picks up Fork 2    ✅
  P3 picks up Fork 3    ✅
  P4 picks up Fork 4    ✅
  
  Now everyone tries to pick up the right fork...
  P0 waits for Fork 1 (held by P1) ⏳
  P1 waits for Fork 2 (held by P2) ⏳
  P2 waits for Fork 3 (held by P3) ⏳
  P3 waits for Fork 4 (held by P4) ⏳
  P4 waits for Fork 0 (held by P0) ⏳
  
  → CIRCULAR WAIT → DEADLOCK! 💀 Everyone starves forever.
```

### Our Solution: `std::scoped_lock`

```cpp
std::mutex forks[5];  // Each fork is a mutex

void philosopher(int id) {
    int left  = id;
    int right = (id + 1) % 5;
    
    for (int i = 0; i < 3; i++) {
        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(500ms);
        
        // scoped_lock acquires BOTH forks atomically — no deadlock!
        std::scoped_lock lock(forks[left], forks[right]);
        
        std::cout << "Philosopher " << id << " is eating.\n";
        std::this_thread::sleep_for(500ms);
        
        // Both forks released automatically at end of scope
    }
}
```

### Why `scoped_lock` Prevents Deadlock

`std::scoped_lock` uses a **deadlock avoidance algorithm** internally. It tries to lock all mutexes at once. If it can't get all of them, it releases whatever it has and retries. This breaks the **circular wait** condition.

### Other Solutions to Dining Philosophers

| Solution | How It Works |
|----------|-------------|
| `scoped_lock` (our approach) | Lock both forks atomically |
| Asymmetric ordering | Even philosophers pick left first, odd pick right first |
| Semaphore (limit diners) | Only allow 4 philosophers to sit at a time |
| Resource hierarchy | Always pick the lower-numbered fork first |

---

## Synchronization Primitives Cheat Sheet

| Primitive | Purpose | C++ Type |
|-----------|---------|----------|
| **Mutex** | Exclusive access to one resource | `std::mutex` |
| **Lock Guard** | RAII mutex wrapper | `std::lock_guard<std::mutex>` |
| **Unique Lock** | Flexible mutex wrapper (needed for CV) | `std::unique_lock<std::mutex>` |
| **Scoped Lock** | Lock multiple mutexes at once | `std::scoped_lock` |
| **Condition Variable** | Sleep until a condition is true | `std::condition_variable` |
| **Semaphore** | Control access to N resources | `std::counting_semaphore<N>` |

---

## How to Run

```bash
cmake -B build -S . && cmake --build build
./build/test_sync_mutex
./build/test_sync_semaphore
./build/test_sync_producer
./build/test_sync_dining
```
