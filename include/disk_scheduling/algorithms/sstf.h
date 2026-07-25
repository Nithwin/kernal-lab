#pragma once

#include "disk_scheduling/disk_scheduler.h"

/**
 * @brief Shortest Seek Time First (SSTF) Disk Scheduling Algorithm.
 * 
 * Selects the request with the minimum seek time from the current head position.
 */
class SSTFDiskScheduler : public DiskScheduler {
public:
    DiskScheduleResult schedule(int initialHead, const std::vector<int>& requests, int diskSize = 200) override;
};
