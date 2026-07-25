/**
 * @file sstf.cpp
 * @brief Shortest Seek Time First (SSTF) Disk Scheduling Algorithm.
 *
 * CONCEPT:
 *   - Greedy disk scheduling policy.
 *   - Selects the request with the minimum seek distance from the current head position.
 *   - Significantly reduces total head movement compared to FCFS.
 *
 * CONS:
 *   - Can cause Starvation for requests far away from the head if a continuous stream
 *     of requests arrives near the head.
 */

#include "disk_scheduling/algorithms/sstf.h"
#include <cmath>
#include <algorithm>

DiskScheduleResult SSTFDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    DiskScheduleResult result;
    result.algorithmName = "SSTF";
    result.initialHead = initialHead;
    result.totalHeadMovement = 0;
    
    std::vector<int> pendingRequests = requests;
    int currentHead = initialHead;
    
    // Service closest request until all pending requests are handled
    while (!pendingRequests.empty()) {
        // Step 1: Search for request with minimum seek distance
        auto closestIt = pendingRequests.begin();
        int minDistance = std::abs(*closestIt - currentHead);
        
        for (auto it = pendingRequests.begin() + 1; it != pendingRequests.end(); ++it) {
            int distance = std::abs(*it - currentHead);
            if (distance < minDistance) {
                minDistance = distance;
                closestIt = it;
            }
        }
        
        // Step 2: Move head to closest request and record stats
        int nextTrack = *closestIt;
        result.seekSequence.push_back(nextTrack);
        result.totalHeadMovement += minDistance;
        currentHead = nextTrack;
        
        // Step 3: Remove serviced request from pending list
        pendingRequests.erase(closestIt);
    }
    
    return result;
}
