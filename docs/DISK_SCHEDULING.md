# 💿 Disk Scheduling Module

> **Source Code:** [`src/disk_scheduling/`](../src/disk_scheduling/) · **Headers:** [`include/disk_scheduling/`](../include/disk_scheduling/) · **Test:** [`tests/test_disk_scheduling.cpp`](../tests/test_disk_scheduling.cpp)

## What is Disk Scheduling?

When multiple processes request data from a hard disk, they each need the disk head to move to a specific **cylinder** (track). The disk scheduler decides the **order** in which to service these requests to minimize the total distance the head travels.

```
  Disk with 200 cylinders (0-199)
  
  ◄───────────────── Disk Head ──────────────────►
  0        50              120          170    199
  |........|..............|.............|.......|
             ↑ Head is here (cylinder 50)
  
  Pending requests: [82, 170, 43, 140, 24, 16, 190]
  
  In what order should we visit them?
```

Think of it like a delivery truck planning its route. The goal is to minimize total distance driven.

---

## Architecture of Our Code

```
include/disk_scheduling/
├── disk_scheduler.h         ← Base class (interface)
└── algorithms/
    ├── fcfs.h               ← First-Come First-Served
    ├── sstf.h               ← Shortest Seek Time First
    ├── scan.h               ← SCAN (Elevator)
    └── c_scan.h             ← Circular SCAN
```

```cpp
struct DiskScheduleResult {
    std::string algorithmName;
    int initialHead;
    int totalHeadMovement;         // Total distance traveled
    std::vector<int> seekSequence; // Order of cylinders visited
};

class DiskScheduler {
public:
    virtual DiskScheduleResult schedule(
        int initialHead,
        const std::vector<int>& requests,
        int diskSize = 200
    ) = 0;
};
```

---

## Running Example (Used for All Algorithms)

We will use this same example to compare all four algorithms:

```
  Disk Size:     200 cylinders (0-199)
  Initial Head:  50
  Requests:      82, 170, 43, 140, 24, 16, 190
```

---

## Algorithm 1: First-Come, First-Served (FCFS)

> 📂 **Code:** [`src/disk_scheduling/algorithms/fcfs.cpp`](../src/disk_scheduling/algorithms/fcfs.cpp)

### How It Works

Service requests in the **exact order** they arrive. Simple — no optimization.

### Visualization

```
  Cylinder:  0   16  24    43  50        82           140     170     190  199
             |....|...|.....|..|.........|.............|.......|.......|....|
  
  Head movement path:
  50 → 82 → 170 → 43 → 140 → 24 → 16 → 190
    32   88   127   97   116    8   174
  
  Total Head Movement = 32 + 88 + 127 + 97 + 116 + 8 + 174 = 642
```

### How Our Code Does It

```cpp
DiskScheduleResult FCFSDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    int currentHead = initialHead;
    
    for (int request : requests) {
        result.seekSequence.push_back(request);
        result.totalHeadMovement += std::abs(request - currentHead);
        currentHead = request;
    }
}
```

| ✅ Pros | ❌ Cons |
|---------|---------|
| Simple and fair | Huge total head movement |
| No starvation | Lots of unnecessary back-and-forth |

**Total Head Movement: 642** ← Very high!

---

## Algorithm 2: Shortest Seek Time First (SSTF)

> 📂 **Code:** [`src/disk_scheduling/algorithms/sstf.cpp`](../src/disk_scheduling/algorithms/sstf.cpp)

### How It Works

Always move to the **closest pending request**. Like a greedy algorithm.

### Visualization

```
  Starting at 50:
  
  50 → 43 → 24 → 16 → 82 → 140 → 170 → 190
    7    19    8   66   58    30    20
  
  Step 1: Closest to 50 → 43 (distance 7)
  Step 2: Closest to 43 → 24 (distance 19)
  Step 3: Closest to 24 → 16 (distance 8)
  Step 4: Closest to 16 → 82 (distance 66)
  Step 5: Closest to 82 → 140 (distance 58)
  Step 6: Closest to 140 → 170 (distance 30)
  Step 7: Closest to 170 → 190 (distance 20)
  
  Total Head Movement = 7 + 19 + 8 + 66 + 58 + 30 + 20 = 208
```

### How Our Code Does It

```cpp
while (!pendingRequests.empty()) {
    // Find the request with minimum distance from currentHead
    auto closestIt = pendingRequests.begin();
    int minDistance = std::abs(*closestIt - currentHead);
    
    for (auto it = pendingRequests.begin() + 1; it != pendingRequests.end(); ++it) {
        int distance = std::abs(*it - currentHead);
        if (distance < minDistance) {
            minDistance = distance;
            closestIt = it;
        }
    }
    
    // Service this request and remove it
    currentHead = *closestIt;
    pendingRequests.erase(closestIt);
}
```

| ✅ Pros | ❌ Cons |
|---------|---------|
| Much better than FCFS | Can cause **starvation** at edges |
| Simple greedy logic | Not globally optimal |

**Total Head Movement: 208** ← Big improvement over FCFS!

---

## Algorithm 3: SCAN (Elevator Algorithm)

> 📂 **Code:** [`src/disk_scheduling/algorithms/scan.cpp`](../src/disk_scheduling/algorithms/scan.cpp)

### How It Works

The disk head moves in **one direction** (like an elevator going up), services all requests in its path, then **reverses direction** and services the remaining requests.

```
  Think of an elevator:
  
  Going UP:   Floor 1 → 2 → 3 → 5 → 7 → TOP
  Going DOWN: TOP → 6 → 4 → 1
  
  It doesn't jump around — it sweeps in one direction, then reverses.
```

### Visualization (Starting at 50, moving UP)

```
  Direction: ──────────────────────────────────►  (UP first)
  
  50 → 82 → 140 → 170 → 190 → 199 → 43 → 24 → 16
    32   58    30    20     9   156   19     8
  
  Phase 1 (UP):   50 → 82 → 140 → 170 → 190 → 199 (end of disk)
  Phase 2 (DOWN): 199 → 43 → 24 → 16
  
  Total Head Movement = 32 + 58 + 30 + 20 + 9 + 156 + 19 + 8 = 332
```

### How Our Code Does It

```cpp
// Divide requests into two groups
std::vector<int> left, right;
for (int req : requests) {
    if (req < initialHead) left.push_back(req);
    else right.push_back(req);
}
std::sort(left.begin(), left.end());
std::sort(right.begin(), right.end());

// Phase 1: Go right (up)
for (int req : right) { /* service */ }
// Hit the end of disk
seekSequence.push_back(diskSize - 1);

// Phase 2: Reverse, go left (down)
for (auto it = left.rbegin(); it != left.rend(); ++it) { /* service */ }
```

| ✅ Pros | ❌ Cons |
|---------|---------|
| No starvation | Goes to disk edge even if no requests there |
| Predictable performance | Requests at the far end wait longer |

**Total Head Movement: 332**

---

## Algorithm 4: C-SCAN (Circular SCAN)

> 📂 **Code:** [`src/disk_scheduling/algorithms/c_scan.cpp`](../src/disk_scheduling/algorithms/c_scan.cpp)

### How It Works

Like SCAN, but instead of reversing direction at the end, it **jumps back to the beginning** and services remaining requests in the same direction. This provides a **more uniform wait time**.

```
  ┌──────────────────────────────────────────────────┐
  │                                                  │
  │  SCAN:   50 ──► 199 ◄── 0   (serves both ways)  │
  │  C-SCAN: 50 ──► 199 ──► 0 ──► 43  (one way only)│
  │                                                  │
  │  C-SCAN treats the disk as circular!             │
  └──────────────────────────────────────────────────┘
```

### Visualization (Starting at 50, moving UP)

```
  50 → 82 → 140 → 170 → 190 → 199 → 0 → 16 → 24 → 43
    32   58    30    20     9   199  16    8   19
  
  Phase 1: Service going RIGHT → 82 → 140 → 170 → 190 → 199
  Jump:    199 → 0 (jump to start)
  Phase 2: Service from 0 going RIGHT → 16 → 24 → 43
  
  Total Head Movement = 32 + 58 + 30 + 20 + 9 + 199 + 16 + 8 + 19 = 391
```

### Why C-SCAN?

With regular SCAN, a request at cylinder 1 might be served right after the head passes — or it might have to wait for the head to go all the way right, then come back. **C-SCAN makes the wait time more uniform** because it always serves in one direction.

| ✅ Pros | ❌ Cons |
|---------|---------|
| Uniform wait time | More total head movement than SCAN |
| Fair across all cylinders | Jump back is wasted movement |

**Total Head Movement: 391**

---

## Algorithm Comparison (Same Example)

| Algorithm | Total Head Movement | Starvation? | Uniformity |
|-----------|--------------------:|:-----------:|:----------:|
| **FCFS** | 642 | ❌ No | ❌ |
| **SSTF** | 208 | ⚠️ Yes | ❌ |
| **SCAN** | 332 | ❌ No | ❌ |
| **C-SCAN** | 391 | ❌ No | ✅ |

```
  Head Movement (lower is better):
  
  SSTF   ████████████ 208
  SCAN   ████████████████████ 332
  C-SCAN ███████████████████████ 391
  FCFS   █████████████████████████████████████ 642
```

### When to Use What?

| Algorithm | Best For |
|-----------|----------|
| **FCFS** | When fairness matters more than efficiency |
| **SSTF** | Maximum throughput (but watch for starvation) |
| **SCAN** | General purpose — good balance |
| **C-SCAN** | Real-time systems where uniform response time matters |

---

## How to Run

```bash
cmake -B build -S . && cmake --build build
./build/test_disk_scheduling
```

Expected output:
```
--- Disk Scheduling Module Test ---

Initial Head Position: 50
Requests: 82 170 43 140 24 16 190

Algorithm: FCFS
Total Head Movement: 642
Seek Sequence: 82 170 43 140 24 16 190

Algorithm: SSTF
Total Head Movement: 208
Seek Sequence: 43 24 16 82 140 170 190

Algorithm: SCAN
Total Head Movement: ...
Seek Sequence: ...

Algorithm: C-SCAN
Total Head Movement: ...
Seek Sequence: ...
```
