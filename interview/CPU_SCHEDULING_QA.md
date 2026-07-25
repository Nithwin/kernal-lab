# 📋 CPU Scheduling — Interview Questions & Answers

> These are the most commonly asked CPU scheduling questions in OS interviews at companies like Google, Amazon, Microsoft, and in university exams.

---

## Q1. What is CPU Scheduling? Why is it needed?

**Answer:**
CPU scheduling is the mechanism by which the OS decides which process in the ready queue gets the CPU next. It is needed because:
- Only **one process** can use the CPU at a time (on a single core).
- Multiple processes compete for CPU time.
- We want to maximize **CPU utilization**, **throughput**, and minimize **waiting time**.

---

## Q2. What is the difference between Preemptive and Non-Preemptive scheduling?

**Answer:**

| Preemptive | Non-Preemptive |
|------------|----------------|
| OS can interrupt a running process and switch to another | Once a process starts, it runs until completion or I/O wait |
| Better for interactive systems | Simpler to implement |
| Higher context-switch overhead | Lower overhead |
| Examples: SRTF, Round Robin | Examples: FCFS, SJF |

---

## Q3. Explain Turnaround Time, Waiting Time, and Response Time.

**Answer:**
- **Turnaround Time (TAT)** = `Completion Time - Arrival Time` — Total time from submission to completion.
- **Waiting Time (WT)** = `TAT - Burst Time` — Time spent waiting in the ready queue.
- **Response Time (RT)** = `First Execution Time - Arrival Time` — Time from submission to first CPU allocation.

**Example:**
```
Process arrives at time 0, starts at time 3, burst = 5, finishes at time 8
TAT = 8 - 0 = 8
WT  = 8 - 5 = 3
RT  = 3 - 0 = 3
```

---

## Q4. What is the Convoy Effect?

**Answer:**
The **Convoy Effect** occurs in FCFS scheduling when a long CPU-bound process occupies the CPU, and many shorter processes pile up behind it in the ready queue, waiting for it to finish.

```
Long process (BT=100) → Short process (BT=1) → Short process (BT=2)
                         ↑ These wait 100 time units just to run for 1-2!
```

This leads to very high average waiting time. **SJF solves this** by running short jobs first.

---

## Q5. Why is SJF optimal but impractical?

**Answer:**
- **Optimal** because it is mathematically proven to give the minimum average waiting time among all non-preemptive algorithms.
- **Impractical** because we need to know the burst time of a process **before it runs**, which is impossible in real systems.
- **Real-world workaround:** Use exponential averaging to **predict** the next burst time based on previous bursts.

---

## Q6. What is starvation? How do you prevent it?

**Answer:**
**Starvation** occurs when a process waits indefinitely because higher-priority (or shorter) processes keep arriving and getting the CPU first.

- Happens in: SJF, SRTF, Priority Scheduling
- Does NOT happen in: FCFS, Round Robin

**Prevention: Aging** — Gradually increase the priority of waiting processes over time so they eventually get to run.

---

## Q7. How does Round Robin work? What happens if the time quantum is too small or too large?

**Answer:**
Round Robin gives each process a fixed time slice (quantum). After the quantum expires, the process is preempted and moved to the back of the ready queue.

| Quantum Too Small | Quantum Too Large |
|-------------------|-------------------|
| Excessive context switches | Degenerates into FCFS |
| High overhead, less useful CPU work | Poor response time |

**Rule of Thumb:** 80% of CPU bursts should be shorter than the time quantum.

---

## Q8. Compare FCFS, SJF, SRTF, Priority, and Round Robin.

**Answer:**

| Feature | FCFS | SJF | SRTF | Priority | RR |
|---------|------|-----|------|----------|-----|
| Preemptive? | No | No | Yes | No* | Yes |
| Starvation? | No | Yes | Yes | Yes | No |
| Convoy Effect? | Yes | No | No | No | No |
| Optimal WT? | No | Yes (NP) | Yes (P) | No | No |
| Real-world use | Batch | Theory | Theory | RT systems | Time-sharing |

*Priority can be preemptive or non-preemptive.

---

## Q9. What scheduling algorithm does Linux use?

**Answer:**
Linux uses the **Completely Fair Scheduler (CFS)**. It uses a **red-black tree** to track how much CPU time each process has received and always picks the process with the **least CPU time used so far** (the "most unfair" situation). This is conceptually similar to Round Robin but more sophisticated.

---

## Q10. What is a context switch? Why is it expensive?

**Answer:**
A **context switch** is the process of saving the state (registers, program counter, stack pointer) of the currently running process and loading the state of the next process to run.

**Why it's expensive:**
- The CPU does **no useful work** during the switch.
- Memory caches are invalidated (cold cache).
- TLB (Translation Lookaside Buffer) entries are flushed.
- Typical cost: 1-10 microseconds.

---

## Q11. Solve this numerical: Given these processes, compute average WT using FCFS.

| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 4 |
| P2 | 1 | 3 |
| P3 | 2 | 1 |

**Answer:**
```
Gantt Chart: |P1 (0-4)|P2 (4-7)|P3 (7-8)|

P1: CT=4, TAT=4-0=4, WT=4-4=0
P2: CT=7, TAT=7-1=6, WT=6-3=3
P3: CT=8, TAT=8-2=6, WT=6-1=5

Average WT = (0+3+5)/3 = 2.67
Average TAT = (4+6+6)/3 = 5.33
```

---

## Q12. Solve the same numerical using SJF.

**Answer:**
```
At time 0: Only P1 available → P1 runs (BT=4)
At time 4: P2(BT=3), P3(BT=1) available → P3 runs (shortest)
At time 5: P2 runs

Gantt Chart: |P1 (0-4)|P3 (4-5)|P2 (5-8)|

P1: CT=4, TAT=4, WT=0
P3: CT=5, TAT=3, WT=2
P2: CT=8, TAT=7, WT=4

Average WT = (0+4+2)/3 = 2.0  ← Better than FCFS!
```
