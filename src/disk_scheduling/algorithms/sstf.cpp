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
    
    while (!pendingRequests.empty()) {
        // Find the closest request
        auto closestIt = pendingRequests.begin();
        int minDistance = std::abs(*closestIt - currentHead);
        
        for (auto it = pendingRequests.begin() + 1; it != pendingRequests.end(); ++it) {
            int distance = std::abs(*it - currentHead);
            if (distance < minDistance) {
                minDistance = distance;
                closestIt = it;
            }
        }
        
        // Service the closest request
        int nextTrack = *closestIt;
        result.seekSequence.push_back(nextTrack);
        result.totalHeadMovement += minDistance;
        currentHead = nextTrack;
        
        // Remove from pending
        pendingRequests.erase(closestIt);
    }
    
    return result;
}
