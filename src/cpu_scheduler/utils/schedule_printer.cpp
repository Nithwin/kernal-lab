/**
 * @file schedule_printer.cpp
 * @brief Utility for formatting and printing CPU scheduling results in Markdown table format.
 *
 * OUTPUT FORMAT:
 *   Prints a clean Markdown table displaying:
 *   PID | Arrival | Burst | Start | Completion | Waiting | Turnaround | Response
 */

#include "cpu_scheduler/utils/schedule_printer.h"
#include <iomanip>
#include <iostream>

void SchedulePrinter::print(const std::vector<Process>& processes)
{
    std::cout << "| PID | Arrival | Burst | Start | Completion | Waiting | Turnaround | Response |\n";
    std::cout << "| --: | ------: | ----: | ----: | ---------: | ------: | ---------: | -------: |\n";
    for (const auto& process : processes)
    {
        std::cout << " | " << std::setw(3) << process.getPid()
                  << " | " << std::setw(7) << process.getArrivalTime()
                  << " | " << std::setw(5) << process.getBurstTime()
                  << " | " << std::setw(5) << process.getStartTime()
                  << " | " << std::setw(10) << process.getCompletionTime()
                  << " | " << std::setw(7) << process.getWaitingTime()
                  << " | " << std::setw(10) << process.getTurnaroundTime()
                  << " | " << std::setw(8) << process.getResponseTime()
                  << " |\n";
    }
    std::cout << "\n\n";
}