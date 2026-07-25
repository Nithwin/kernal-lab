# 🧠 Memory Management — Interview Questions & Answers

> These questions cover contiguous allocation, paging, virtual memory, and fragmentation — the most common memory management topics in OS interviews.

---

## Q1. What is the difference between Internal and External Fragmentation?

**Answer:**

| Internal Fragmentation | External Fragmentation |
|------------------------|------------------------|
| Wasted space **inside** an allocated block | Wasted space **between** allocated blocks |
| Process gets more memory than it needs | Enough total free memory exists, but not contiguous |
| Happens with: Fixed-size partitions, Paging | Happens with: Variable-size partitions, Contiguous allocation |

```
Internal Fragmentation:          External Fragmentation:
┌──────────────┐                 ┌─────┬──────┬─────┬──────┬─────┐
│ Process (50) │                 │ P1  │ FREE │ P2  │ FREE │ P3  │
│ Block  (64)  │                 │100KB│ 50KB │80KB │ 70KB │60KB │
│ Wasted: 14KB │                 └─────┴──────┴─────┴──────┴─────┘
└──────────────┘                 FREE = 120KB, but can't fit 100KB process!
```

---

## Q2. Explain First Fit, Best Fit, Worst Fit, and Next Fit.

**Answer:**

| Algorithm | Strategy | Speed | Fragmentation |
|-----------|----------|-------|---------------|
| **First Fit** | First hole big enough | Fast | Moderate |
| **Best Fit** | Smallest sufficient hole | Slow | Tiny fragments |
| **Worst Fit** | Largest hole | Slow | Large fragments |
| **Next Fit** | First fit from last position | Fast | Moderate |

**Example:**
```
Holes: [100KB, 500KB, 200KB, 300KB]
Request: 210KB

First Fit → 500KB (first one ≥ 210)
Best Fit  → 300KB (smallest ≥ 210)
Worst Fit → 500KB (largest)
Next Fit  → depends on last allocation position
```

---

## Q3. What is Paging? How does it solve external fragmentation?

**Answer:**
**Paging** divides:
- Logical memory into fixed-size **pages**
- Physical memory into fixed-size **frames** (same size as pages)

A **page table** maps each page to a frame. Since pages don't need to be contiguous in physical memory, there are **no external fragments**.

```
Logical:   [Page 0][Page 1][Page 2]
Physical:  [Frame 5][Frame 2][Frame 7]  ← Non-contiguous, that's OK!
```

**Trade-off:** Paging may cause **internal fragmentation** (last page may not be fully used).

---

## Q4. How does Logical-to-Physical Address Translation work in Paging?

**Answer:**

```
Given:
  Page Size = 4 KB (4096 bytes)
  Logical Address = 13500

Step 1: Page Number = 13500 / 4096 = 3 (integer division)
Step 2: Offset = 13500 % 4096 = 1212

Step 3: Look up Page 3 in Page Table → Frame 6

Step 4: Physical Address = (6 × 4096) + 1212 = 24576 + 1212 = 25788
```

**Formula:**
```
Physical Address = (Frame Number × Page Size) + Offset
```

---

## Q5. What is a Page Fault? What happens when one occurs?

**Answer:**
A **page fault** occurs when a process tries to access a page that is **not currently loaded in physical memory** (RAM).

**Steps when a page fault occurs:**
1. Process accesses a page → page table says "not loaded" → **trap to OS**
2. OS finds a free frame in RAM
3. Reads the required page from disk into that frame
4. Updates the page table entry
5. Restarts the instruction that caused the fault

**If no free frame exists:** The OS must **replace** an existing page (using FIFO, LRU, etc.).

---

## Q6. What is a Page Table? What are its entries?

**Answer:**
A **page table** is a per-process data structure that maps logical page numbers to physical frame numbers.

```
Page Table for Process P1:
┌──────────┬──────────────┬────────────┬────────────┐
│ Page No. │ Frame Number │ Valid Bit  │ Dirty Bit  │
├──────────┼──────────────┼────────────┼────────────┤
│    0     │      5       │     1      │     0      │
│    1     │      2       │     1      │     1      │
│    2     │      -       │     0      │     0      │  ← Not loaded!
│    3     │      7       │     1      │     0      │
└──────────┴──────────────┴────────────┴────────────┘
```

- **Valid bit** = 1 means the page is loaded in RAM
- **Dirty bit** = 1 means the page has been modified (needs write-back to disk)

---

## Q7. What is Virtual Memory?

**Answer:**
**Virtual memory** allows a process to use more memory than physically available by using disk space as an extension of RAM.

```
  Process thinks it has 4 GB of memory
  Actual RAM: only 2 GB
  
  Solution: Keep frequently used pages in RAM,
            store the rest on disk (swap space).
            Load pages on demand (page faults).
```

**Benefits:**
- Programs can be larger than physical memory
- Better memory utilization
- Process isolation (each process has its own virtual address space)

---

## Q8. What is Thrashing?

**Answer:**
**Thrashing** occurs when a system spends more time **paging (swapping pages in/out)** than executing actual work. This happens when there are too many processes competing for too little RAM.

```
  CPU Utilization
       │
  100% │        ╭──╮
       │       ╱    ╲
   50% │      ╱      ╲
       │     ╱        ╲
       │    ╱   CLIFF  ╲────── Thrashing!
    0% │───╱             ╲───
       └──────────────────────
         Few   Moderate  Too Many
              Processes
```

**Solution:** Reduce the number of active processes, or use the **Working Set Model** to give each process enough frames.

---

## Q9. Explain the page replacement algorithms: FIFO, LRU, and Optimal.

**Answer:**

| Algorithm | Replaces | Pros | Cons |
|-----------|----------|------|------|
| **FIFO** | Oldest page | Simple | Belady's Anomaly |
| **LRU** | Least Recently Used | Good performance | Expensive to implement |
| **Optimal** | Page not used for longest time | Best possible | Impossible (needs future knowledge) |

**FIFO Example (3 frames):**
```
Reference String: 7 0 1 2 0 3 0 4

Step 1: [7] - - → Page Fault
Step 2: [7 0] - → Page Fault
Step 3: [7 0 1] → Page Fault
Step 4: [2 0 1] → Page Fault (7 is oldest, replaced)
Step 5: [2 0 1] → Hit (0 is present)
Step 6: [2 3 1] → Page Fault (0 is oldest)
...
```

---

## Q10. What is the TLB (Translation Lookaside Buffer)?

**Answer:**
The **TLB** is a small, fast hardware cache that stores recent page-table entries. It speeds up address translation by avoiding a memory lookup in the page table.

```
  CPU generates logical address
        │
        ▼
  ┌──────────┐  HIT → Direct frame access (fast!)
  │   TLB    │
  └──────────┘  MISS → Look up page table in RAM → Update TLB
```

- **TLB Hit:** Physical address in ~1 clock cycle
- **TLB Miss:** Must access page table in RAM (~100 clock cycles)
- Typical TLB hit rate: **95-99%**

---

## Q11. What is Belady's Anomaly?

**Answer:**
**Belady's Anomaly** is a counterintuitive phenomenon where **increasing the number of frames can increase page faults** with FIFO replacement.

```
  With 3 frames: 9 page faults
  With 4 frames: 10 page faults  ← More frames, MORE faults! 🤯
```

This happens only with **FIFO**. LRU and Optimal are **stack algorithms** and do not suffer from Belady's Anomaly.

---

## Q12. Calculate pages needed: A process needs 72 KB of memory. Page size is 16 KB. How many pages?

**Answer:**
```
Pages needed = ceil(72 KB / 16 KB) = ceil(4.5) = 5 pages

Page 0: 16 KB
Page 1: 16 KB
Page 2: 16 KB
Page 3: 16 KB
Page 4: 8 KB (partially filled — this causes 8 KB of internal fragmentation)

Total internal fragmentation = 16 - 8 = 8 KB
```
