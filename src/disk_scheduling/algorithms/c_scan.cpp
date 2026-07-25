/**
 * @file c_scan.cpp
 * @brief Circular SCAN (C-SCAN) Disk Scheduling Algorithm.
 *
 * CONCEPT:
 *   - Similar to SCAN, but provides a more UNIFORM WAIT TIME.
 *   - The disk head moves in one direction only (e.g., UP toward diskSize - 1),
 *     servicing requests along the way.
 *   - Upon reaching the disk edge (diskSize - 1), it immediately JUMPS back to 0
 *     without servicing any requests during the jump, then resumes servicing in the original direction.
 *
 * ADVANTAGE OVER SCAN:
 *   - In SCAN, cylinders near the edges get less frequent visits than cylinders in the middle.
 *   - C-SCAN treats the disk tracks as a circular list, ensuring equal waiting time for all cylinders.
 */

#include "disk_scheduling/algorithms/c_scan.h"
#include <cmath>
#include <algorithm>

DiskScheduleResult CSCANDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    DiskScheduleResult result;
    result.algorithmName = "C-SCAN";
    result.initialHead = initialHead;
    result.totalHeadMovement = 0;
    
    std::vector<int> left, right;
    
    // Step 1: Partition requests into left (< initialHead) and right (>= initialHead)
    for (int req : requests) {
        if (req < initialHead)
            left.push_back(req);
        else
            right.push_back(req);
    }
    
    // Step 2: Sort both vectors ascending
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    int currentHead = initialHead;
    
    // Step 3: Service right side (going UP to disk end)
    for (int req : right) {
        result.seekSequence.push_back(req);
        result.totalHeadMovement += std::abs(req - currentHead);
        currentHead = req;
    }
    
    // Step 4: If left side has requests, reach end of disk and jump back to cylinder 0
    if (!left.empty()) {
        // Go to maximum disk boundary
        result.seekSequence.push_back(diskSize - 1);
        result.totalHeadMovement += std::abs(diskSize - 1 - currentHead);
        currentHead = diskSize - 1;
        
        // Return to start (cylinder 0) — circular return
        result.seekSequence.push_back(0);
        result.totalHeadMovement += std::abs(currentHead - 0);
        currentHead = 0;
        
        // Step 5: Service remaining requests from cylinder 0 going UP
        for (int req : left) {
            result.seekSequence.push_back(req);
            result.totalHeadMovement += std::abs(req - currentHead);
            currentHead = req;
        }
    }
    
    return result;
}
