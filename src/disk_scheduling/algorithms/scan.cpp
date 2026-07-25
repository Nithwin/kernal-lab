/**
 * @file scan.cpp
 * @brief SCAN (Elevator) Disk Scheduling Algorithm.
 *
 * CONCEPT:
 *   - The disk arm starts at the initial head position and moves in one direction
 *     (e.g., toward higher cylinders), servicing requests as it reaches each cylinder,
 *     until it reaches the end of the disk (cylinder diskSize - 1).
 *   - At the disk edge, direction reverses and the arm services remaining requests
 *     moving in the opposite direction.
 *
 * PROS:
 *   - Prevents starvation (unlike SSTF).
 *   - Provides good throughput and bounded waiting time.
 */

#include "disk_scheduling/algorithms/scan.h"
#include <cmath>
#include <algorithm>

DiskScheduleResult SCANDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    DiskScheduleResult result;
    result.algorithmName = "SCAN";
    result.initialHead = initialHead;
    result.totalHeadMovement = 0;
    
    std::vector<int> left, right;
    
    // Step 1: Divide requests into left (< initialHead) and right (>= initialHead)
    for (int req : requests) {
        if (req < initialHead)
            left.push_back(req);
        else
            right.push_back(req);
    }
    
    // Step 2: Sort both partitions
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    int currentHead = initialHead;
    int run = 2; // Maximum 2 directional sweeps
    bool movingUp = directionUp;
    
    while (run--) {
        if (movingUp) {
            // Sweep UP (toward higher cylinders)
            for (int req : right) {
                result.seekSequence.push_back(req);
                result.totalHeadMovement += std::abs(req - currentHead);
                currentHead = req;
            }
            // If there are requests remaining on the left, touch end of disk before reversing
            if (run > 0 && !left.empty()) {
                result.seekSequence.push_back(diskSize - 1);
                result.totalHeadMovement += std::abs(diskSize - 1 - currentHead);
                currentHead = diskSize - 1;
            }
            movingUp = false; // Reverse direction
        } else {
            // Sweep DOWN (toward lower cylinders, descending order)
            for (auto it = left.rbegin(); it != left.rend(); ++it) {
                result.seekSequence.push_back(*it);
                result.totalHeadMovement += std::abs(*it - currentHead);
                currentHead = *it;
            }
            // If there are requests remaining on the right, touch start of disk before reversing
            if (run > 0 && !right.empty()) {
                result.seekSequence.push_back(0);
                result.totalHeadMovement += std::abs(currentHead - 0);
                currentHead = 0;
            }
            movingUp = true; // Reverse direction
        }
    }
    
    return result;
}
