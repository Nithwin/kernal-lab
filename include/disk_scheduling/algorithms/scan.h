#pragma once

#include "disk_scheduling/disk_scheduler.h"

/**
 * @brief SCAN Disk Scheduling Algorithm (Elevator Algorithm).
 * 
 * The disk arm starts at one end of the disk and moves toward the other end, 
 * servicing requests as it reaches each cylinder, until it gets to the other end.
 */
class SCANDiskScheduler : public DiskScheduler {
private:
    bool directionUp; // True for moving towards higher cylinder numbers

public:
    SCANDiskScheduler(bool directionUp = true) : directionUp(directionUp) {}
    
    DiskScheduleResult schedule(int initialHead, const std::vector<int>& requests, int diskSize = 200) override;
};
