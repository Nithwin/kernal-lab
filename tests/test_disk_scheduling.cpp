#include <iostream>
#include <vector>
#include "disk_scheduling/algorithms/fcfs.h"
#include "disk_scheduling/algorithms/sstf.h"
#include "disk_scheduling/algorithms/scan.h"
#include "disk_scheduling/algorithms/c_scan.h"

/**
 * @brief Test for the Disk Scheduling Module.
 * 
 * Demonstrates FCFS, SSTF, SCAN, and C-SCAN disk scheduling algorithms.
 */
void printResult(const DiskScheduleResult& result) {
    std::cout << "Algorithm: " << result.algorithmName << "\n";
    std::cout << "Total Head Movement: " << result.totalHeadMovement << "\n";
    std::cout << "Seek Sequence: ";
    for (int track : result.seekSequence) {
        std::cout << track << " ";
    }
    std::cout << "\n\n";
}

int main() {
    std::cout << "--- Disk Scheduling Module Test ---\n\n";
    
    std::vector<int> requests = {82, 170, 43, 140, 24, 16, 190};
    int initialHead = 50;

    std::cout << "Initial Head Position: " << initialHead << "\n";
    std::cout << "Requests: ";
    for (int r : requests) std::cout << r << " ";
    std::cout << "\n\n";

    FCFSDiskScheduler fcfs;
    printResult(fcfs.schedule(initialHead, requests));

    SSTFDiskScheduler sstf;
    printResult(sstf.schedule(initialHead, requests));

    SCANDiskScheduler scan(true); // Moving up
    printResult(scan.schedule(initialHead, requests));

    CSCANDiskScheduler cscan;
    printResult(cscan.schedule(initialHead, requests));

    return 0;
}
