# 📋 CPU Scheduling Module

> **Source Code:** [`src/cpu_scheduler/`](../src/cpu_scheduler/) · **Headers:** [`include/cpu_scheduler/`](../include/cpu_scheduler/) · **Test:** [`tests/test_cpu_scheduler.cpp`](../tests/test_cpu_scheduler.cpp)

## What is CPU Scheduling?

When multiple processes are loaded into memory and ready to run, the OS must decide **which process gets the CPU next**. This decision is made by the **CPU Scheduler** (also called the **Short-Term Scheduler**).

Think of it like a traffic signal at a busy intersection — it decides which lane (process) gets to go (use the CPU) and for how long.

```
              Ready Queue
        ┌──────────────────────┐
        │  P1  P2  P3  P4  P5 │ ──── Scheduler picks one ────► CPU
        └──────────────────────┘                                  │
              ▲                                                   │
              │                                                   ▼
              └───────── Process finishes or gets preempted ──────┘
```

---

## Key Terms You Must Know

| Term | Formula | What It Means |
|------|---------|---------------|
| **Arrival Time (AT)** | Given | When the process enters the ready queue |
| **Burst Time (BT)** | Given | Total CPU time the process needs |
| **Completion Time (CT)** | Calculated | When the process finishes execution |
| **Turnaround Time (TAT)** | `CT - AT` | Total time from arrival to completion |
| **Waiting Time (WT)** | `TAT - BT` | Time spent waiting in the ready queue |
| **Response Time (RT)** | `First_Run - AT` | Time from arrival to first execution |

> 💡 **Lower average WT and TAT = better algorithm performance.**

These are calculated in our code inside [`scheduler.cpp`](../src/cpu_scheduler/scheduler.cpp):
```cpp
// Turnaround = Completion - Arrival
int turnaround = process.getCompletionTime() - process.getArrivalTime();
// Waiting = Turnaround - Burst
int waiting = turnaround - process.getBurstTime();
// Response = First Start - Arrival
int response = process.getStartTime() - process.getArrivalTime();
```

---

## Preemptive vs Non-Preemptive

| Non-Preemptive | Preemptive |
|----------------|------------|
| Once a process starts, it runs until it finishes | A running process can be interrupted mid-execution |
| Simpler to implement | Better responsiveness |
| FCFS, SJF, Priority (NP) | SRTF, Round Robin, Priority (P) |

---

## Architecture of Our Code

```
include/cpu_scheduler/
├── process.h           ← Process class (PID, burst, arrival, state, etc.)
├── scheduler.h         ← Abstract base class (startProcess, finishProcess)
├── algorithms/
│   ├── fcfs.h          ← First-Come First-Served
│   ├── sjf.h           ← Shortest Job First
│   ├── srtf.h          ← Shortest Remaining Time First
│   ├── priority.h      ← Priority Scheduling
│   └── round_robin.h   ← Round Robin
└── utils/
    └── schedule_printer.h  ← Pretty-prints results
```

Every algorithm **inherits** from the `Scheduler` base class:
```cpp
class Scheduler {
public:
    virtual void schedule(std::vector<Process>& processes) = 0;  // Pure virtual
protected:
    void startProcess(Process& process, int currentTime);   // Records start time
    void finishProcess(Process& process, int currentTime);  // Calculates TAT, WT, RT
};
```

This means to add a new algorithm, you simply create a new class that inherits `Scheduler` and implements `schedule()`. That's it!

---

## Algorithm 1: First-Come, First-Served (FCFS)

> 📂 **Code:** [`src/cpu_scheduler/algorithms/fcfs.cpp`](../src/cpu_scheduler/algorithms/fcfs.cpp)

### How It Works
The simplest algorithm — whoever arrives first gets the CPU first. Like a queue at a grocery store checkout.

```
  Process arrives first ──► Gets CPU first ──► Runs to completion ──► Next process
```

### Step-by-Step Example

| Process | Arrival Time | Burst Time |
|---------|-------------|------------|
| P1 | 0 | 4 |
| P2 | 1 | 3 |
| P3 | 2 | 1 |
| P4 | 3 | 2 |

**Gantt Chart:**
```
 ┌────────┬──────┬───┬────┐
 │   P1   │  P2  │P3 │ P4 │
 └────────┴──────┴───┴────┘
 0        4      7   8   10
```

**Calculations:**
| Process | CT | TAT (CT-AT) | WT (TAT-BT) |
|---------|-----|-------------|-------------|
| P1 | 4 | 4-0 = 4 | 4-4 = 0 |
| P2 | 7 | 7-1 = 6 | 6-3 = 3 |
| P3 | 8 | 8-2 = 6 | 6-1 = 5 |
| P4 | 10 | 10-3 = 7 | 7-2 = 5 |

**Average WT** = (0+3+5+5)/4 = **3.25**

### How Our Code Does It
```cpp
void FCFSScheduler::schedule(std::vector<Process>& processes) {
    // Step 1: Sort by arrival time (earliest first)
    std::sort(processes.begin(), processes.end(), ...);

    int currentTime = 0;

    for (Process& process : processes) {
        // Step 2: If CPU is idle, jump forward to this process's arrival
        if (currentTime < process.getArrivalTime())
            currentTime = process.getArrivalTime();

        // Step 3: Start → Run entire burst → Finish
        startProcess(process, currentTime);
        currentTime += process.getBurstTime();
        finishProcess(process, currentTime);
    }
}
```

### Pros & Cons
| ✅ Pros | ❌ Cons |
|---------|---------|
| Dead simple to implement | **Convoy Effect** — short processes wait behind long ones |
| No starvation | Poor average waiting time |

---

## Algorithm 2: Shortest Job First (SJF)

> 📂 **Code:** [`src/cpu_scheduler/algorithms/sjf.cpp`](../src/cpu_scheduler/algorithms/sjf.cpp)

### How It Works
Always pick the process with the **shortest burst time** that has already arrived. Non-preemptive — once it starts, it runs to completion.

```
  Ready Queue: [P1(BT=8), P2(BT=2), P3(BT=4)]
  
  SJF picks ──► P2 (shortest burst = 2)
```

### Step-by-Step Example

| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 7 |
| P2 | 2 | 4 |
| P3 | 4 | 1 |
| P4 | 5 | 4 |

**Gantt Chart:**
```
 ┌───────────────┬───┬────────┬────────┐
 │      P1       │P3 │   P2   │   P4   │
 └───────────────┴───┴────────┴────────┘
 0               7   8       12       16
```
At time 7: P2(BT=4), P3(BT=1), P4(BT=4) are all waiting → SJF picks P3 (BT=1).

**Average WT** = (0+6+3+7)/4 = **4.0** (vs FCFS which would be higher!)

### How Our Code Does It
```cpp
// The key selection logic inside the while loop:
if (process.getBurstTime() < selectedProcess->getBurstTime()) {
    selectedProcess = &process;  // Pick the shorter job
}
```
Tie-breaking: If burst times are equal → pick earlier arrival → if still tied → pick lower PID.

### Pros & Cons
| ✅ Pros | ❌ Cons |
|---------|---------|
| Optimal average waiting time (proven mathematically!) | Requires knowing burst time in advance |
| | Can cause **starvation** of long processes |

---

## Algorithm 3: Shortest Remaining Time First (SRTF)

> 📂 **Code:** [`src/cpu_scheduler/algorithms/srtf.cpp`](../src/cpu_scheduler/algorithms/srtf.cpp)

### How It Works
The **preemptive version of SJF**. At every time unit, the OS checks: "Is there a process with less remaining time than the one currently running?" If yes, **preempt** the running process.

```
  Time 0: P1(remaining=7) starts
  Time 2: P2(remaining=4) arrives → 4 < 7 → PREEMPT P1! → P2 runs
  Time 4: P3(remaining=1) arrives → 1 < 4 → PREEMPT P2! → P3 runs
```

### Step-by-Step Example

| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 7 |
| P2 | 2 | 4 |
| P3 | 4 | 1 |

**Gantt Chart:**
```
 ┌────┬──────┬───┬──────┬───────────┐
 │ P1 │  P2  │P3 │  P2  │    P1     │
 └────┴──────┴───┴──────┴───────────┘
 0    2      4   5      7          12
```

### How Our Code Does It
```cpp
// Runs ONE time unit per iteration (preemptive!)
selectedProcess->setRemainingTime(selectedProcess->getRemainingTime() - 1);
currentTime++;

if (selectedProcess->getRemainingTime() == 0) {
    finishProcess(*selectedProcess, currentTime);  // Done!
} else {
    selectedProcess->setState(ProcessState::Ready);  // Back to ready queue
}
```

### Pros & Cons
| ✅ Pros | ❌ Cons |
|---------|---------|
| Better than SJF for response time | High context-switch overhead |
| Truly optimal average WT | Starvation of long processes |

---

## Algorithm 4: Priority Scheduling

> 📂 **Code:** [`src/cpu_scheduler/algorithms/priority.cpp`](../src/cpu_scheduler/algorithms/priority.cpp)

### How It Works
Each process is assigned a **priority number**. The CPU always runs the process with the **highest priority** (lower number = higher priority in our implementation).

```
  Ready Queue: P1(priority=3), P2(priority=1), P3(priority=2)
  
  Priority picks ──► P2 (priority 1 is highest)
```

### Step-by-Step Example

| Process | AT | BT | Priority |
|---------|----|----|----------|
| P1 | 0 | 4 | 3 |
| P2 | 1 | 3 | 1 |
| P3 | 2 | 2 | 2 |

**Gantt Chart:**
```
 ┌────────┬──────┬────┐
 │   P1   │  P2  │ P3 │
 └────────┴──────┴────┘
 0        4      7    9
```
P1 starts first (only process at time 0). At time 4, P2(pri=1) and P3(pri=2) are waiting → P2 wins.

### ⚠️ Starvation Problem
If high-priority processes keep arriving, a low-priority process **might never run**!

**Solution: Aging** — Gradually increase the priority of waiting processes over time.

### Pros & Cons
| ✅ Pros | ❌ Cons |
|---------|---------|
| Flexible, can model real-world importance | Starvation |
| Used in real OS (Linux nice values!) | Requires priority assignment |

---

## Algorithm 5: Round Robin (RR)

> 📂 **Code:** [`src/cpu_scheduler/algorithms/round_robin.cpp`](../src/cpu_scheduler/algorithms/round_robin.cpp)

### How It Works
Each process gets a fixed **time quantum** (e.g., 2 units). If it doesn't finish within that time, it goes to the **back of the queue**. Like taking turns!

```
  Time Quantum = 2

  ┌─── Queue: P1, P2, P3 ───┐
  │                          │
  │  P1 runs for 2 → back   │
  │  P2 runs for 2 → back   │
  │  P3 runs for 2 → done!  │
  │  P1 runs for 2 → done!  │
  │  P2 runs for 1 → done!  │
  └──────────────────────────┘
```

### Step-by-Step Example (Quantum = 2)

| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 5 |
| P2 | 1 | 3 |
| P3 | 2 | 2 |

**Gantt Chart:**
```
 ┌────┬────┬────┬────┬────┬───┐
 │ P1 │ P2 │ P3 │ P1 │ P2 │P1 │
 └────┴────┴────┴────┴────┴───┘
 0    2    4    6    8    9  10
```
1. t=0: P1 runs 2 units (remaining: 3) → back of queue
2. t=2: P2 runs 2 units (remaining: 1) → back of queue
3. t=4: P3 runs 2 units (remaining: 0) → **done!**
4. t=6: P1 runs 2 units (remaining: 1) → back of queue
5. t=8: P2 runs 1 unit  (remaining: 0) → **done!**
6. t=9: P1 runs 1 unit  (remaining: 0) → **done!**

### How Our Code Does It
```cpp
// Uses a std::queue for the ready queue
std::queue<Process*> readyQueue;

// Each process runs for min(remainingTime, quantum)
int executionTime = std::min(current->getRemainingTime(), quantum);
current->setRemainingTime(current->getRemainingTime() - executionTime);

if (current->getRemainingTime() == 0) {
    finishProcess(*current, currentTime);  // Done!
} else {
    readyQueue.push(current);  // Back to the end of the queue
}
```

### Choosing the Right Quantum
| Quantum Too Small | Quantum Too Large |
|-------------------|-------------------|
| Too many context switches → overhead | Behaves like FCFS |
| Wastes CPU time on switching | Poor response time |

**Rule of Thumb:** 80% of CPU bursts should be shorter than the time quantum.

### Pros & Cons
| ✅ Pros | ❌ Cons |
|---------|---------|
| Fair — every process gets CPU time | Higher average WT than SJF |
| Great response time | Depends heavily on quantum choice |
| **Used in real OS!** (Linux CFS is RR-based) | Context switch overhead |

---

## Algorithm Comparison Summary

| Algorithm | Type | Starvation? | Best For |
|-----------|------|-------------|----------|
| FCFS | Non-Preemptive | ❌ No | Simple batch systems |
| SJF | Non-Preemptive | ⚠️ Yes | Minimizing average WT |
| SRTF | Preemptive | ⚠️ Yes | Best possible avg WT |
| Priority | Non-Preemptive | ⚠️ Yes | Real-time systems |
| Round Robin | Preemptive | ❌ No | Time-sharing/interactive systems |

---

## How to Run

```bash
cmake -B build -S . && cmake --build build
./build/test_cpu_scheduler
```
