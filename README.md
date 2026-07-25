# KernelLab 💻

> A comprehensive Open-Source playground designed to teach Operating Systems concepts and algorithms.

KernelLab is built for students, professionals, and OS enthusiasts who want to master basic and advanced operating systems concepts. It is an excellent resource for **interview preparation** and **exam study**, providing hands-on C++ implementations of the algorithms that power modern systems.

---

## 🚀 Modules & Learning Outcomes

By exploring this repository, you will understand the core components of modern operating systems. The project is neatly divided into several modules, each containing documented code and individual tests to help you learn efficiently.

### 1️⃣ CPU Scheduling (`src/cpu_scheduler`)
Understand how an OS decides which process runs next.
- First-Come, First-Served (FCFS)
- Shortest Job First (SJF)
- Shortest Remaining Time First (SRTF)
- Priority Scheduling
- Round Robin

### 2️⃣ Memory Management (`src/memory_manager`)
Learn how an OS allocates RAM and handles virtual memory.
- Contiguous Allocation (First Fit, Best Fit, Worst Fit, Next Fit)
- Paging and Frame Management

### 3️⃣ Process Synchronization (`src/synchronization`)
Dive into concurrent programming and race condition prevention.
- Mutexes & Spinlocks (`mutex_demo.cpp`)
- Semaphores (`semaphore_demo.cpp`)
- Producer-Consumer Problem (`producer_consumer.cpp`)
- Dining Philosophers Problem (`dining_philosophers.cpp`)

### 4️⃣ Disk Scheduling (`src/disk_scheduling`)
Explore how disk I/O requests are optimized to minimize head movement.
- FCFS (First-Come, First-Served)
- SSTF (Shortest Seek Time First)
- SCAN (Elevator Algorithm)
- C-SCAN (Circular SCAN)

---

## 🛠️ Building and Running

We have organized the project using CMake so you can compile and run tests for each module independently.

1. **Configure the build:**
   ```bash
   cmake -B build -S .
   ```
2. **Compile the project:**
   ```bash
   cmake --build build
   ```
3. **Run the individual module tests:**
   ```bash
   ./build/test_cpu_scheduler
   ./build/test_memory_manager
   ./build/test_disk_scheduling
   ./build/test_sync_dining
   ./build/test_sync_mutex
   ./build/test_sync_producer
   ./build/test_sync_semaphore
   ```

---

## 🤝 Contributing & "Bring Your Own Language"

This repository is designed to be an Open Source learning hub! 
We highly encourage contributions. 

**Want to learn by doing?**
Create a new directory (e.g., `python/`, `rust/`, `java/`) and port this project into your **favorite programming language**! 
See [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to push your own language implementation here.

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).
