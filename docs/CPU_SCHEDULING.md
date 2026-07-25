# CPU Scheduling Module

This module demonstrates various CPU scheduling algorithms, which determine how processes in the ready queue are allocated the CPU.

## Algorithms Implemented

1. **First-Come, First-Served (FCFS)**
   - Simplest algorithm. Processes are assigned the CPU in the order they request it.
   - Non-preemptive.

2. **Shortest Job First (SJF)**
   - Selects the process with the smallest execution time next.
   - Non-preemptive. Minimizes average waiting time.

3. **Shortest Remaining Time First (SRTF)**
   - The preemptive version of SJF.
   - If a new process arrives with a shorter burst time than the current running process, it preempts it.

4. **Priority Scheduling**
   - Each process is assigned a priority. The CPU is allocated to the highest priority process.
   - Can lead to starvation (solved by aging).

5. **Round Robin (RR)**
   - Each process is given a small unit of CPU time (time quantum). 
   - After this time has elapsed, the process is preempted and added to the end of the ready queue.

## C++ Implementation Details
- Base classes and interfaces are used to enforce standard behavior for all schedulers.
- Leverages STL (`std::vector`, `std::sort`, lambda functions) to cleanly organize and sort the queue.
- See `tests/test_cpu_scheduler.cpp` for an example of how to configure and run the algorithms.
