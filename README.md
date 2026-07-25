# KernelLab 💻

> A comprehensive Open-Source playground designed to teach Operating Systems concepts and algorithms — with code, documentation, and interview prep.

KernelLab is built for **students**, **professionals**, and **OS enthusiasts** who want to master operating systems concepts through clean, documented, hands-on C++ implementations.

Whether you're preparing for a **tech interview**, studying for a **university exam**, or just want to deeply understand how operating systems work, this repo has you covered.

---

## 📚 What's Inside

This repository is organized into **4 modules**, each containing:
- ✅ Clean, commented C++ source code
- ✅ Detailed documentation with ASCII diagrams and examples
- ✅ Separate test executables you can run independently
- ✅ Interview questions with answers for each topic

---

## 🚀 Modules

### 1️⃣ CPU Scheduling
> How does the OS decide which process runs next?

| Algorithm | Type | Key Concept |
|-----------|------|-------------|
| First-Come First-Served (FCFS) | Non-Preemptive | Queue order |
| Shortest Job First (SJF) | Non-Preemptive | Optimal average WT |
| Shortest Remaining Time First (SRTF) | Preemptive | Preemptive SJF |
| Priority Scheduling | Non-Preemptive | Priority-based selection |
| Round Robin | Preemptive | Time quantum fairness |

📖 **[Read Full Documentation →](docs/CPU_SCHEDULING.md)**
🎯 **[Interview Questions →](interview/CPU_SCHEDULING_QA.md)**
📂 Source: [`src/cpu_scheduler/`](src/cpu_scheduler/) · Headers: [`include/cpu_scheduler/`](include/cpu_scheduler/)

---

### 2️⃣ Memory Management
> How does the OS allocate RAM and manage virtual memory?

| Feature | Algorithms |
|---------|-----------|
| Contiguous Allocation | First Fit, Best Fit, Worst Fit, Next Fit |
| Paging | Page Tables, Frame Management, Address Translation |

📖 **[Read Full Documentation →](docs/MEMORY_MANAGEMENT.md)**
🎯 **[Interview Questions →](interview/MEMORY_MANAGEMENT_QA.md)**
📂 Source: [`src/memory_manager/`](src/memory_manager/) · Headers: [`include/memory_manager/`](include/memory_manager/)

---

### 3️⃣ Process Synchronization
> How do we prevent race conditions and deadlocks?

| Demo | Concept | C++ Primitive |
|------|---------|---------------|
| Mutex Demo | Mutual Exclusion | `std::mutex`, `std::lock_guard` |
| Semaphore Demo | Resource Counting | `std::counting_semaphore` |
| Producer-Consumer | Bounded Buffer | `std::condition_variable` |
| Dining Philosophers | Deadlock Prevention | `std::scoped_lock` |

📖 **[Read Full Documentation →](docs/PROCESS_SYNCHRONIZATION.md)**
🎯 **[Interview Questions →](interview/PROCESS_SYNCHRONIZATION_QA.md)**
📂 Source: [`src/synchronization/`](src/synchronization/)

---

### 4️⃣ Disk Scheduling
> How does the OS optimize disk I/O to minimize head movement?

| Algorithm | Strategy | Starvation? |
|-----------|----------|:-----------:|
| FCFS | Arrival order | ❌ No |
| SSTF | Closest request first | ⚠️ Yes |
| SCAN (Elevator) | Sweep one direction, reverse | ❌ No |
| C-SCAN | Sweep one direction, jump back | ❌ No |

📖 **[Read Full Documentation →](docs/DISK_SCHEDULING.md)**
🎯 **[Interview Questions →](interview/DISK_SCHEDULING_QA.md)**
📂 Source: [`src/disk_scheduling/`](src/disk_scheduling/) · Headers: [`include/disk_scheduling/`](include/disk_scheduling/)

---

## 🎯 Interview Preparation

We have a dedicated **[`interview/`](interview/)** folder with **60+ curated questions and answers** covering all major OS topics:

| Topic | Questions | Link |
|-------|:---------:|------|
| General OS Concepts | 12 | [GENERAL_OS_QA.md](interview/GENERAL_OS_QA.md) |
| CPU Scheduling | 12 | [CPU_SCHEDULING_QA.md](interview/CPU_SCHEDULING_QA.md) |
| Memory Management | 12 | [MEMORY_MANAGEMENT_QA.md](interview/MEMORY_MANAGEMENT_QA.md) |
| Process Synchronization | 12 | [PROCESS_SYNCHRONIZATION_QA.md](interview/PROCESS_SYNCHRONIZATION_QA.md) |
| Disk Scheduling | 12 | [DISK_SCHEDULING_QA.md](interview/DISK_SCHEDULING_QA.md) |

Each file includes **detailed answers**, **ASCII diagrams**, **numerical examples**, and **comparison tables**.

👉 **[Start with the Top 10 Most-Asked Questions →](interview/README.md)**

---

## 🛠️ Building and Running

### Prerequisites
- C++20 compiler (GCC 11+, Clang 14+, MSVC 19.29+)
- CMake 3.20+

### Build

```bash
# Configure
cmake -B build -S .

# Compile all modules
cmake --build build
```

### Run Module Tests

```bash
# CPU Scheduling
./build/test_cpu_scheduler

# Memory Management
./build/test_memory_manager

# Disk Scheduling
./build/test_disk_scheduling

# Synchronization (each is a separate demo)
./build/test_sync_mutex
./build/test_sync_semaphore
./build/test_sync_producer
./build/test_sync_dining
```

---

## 📁 Project Structure

```
kernal-lab/
├── include/                    ← Header files (class definitions)
│   ├── cpu_scheduler/
│   │   ├── process.h           ← Process class (PID, burst, state, etc.)
│   │   ├── scheduler.h         ← Abstract base class for schedulers
│   │   ├── algorithms/         ← FCFS, SJF, SRTF, Priority, Round Robin
│   │   └── utils/              ← Schedule printer
│   ├── memory_manager/
│   │   ├── memory.h            ← Memory block class
│   │   ├── manager.h           ← Abstract base class for allocators
│   │   ├── algorithms/         ← First Fit, Best Fit, Worst Fit, Next Fit
│   │   ├── paging/             ← Pager, Page, PageTable, Frame
│   │   └── utils/              ← Memory printer
│   └── disk_scheduling/
│       ├── disk_scheduler.h    ← Abstract base class
│       └── algorithms/         ← FCFS, SSTF, SCAN, C-SCAN
│
├── src/                        ← Implementation files
│   ├── cpu_scheduler/          ← CPU scheduling implementations
│   ├── memory_manager/         ← Memory management implementations
│   ├── disk_scheduling/        ← Disk scheduling implementations
│   └── synchronization/        ← Standalone sync demos (each has main())
│
├── tests/                      ← Test files for each module
│   ├── test_cpu_scheduler.cpp
│   ├── test_memory_manager.cpp
│   └── test_disk_scheduling.cpp
│
├── docs/                       ← Detailed documentation with diagrams
│   ├── CPU_SCHEDULING.md
│   ├── MEMORY_MANAGEMENT.md
│   ├── PROCESS_SYNCHRONIZATION.md
│   └── DISK_SCHEDULING.md
│
├── interview/                  ← Interview Q&A for each topic
│   ├── README.md               ← Quick reference & top 10 questions
│   ├── GENERAL_OS_QA.md
│   ├── CPU_SCHEDULING_QA.md
│   ├── MEMORY_MANAGEMENT_QA.md
│   ├── PROCESS_SYNCHRONIZATION_QA.md
│   └── DISK_SCHEDULING_QA.md
│
├── CMakeLists.txt              ← Build configuration
├── CONTRIBUTING.md             ← How to contribute
├── CODE_OF_CONDUCT.md
├── LICENSE                     ← MIT License
└── README.md                   ← You are here!
```

---

## 🤝 Contributing — "Bring Your Own Language"

This repository is designed to be a **polyglot OS learning hub**! We encourage you to:

### 🌍 Port to Your Favorite Language
Create a new directory (e.g., `python/`, `rust/`, `java/`, `go/`) and implement these algorithms in your language of choice. This is a fantastic way to practice a new language while cementing your OS knowledge.

### 📝 Improve Documentation
Found an explanation that could be clearer? Add more examples or fix typos — every improvement helps learners worldwide.

### 🐛 Fix Bugs or Add Algorithms
Want to add LOOK/C-LOOK for disk scheduling, or Banker's Algorithm for deadlocks? Open an issue first, then submit a PR!

👉 **[Read the full Contributing Guide →](CONTRIBUTING.md)**

---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---

## ⭐ Star This Repo

If this helped you learn OS concepts or prepare for an interview, consider giving it a ⭐! It helps others discover this resource.
