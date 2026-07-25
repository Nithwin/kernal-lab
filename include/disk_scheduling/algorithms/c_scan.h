#pragma once

#include "disk_scheduling/disk_scheduler.h"

/**
 * @brief Circular SCAN (C-SCAN) Disk Scheduling Algorithm.
 * 
 * Similar to SCAN, but when it reaches the end of the disk, it returns to the
 * beginning of the disk without servicing any requests on the return trip.
 */
class CSCANDiskScheduler : public DiskScheduler {
public:
    DiskScheduleResult schedule(int initialHead, const std::vector<int>& requests, int diskSize = 200) override;
};
