#include "disk_scheduling/algorithms/c_scan.h"
#include <cmath>
#include <algorithm>

DiskScheduleResult CSCANDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    DiskScheduleResult result;
    result.algorithmName = "C-SCAN";
    result.initialHead = initialHead;
    result.totalHeadMovement = 0;
    
    std::vector<int> left, right;
    
    for (int req : requests) {
        if (req < initialHead)
            left.push_back(req);
        else
            right.push_back(req);
    }
    
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    int currentHead = initialHead;
    
    // First, go right to the end of the disk
    for (int req : right) {
        result.seekSequence.push_back(req);
        result.totalHeadMovement += std::abs(req - currentHead);
        currentHead = req;
    }
    
    // Jump to the end (if there are left requests to process)
    if (!left.empty()) {
        result.seekSequence.push_back(diskSize - 1);
        result.totalHeadMovement += std::abs(diskSize - 1 - currentHead);
        currentHead = diskSize - 1;
        
        // Jump to the start of the disk (0) - This is considered a seek 
        // Some variants consider it as cost 0, we'll consider it as distance.
        result.seekSequence.push_back(0);
        result.totalHeadMovement += std::abs(currentHead - 0);
        currentHead = 0;
        
        // Now process left side from start to the initial point
        for (int req : left) {
            result.seekSequence.push_back(req);
            result.totalHeadMovement += std::abs(req - currentHead);
            currentHead = req;
        }
    }
    
    return result;
}
