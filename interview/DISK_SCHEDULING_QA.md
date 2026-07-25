# 💿 Disk Scheduling — Interview Questions & Answers

> Common disk scheduling questions asked in OS interviews and university exams.

---

## Q1. Why is Disk Scheduling needed?

**Answer:**
Multiple processes request disk I/O simultaneously. The disk head must physically **move** to the correct cylinder to read/write data. Disk scheduling optimizes the **order** of servicing requests to:
- Minimize **seek time** (time to move the head)
- Maximize **throughput** (requests served per unit time)
- Ensure **fairness** (no request waits forever)

---

## Q2. What are the components of Disk Access Time?

**Answer:**

```
Disk Access Time = Seek Time + Rotational Latency + Transfer Time

Seek Time:           Time to move the head to the correct track/cylinder
                     (Most expensive — this is what scheduling optimizes!)

Rotational Latency:  Time for the disk to rotate so the desired sector
                     is under the head (average = half a rotation)

Transfer Time:       Time to actually read/write the data
```

**Seek time dominates**, so disk scheduling focuses on minimizing total head movement.

---

## Q3. Compare FCFS, SSTF, SCAN, and C-SCAN.

**Answer:**

| Feature | FCFS | SSTF | SCAN | C-SCAN |
|---------|------|------|------|--------|
| Strategy | Order of arrival | Closest request | Elevator sweep | One-way sweep |
| Starvation | ❌ No | ⚠️ Yes | ❌ No | ❌ No |
| Throughput | Low | High | Good | Good |
| Fairness | Fair | Unfair (edges) | Moderate | Most fair |
| Complexity | O(1) per request | O(n) per request | O(n log n) sort | O(n log n) sort |

---

## Q4. What is the SSTF Starvation Problem?

**Answer:**
In SSTF, the head always moves to the **closest request**. If new requests keep arriving near the current head position, requests at the **far edges** of the disk may **never be served**.

```
  Head at cylinder 50
  
  Requests:  [48, 52, 47, 53, 46, 55, ...]  ← Keeps getting requests near 50
  
  Request at cylinder 190: NEVER SERVED! 😢 (starvation)
```

**Solution:** Use SCAN or C-SCAN which guarantee all requests will eventually be served.

---

## Q5. Explain the SCAN (Elevator) Algorithm in detail.

**Answer:**
The disk arm moves in one direction (e.g., toward higher cylinders), servicing all requests in its path. When it reaches the **end of the disk**, it **reverses direction** and services requests going back.

```
  Head starts at 50, moving RIGHT:
  
  RIGHT sweep: 50 → 82 → 140 → 170 → 190 → [199 end]
  LEFT sweep:  [199 end] → 43 → 24 → 16
  
  Just like an elevator going up, then down.
```

**Variations:**
- **LOOK:** Like SCAN, but reverses at the **last request** instead of the disk edge.
- **C-LOOK:** Like C-SCAN, but jumps back to the **first request** instead of cylinder 0.

---

## Q6. What is the difference between SCAN and C-SCAN?

**Answer:**

| Feature | SCAN | C-SCAN |
|---------|------|--------|
| Direction | Sweeps both ways | Sweeps one way only |
| After reaching end | Reverses direction | Jumps back to start |
| Wait time | Varies (edge vs middle) | Uniform |
| Treats disk as | Linear | **Circular** |

```
SCAN:   0 ◄──────── 50 ────────► 199 ◄──────── 0
C-SCAN: 0 ────────► 50 ────────► 199 ────────► 0 ────────► 50
                                      (jump, no service)
```

C-SCAN is better when **uniform response time** is important (like in real-time systems).

---

## Q7. What are LOOK and C-LOOK?

**Answer:**
LOOK and C-LOOK are optimized versions that **don't go all the way to the disk edge** if there are no requests there.

| Algorithm | Goes to disk edge? | Optimization |
|-----------|-------------------|--------------|
| SCAN | Yes (always to 0 or 199) | None |
| LOOK | No (stops at last request) | Saves unnecessary movement |
| C-SCAN | Yes | None |
| C-LOOK | No | Saves unnecessary movement |

```
SCAN:  50 → 82 → 140 → 170 → 190 → [199] → reverse
LOOK:  50 → 82 → 140 → 170 → 190 → reverse   (skips going to 199)
```

---

## Q8. Solve this numerical: Calculate total head movement for FCFS.

```
Initial Head: 53
Requests: 98, 183, 37, 122, 14, 124, 65, 67
```

**Answer:**
```
53 → 98 → 183 → 37 → 122 → 14 → 124 → 65 → 67

|53-98|  = 45
|98-183| = 85
|183-37| = 146
|37-122| = 85
|122-14| = 108
|14-124| = 110
|124-65| = 59
|65-67|  = 2

Total Head Movement = 45+85+146+85+108+110+59+2 = 640
```

---

## Q9. Solve the same numerical with SSTF.

**Answer:**
```
Start at 53:
  Closest to 53: 65 (dist=12) ✓
  Closest to 65: 67 (dist=2) ✓
  Closest to 67: 37 (dist=30) ✓
  Closest to 37: 14 (dist=23) ✓
  Closest to 14: 98 (dist=84) ✓
  Closest to 98: 122 (dist=24) ✓
  Closest to 122: 124 (dist=2) ✓
  Closest to 124: 183 (dist=59) ✓

Total = 12+2+30+23+84+24+2+59 = 236

Much better than FCFS (640)!
```

---

## Q10. In a real OS, which disk scheduling algorithm is used?

**Answer:**
Modern operating systems typically use variations of:
- **Linux:** Uses the **Completely Fair Queuing (CFQ)** scheduler, **deadline scheduler**, or **BFQ (Budget Fair Queueing)** scheduler. These are based on SCAN/C-SCAN ideas but add priorities and deadlines.
- **Windows:** Uses a custom scheduler similar to SCAN.

**For SSDs:** Disk scheduling is less important because SSDs have no moving head. Random access is almost as fast as sequential access. Most OS schedulers detect SSDs and use simpler algorithms like **NOOP (no-operation)** or **mq-deadline**.

---

## Q11. What is the Disk Scheduling problem's relationship to the Traveling Salesman Problem?

**Answer:**
Finding the truly optimal order to service disk requests is equivalent to the **Shortest Hamiltonian Path problem**, which is NP-hard. This means:
- There is no known polynomial-time algorithm to find the best order.
- SSTF is a **greedy approximation** (not globally optimal).
- That's why we use heuristics like SCAN and C-SCAN instead.

---

## Q12. How does disk scheduling differ for SSDs vs HDDs?

**Answer:**

| Feature | HDD | SSD |
|---------|-----|-----|
| Has moving parts? | Yes (head, platter) | No |
| Seek time | High (~5-10ms) | Negligible (~0.1ms) |
| Random vs Sequential | Sequential much faster | Almost equal |
| Scheduling importance | Critical | Minimal |
| Common scheduler | CFQ, deadline, BFQ | NOOP, mq-deadline |
| Wear leveling needed? | No | Yes |

Since SSDs have no physical head to move, the concept of "seek time" disappears, making traditional disk scheduling algorithms largely irrelevant for SSDs.
