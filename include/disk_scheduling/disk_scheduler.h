#pragma once

#include <vector>
#include <string>

/**
 * @brief Result structure for a disk scheduling algorithm.
 */
struct DiskScheduleResult {
    std::string algorithmName;
    int initialHead;
    int totalHeadMovement;
    std::vector<int> seekSequence;
};

/**
 * @brief Base class for all disk scheduling algorithms.
 * 
 * Provides an interface that all concrete disk scheduling algorithms must implement.
 */
class DiskScheduler {
public:
    virtual ~DiskScheduler() = default;

    /**
     * @brief Schedules the disk requests.
     * 
     * @param initialHead The starting position of the disk head.
     * @param requests A vector of cylinder requests.
     * @param diskSize The total number of cylinders on the disk (default 200).
     * @return DiskScheduleResult Contains the seek sequence and total head movement.
     */
    virtual DiskScheduleResult schedule(int initialHead, const std::vector<int>& requests, int diskSize = 200) = 0;
};
