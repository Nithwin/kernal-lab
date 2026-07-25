# 🧠 Memory Management Module

> **Source Code:** [`src/memory_manager/`](../src/memory_manager/) · **Headers:** [`include/memory_manager/`](../include/memory_manager/) · **Test:** [`tests/test_memory_manager.cpp`](../tests/test_memory_manager.cpp)

## What is Memory Management?

Every running program needs RAM. But RAM is limited and multiple programs compete for it. The OS must:
1. **Allocate** memory when a process needs it.
2. **Deallocate** memory when a process finishes.
3. **Track** which parts of memory are free and which are occupied.

```
           Physical Memory (RAM)
  ┌─────────────────────────────────────┐
  │         OS Kernel                   │ ← Reserved for the OS
  ├─────────────────────────────────────┤
  │    Process A (200 KB)               │ ← Allocated
  ├─────────────────────────────────────┤
  │         FREE (100 KB)               │ ← Hole
  ├─────────────────────────────────────┤
  │    Process B (300 KB)               │ ← Allocated
  ├─────────────────────────────────────┤
  │         FREE (400 KB)               │ ← Hole
  └─────────────────────────────────────┘
```

---

## Architecture of Our Code

```
include/memory_manager/
├── memory.h             ← Memory block (start address, size, allocated?, pid)
├── manager.h            ← Abstract base class for allocators
├── algorithms/
│   ├── first_fit.h      ← First Fit allocation
│   ├── best_fit.h       ← Best Fit allocation
│   ├── worst_fit.h      ← Worst Fit allocation
│   └── next_fit.h       ← Next Fit allocation
├── paging/
│   ├── pager.h          ← Manages pages ↔ frames mapping
│   ├── page.h           ← A single page entry
│   ├── page_table.h     ← Per-process page table
│   └── frame.h          ← A single physical memory frame
└── utils/
    └── memory_printer.h ← Pretty-prints memory state
```

Base class design:
```cpp
class MemoryManager {
protected:
    int totalMemory;
    std::vector<Memory> blocks;   // List of memory blocks (allocated + free)
public:
    virtual bool allocate(int pid, int size) = 0;  // Pure virtual
    virtual bool deallocate(int pid);               // Free memory by PID
};
```

---

## Part 1: Contiguous Memory Allocation

In contiguous allocation, each process gets **one continuous block** of memory. The OS maintains a list of free "holes" and must choose which hole to use.

### Example Setup

```
  Memory: 1000 KB total
  
  ┌────────┬────────┬──────────┬────────┬──────────┐
  │ P1     │ FREE   │ P2       │ FREE   │ P3       │
  │ 200KB  │ 150KB  │ 300KB    │ 250KB  │ 100KB    │
  └────────┴────────┴──────────┴────────┴──────────┘
  0       200      350        650      900       1000
  
  New request: Process P4 needs 120 KB
  Which hole do we choose?
```

---

### Algorithm 1: First Fit

> 📂 **Code:** [`src/memory_manager/algorithms/first_fit.cpp`](../src/memory_manager/algorithms/first_fit.cpp)

**Rule:** Scan from the beginning. Allocate the **first hole** that is big enough.

```
  Holes: [150 KB, 250 KB]
  Request: 120 KB
  
  Scan → 150 KB ≥ 120 KB? ✅ YES → Allocate here!
  
  Result:
  ┌────────┬──────┬────┬──────────┬────────┬──────────┐
  │ P1     │  P4  │FREE│ P2       │ FREE   │ P3       │
  │ 200KB  │120KB │30KB│ 300KB    │ 250KB  │ 100KB    │
  └────────┴──────┴────┴──────────┴────────┴──────────┘
```

**How our code works:**
```cpp
bool FirstFit::allocate(int pid, int size) {
    for (size_t i = 0; i < blocks.size(); i++) {
        if (!blocks[i].getIsAllocated() && blocks[i].getSize() >= size) {
            // Found a big enough hole! Split it.
            blocks[i].setIsAllocated(true);
            blocks[i].setPid(pid);
            
            // If hole is bigger than needed, split into [allocated | remaining free]
            if (blockSize > size) {
                Memory freeBlock(startAddress + size, blockSize - size);
                blocks.insert(blocks.begin() + i + 1, freeBlock);
            }
            return true;
        }
    }
    return false;  // No hole big enough
}
```

| ✅ Pros | ❌ Cons |
|---------|---------|
| Fast — stops at first match | Creates small fragments at the beginning |

---

### Algorithm 2: Best Fit

> 📂 **Code:** [`src/memory_manager/algorithms/best_fit.cpp`](../src/memory_manager/algorithms/best_fit.cpp)

**Rule:** Scan **all** holes. Pick the **smallest hole** that is big enough.

```
  Holes: [150 KB, 250 KB]
  Request: 120 KB
  
  Check 150 KB ≥ 120? ✅ (waste = 30 KB)
  Check 250 KB ≥ 120? ✅ (waste = 130 KB)
  
  Best = 150 KB (least waste)  → Allocate here!
```

| ✅ Pros | ❌ Cons |
|---------|---------|
| Minimizes wasted space | Slower (must scan all holes) |
| | Creates tiny unusable fragments |

---

### Algorithm 3: Worst Fit

> 📂 **Code:** [`src/memory_manager/algorithms/worst_fit.cpp`](../src/memory_manager/algorithms/worst_fit.cpp)

**Rule:** Scan **all** holes. Pick the **largest hole**.

```
  Holes: [150 KB, 250 KB]
  Request: 120 KB
  
  Worst Fit picks ──► 250 KB (largest)
  
  Remaining hole = 250 - 120 = 130 KB (still usable!)
```

The idea: by leaving larger leftover fragments, they are more likely to be useful for future requests.

| ✅ Pros | ❌ Cons |
|---------|---------|
| Leaves larger remaining holes | Slow (must scan all) |
| | Quickly fragments large blocks |

---

### Algorithm 4: Next Fit

> 📂 **Code:** [`src/memory_manager/algorithms/next_fit.cpp`](../src/memory_manager/algorithms/next_fit.cpp)

**Rule:** Like First Fit, but instead of always starting from the beginning, start searching from **where the last allocation happened**.

```
  Last allocation was at index 3
  
  Next request → start scanning from index 3 (not 0)
  This distributes allocations more evenly across memory.
```

| ✅ Pros | ❌ Cons |
|---------|---------|
| Faster than First Fit (doesn't re-scan the beginning) | Can fragment the end of memory |
| Distributes allocations evenly | |

---

### Comparison of All Allocation Algorithms

| Algorithm | Speed | Fragmentation | When to Use |
|-----------|-------|---------------|-------------|
| **First Fit** | ⚡ Fast | Moderate | General purpose |
| **Best Fit** | 🐢 Slow | Many tiny fragments | When memory is precious |
| **Worst Fit** | 🐢 Slow | Large fragments | When you want usable leftovers |
| **Next Fit** | ⚡ Fast | Moderate | When allocations are frequent |

---

## Part 2: Paging

### The Problem with Contiguous Allocation

Contiguous allocation suffers from **external fragmentation**: there might be enough total free memory, but it's scattered in small holes that can't satisfy a large request.

```
  FREE(50) + FREE(80) + FREE(70) = 200 KB free
  But a process needs 150 KB contiguous → FAILS! ❌
```

### The Solution: Paging

**Paging** breaks memory into fixed-size chunks:
- **Logical memory** (process view) → divided into **Pages**
- **Physical memory** (actual RAM) → divided into **Frames**
- Pages and Frames are the **same size** (e.g., 256 bytes)
- A **Page Table** maps each page to a frame

```
    Logical Address Space          Physical Memory (RAM)
    (Process View)                 (Actual Hardware)
    
    ┌──────────┐                  ┌──────────┐
    │ Page 0   │ ──────────────►  │ Frame 5  │
    ├──────────┤                  ├──────────┤
    │ Page 1   │ ──────────►      │ Frame 2  │
    ├──────────┤              │   ├──────────┤
    │ Page 2   │ ────►        │   │ Frame 7  │
    └──────────┘     │        │   ├──────────┤
                     │        │   │ Frame 0  │
    Page Table:      │        │   ├──────────┤
    ┌──────┬───────┐ │        │   │ Frame 1  │
    │ Page │ Frame │ │        │   ├──────────┤
    ├──────┼───────┤ │        └──►│ Frame 3  │
    │  0   │   5   │─┘            ├──────────┤
    │  1   │   2   │              │ Frame 4  │
    │  2   │   7   │              ├──────────┤
    └──────┴───────┘              │ Frame 6  │
                                  └──────────┘
    
    Notice: Pages are NOT stored in order in physical memory!
    That's the beauty — no external fragmentation.
```

### Address Translation

To translate a logical address to a physical address:

```
  Logical Address = 600
  Page Size = 256 bytes
  
  Page Number  = 600 / 256 = 2      (integer division)
  Offset       = 600 % 256 = 88     (remainder)
  
  Look up Page 2 in Page Table → Frame 7
  
  Physical Address = (Frame × Page Size) + Offset
                   = (7 × 256) + 88
                   = 1792 + 88
                   = 1880
```

### How Our Code Does It

```cpp
// In pager.cpp
int Pager::translateAddress(int pid, int logicalAddress) {
    int pageNumber = logicalAddress / pageSize;   // Which page?
    int offset     = logicalAddress % pageSize;   // Where inside the page?
    
    const Page& page = pageTable.getPage(pageNumber);
    int frameNumber  = page.getFrameNumber();     // Look up the frame
    
    return frameNumber * pageSize + offset;       // Physical address!
}
```

### Loading a Process (Page-by-Page)

When a process with 900 bytes of memory needs to be loaded (page size = 256):

```
  Pages needed = ceil(900 / 256) = 4 pages
  
  For each page:
    1. Find a free frame
    2. Mark frame as occupied (pid, page number)
    3. Add entry to the process's page table
    
  If not enough frames → Rollback all allocated frames → return false
```

### Page Fault

A **page fault** occurs when a process tries to access a page that isn't currently loaded in any frame. Our code handles this:

```cpp
bool Pager::handlePageFault(int pid, int pageNumber) {
    Frame* frame = findFreeFrame();  // Find empty frame
    if (frame == nullptr) return false;  // No space!
    
    frame->setFree(false);
    frame->setPid(pid);
    frame->setPageNumber(pageNumber);
    
    page.setFrameNumber(frame->getFrameNumber());
    page.setLoaded(true);
    return true;
}
```

---

## How to Run

```bash
cmake -B build -S . && cmake --build build
./build/test_memory_manager
```

Expected output:
```
Process 1 Loaded
Process 2 Loaded

Frames
-----------------------------
Frame 0 | PID = 1 | Page = 0 | Free = false
Frame 1 | PID = 1 | Page = 1 | Free = false
...
Deallocating Process 1...
Frame 0 | PID = -1 | Page = -1 | Free = true
...
```
