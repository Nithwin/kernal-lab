#include "disk_scheduling/algorithms/scan.h"
#include <cmath>
#include <algorithm>

DiskScheduleResult SCANDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    DiskScheduleResult result;
    result.algorithmName = "SCAN";
    result.initialHead = initialHead;
    result.totalHeadMovement = 0;
    
    std::vector<int> left, right;
    
    // Divide requests into left and right of the initial head
    for (int req : requests) {
        if (req < initialHead)
            left.push_back(req);
        else
            right.push_back(req);
    }
    
    // Sort both vectors
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    int currentHead = initialHead;
    
    // Process based on direction
    int run = 2; // We run max 2 directions
    bool movingUp = directionUp;
    
    while (run--) {
        if (movingUp) {
            for (int req : right) {
                result.seekSequence.push_back(req);
                result.totalHeadMovement += std::abs(req - currentHead);
                currentHead = req;
            }
            if (run > 0 && !left.empty()) { // Move to end of disk before reversing
                result.seekSequence.push_back(diskSize - 1);
                result.totalHeadMovement += std::abs(diskSize - 1 - currentHead);
                currentHead = diskSize - 1;
            }
            movingUp = false; // reverse direction
        } else {
            for (auto it = left.rbegin(); it != left.rend(); ++it) {
                result.seekSequence.push_back(*it);
                result.totalHeadMovement += std::abs(*it - currentHead);
                currentHead = *it;
            }
            if (run > 0 && !right.empty()) { // Move to start of disk before reversing
                result.seekSequence.push_back(0);
                result.totalHeadMovement += std::abs(currentHead - 0);
                currentHead = 0;
            }
            movingUp = true; // reverse direction
        }
    }
    
    return result;
}
