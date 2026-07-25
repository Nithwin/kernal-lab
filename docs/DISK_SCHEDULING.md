# Disk Scheduling Module

Disk scheduling algorithms determine the order in which disk I/O requests are serviced to minimize total head movement and improve performance.

## Algorithms Implemented

1. **First-Come, First-Served (FCFS)**
   - Services requests in the exact order they arrive.
   - Pros: Simple to implement, fair.
   - Cons: Often results in high total head movement (poor performance).

2. **Shortest Seek Time First (SSTF)**
   - Selects the request with the minimum seek time (closest distance) from the current head position.
   - Pros: Drastically reduces head movement compared to FCFS.
   - Cons: Can cause starvation for requests at the edges of the disk if a continuous stream of requests arrives near the current head.

3. **SCAN (Elevator Algorithm)**
   - The disk arm starts at one end and moves towards the other, servicing requests along the way. Upon reaching the end, the direction reverses.
   - Pros: Prevents starvation, better bounds on wait time.
   - Cons: The return trip might serve fewer requests if they are densely clustered at the opposite end.

4. **Circular SCAN (C-SCAN)**
   - Similar to SCAN, but upon reaching the end of the disk, it immediately returns to the beginning without servicing any requests on the return trip.
   - Pros: Provides a more uniform wait time across all cylinders.
   
## C++ Implementation Details
- Based on the `DiskScheduler` interface.
- Calculates `totalHeadMovement` and records the `seekSequence`.
- Highly encapsulated and easy to extend (e.g., if you want to add LOOK or C-LOOK).
- See `tests/test_disk_scheduling.cpp` for example usage.
