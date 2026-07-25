#include "disk_scheduling/algorithms/fcfs.h"
#include <cmath>

DiskScheduleResult FCFSDiskScheduler::schedule(int initialHead, const std::vector<int>& requests, int diskSize) {
    DiskScheduleResult result;
    result.algorithmName = "FCFS";
    result.initialHead = initialHead;
    result.totalHeadMovement = 0;
    
    int currentHead = initialHead;
    
    for (int request : requests) {
        result.seekSequence.push_back(request);
        result.totalHeadMovement += std::abs(request - currentHead);
        currentHead = request;
    }
    
    return result;
}
