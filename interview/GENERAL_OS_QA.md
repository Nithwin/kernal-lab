# 🎯 OS Interview Questions — General Concepts

> These questions cover fundamental operating system concepts that don't fit into a single module. These are frequently asked as warm-up or theoretical questions.

---

## Q1. What is an Operating System?

**Answer:**
An **Operating System (OS)** is system software that manages hardware resources and provides services to user programs. It acts as an **intermediary** between the user and the hardware.

```
  ┌──────────────────────────────────┐
  │          User Applications       │
  ├──────────────────────────────────┤
  │      System Libraries/APIs       │
  ├──────────────────────────────────┤
  │     ┌────────────────────────┐   │
  │     │   Operating System     │   │
  │     │  ┌──────────────────┐  │   │
  │     │  │ Process Manager  │  │   │
  │     │  │ Memory Manager   │  │   │
  │     │  │ File System      │  │   │
  │     │  │ I/O Manager      │  │   │
  │     │  │ Scheduler        │  │   │
  │     │  └──────────────────┘  │   │
  │     └────────────────────────┘   │
  ├──────────────────────────────────┤
  │           Hardware               │
  │   (CPU, RAM, Disk, Network)      │
  └──────────────────────────────────┘
```

---

## Q2. What is the difference between a Process and a Thread?

**Answer:**

| Feature | Process | Thread |
|---------|---------|--------|
| Memory | Own address space | Shares parent process's memory |
| Creation cost | Heavy (fork) | Lightweight |
| Communication | IPC (pipes, sockets) | Shared memory (direct) |
| Crash effect | Does not affect other processes | Can crash the whole process |
| Context switch | Expensive | Cheaper |

```
Process A                          Process B
┌────────────────────┐             ┌────────────────────┐
│ Thread 1  Thread 2 │             │ Thread 1           │
│ ┌──────┐ ┌──────┐  │             │ ┌──────┐           │
│ │Stack │ │Stack │  │             │ │Stack │           │
│ └──────┘ └──────┘  │             │ └──────┘           │
│ ┌──────────────────┐│             │ ┌──────────────────┐│
│ │  Shared Heap     ││             │ │  Shared Heap     ││
│ └──────────────────┘│             │ └──────────────────┘│
│ ┌──────────────────┐│             │ ┌──────────────────┐│
│ │  Code + Data     ││             │ │  Code + Data     ││
│ └──────────────────┘│             │ └──────────────────┘│
└────────────────────┘             └────────────────────┘
     Separate memory                   Separate memory
```

---

## Q3. What are the different states of a process?

**Answer:**

```
                     ┌─────────┐
          admitted   │   New   │
         ┌──────────►│         │
         │           └────┬────┘
         │                │
         │                ▼
    ┌────┴────┐     ┌──────────┐      ┌───────────┐
    │Terminated│◄────│ Running  │◄─────│   Ready   │
    │         │     │          │──────►│           │
    └─────────┘     └────┬─────┘      └─────┬─────┘
                         │                   ▲
                         │  I/O wait         │ I/O complete
                         ▼                   │
                    ┌──────────┐              │
                    │ Waiting  │──────────────┘
                    │(Blocked) │
                    └──────────┘
```

- **New** → Process is being created
- **Ready** → Process is waiting to be assigned to the CPU
- **Running** → Process is currently executing on the CPU
- **Waiting** → Process is waiting for I/O or an event
- **Terminated** → Process has finished execution

---

## Q4. What is the difference between User Mode and Kernel Mode?

**Answer:**

| Feature | User Mode | Kernel Mode |
|---------|-----------|-------------|
| Privileges | Limited | Full access to hardware |
| Direct hardware access | ❌ No | ✅ Yes |
| Failure effect | Only the program crashes | Entire system can crash |
| Examples | Your apps, browsers | Device drivers, OS kernel |

A **system call** is how a user-mode program requests services from the kernel (e.g., `read()`, `write()`, `fork()`).

---

## Q5. What is a System Call? Give examples.

**Answer:**
A **system call** is the interface between user programs and the OS kernel. When a program needs to perform privileged operations, it makes a system call.

| Category | System Calls | Purpose |
|----------|-------------|---------|
| Process | `fork()`, `exec()`, `exit()`, `wait()` | Create and manage processes |
| File | `open()`, `read()`, `write()`, `close()` | File operations |
| Memory | `mmap()`, `brk()`, `sbrk()` | Memory allocation |
| I/O | `ioctl()`, `read()`, `write()` | Device operations |
| IPC | `pipe()`, `shmget()`, `msgget()` | Inter-process communication |

---

## Q6. What is the difference between Monolithic and Microkernel architecture?

**Answer:**

| Feature | Monolithic Kernel | Microkernel |
|---------|-------------------|-------------|
| Structure | All services in kernel space | Only essential services in kernel |
| Performance | Fast (no IPC overhead) | Slower (IPC between services) |
| Size | Large | Small |
| Stability | One bug can crash everything | More resilient |
| Examples | Linux, Unix | Minix, QNX |

```
Monolithic:                    Microkernel:
┌────────────────────┐         ┌──────────────────────────┐
│     User Space     │         │       User Space         │
├────────────────────┤         │  ┌─────┐ ┌─────┐ ┌────┐ │
│ File System        │         │  │ FS  │ │ Net │ │Drv │ │
│ Memory Manager     │         │  └──┬──┘ └──┬──┘ └─┬──┘ │
│ Device Drivers     │         ├─────┼───────┼──────┼─────┤
│ Scheduler          │         │  Minimal Kernel (IPC,    │
│ Network Stack      │         │  Scheduling, Memory)     │
│ ALL IN KERNEL!     │         └──────────────────────────┘
└────────────────────┘
```

---

## Q7. What is IPC (Inter-Process Communication)?

**Answer:**
IPC allows processes to communicate and share data. Common methods:

| Method | Description | Speed | Use Case |
|--------|-------------|-------|----------|
| **Pipes** | Unidirectional byte stream | Medium | Parent-child |
| **Message Queues** | Structured messages | Medium | Client-server |
| **Shared Memory** | Shared RAM region | Fast | High-throughput |
| **Sockets** | Network-style communication | Slow | Across machines |
| **Signals** | Simple notifications | Fast | Event notification |
| **Semaphores** | Synchronization primitive | Fast | Synchronization |

---

## Q8. What is the difference between fork() and exec()?

**Answer:**
- **`fork()`** — Creates a **copy** of the current process. Both parent and child continue from the same point.
- **`exec()`** — **Replaces** the current process's code with a new program.

```
Parent Process (PID 100)
        │
        ├── fork() ──► Child Process (PID 101)
        │              │ (exact copy of parent)
        │              │
        │              ├── exec("ls") ──► Now running "ls"
        │              │                  (code replaced)
        │              │
        │              └── exit()
        │
        └── wait() ──► Resumes after child finishes
```

**Common pattern:** `fork()` + `exec()` = create a new process running a different program (this is how your shell runs commands!).

---

## Q9. What is a Zombie Process vs an Orphan Process?

**Answer:**

| Feature | Zombie | Orphan |
|---------|--------|--------|
| Definition | Child finished but parent hasn't called `wait()` | Parent finished before child |
| State | Terminated (but entry exists in process table) | Running (adopted by `init`/`systemd`) |
| Problem | Wastes process table entries | Generally harmless |
| Fix | Parent calls `wait()` or `waitpid()` | Adopted by PID 1 automatically |

---

## Q10. What is a Context Switch? What information is saved?

**Answer:**
A **context switch** saves the state of the running process and loads the state of the next process. Saved information includes:

- Program Counter (PC)
- CPU Registers
- Stack Pointer
- Process State
- Memory management info (page tables)
- I/O status

**Cost:** ~1-10 microseconds (no useful work during this time).

---

## Q11. What is the difference between Multiprogramming, Multitasking, and Multiprocessing?

**Answer:**

| Concept | Definition |
|---------|-----------|
| **Multiprogramming** | Multiple programs loaded in memory; CPU switches when one waits for I/O |
| **Multitasking** | Like multiprogramming, but with **time-sharing** (rapid switching gives illusion of parallelism) |
| **Multiprocessing** | Multiple CPUs/cores executing processes **truly in parallel** |
| **Multithreading** | Multiple threads within a single process executing concurrently |

---

## Q12. What is Demand Paging?

**Answer:**
**Demand paging** loads pages into memory **only when they are accessed** (on demand), rather than loading the entire program at startup.

```
Process starts → Only Page 0 loaded
Process accesses Page 3 → PAGE FAULT → Load Page 3 from disk
Process accesses Page 1 → PAGE FAULT → Load Page 1 from disk
Process accesses Page 3 again → Already in memory → No fault ✅
```

**Benefits:**
- Faster program startup
- Less memory used
- Allows programs larger than physical memory
