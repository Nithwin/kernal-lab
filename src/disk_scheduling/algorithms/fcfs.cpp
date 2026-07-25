/**
 * @file fcfs.cpp
 * @brief First-Come, First-Served (FCFS) Disk Scheduling Algorithm.
 *
 * CONCEPT:
 *   - Services disk I/O requests in the exact order they arrive.
 *   - Simple and completely fair (no starvation).
 *   - Does NOT optimize head movement (leads to high total seek distance).
 *
 * FORMULA:
 *   Seek Distance = | Target Track - Current Track |
 *   Total Seek Distance = Sum of all individual seek distances.
 */

#include "disk_scheduling/algorithms/fcfs.h"
#include <cmath>

DiskScheduleResult FCFSDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    DiskScheduleResult result;
    result.algorithmName = "FCFS";
    result.initialHead = initialHead;
    result.totalHeadMovement = 0;
    
    int currentHead = initialHead;
    
    // Service each request sequentially in order of arrival
    for (int request : requests) {
        result.seekSequence.push_back(request);
        result.totalHeadMovement += std::abs(request - currentHead);
        currentHead = request;
    }
    
    return result;
}
