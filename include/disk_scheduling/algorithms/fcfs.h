#pragma once

#include "disk_scheduling/disk_scheduler.h"

/**
 * @brief First-Come, First-Served (FCFS) Disk Scheduling Algorithm.
 * 
 * Services requests in the exact order they arrive in the queue.
 */
class FCFSDiskScheduler : public DiskScheduler {
public:
    DiskScheduleResult schedule(int initialHead, const std::vector<int>& requests, int diskSize = 200) override;
};
