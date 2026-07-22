#include <iostream>
#include <vector>
#include <iomanip>
#include <cpu_scheduler/process.h>
#include <cpu_scheduler/algorithms/fcfs.h>
#include <cpu_scheduler/algorithms/sjf.h>
#include <cpu_scheduler/algorithms/srtf.h>
#include <cpu_scheduler/algorithms/priority.h>
#include <cpu_scheduler/algorithms/round_robin.h>
#include <cpu_scheduler/utils/schedule_printer.h>
#include <memory_manager/utils/memory_printer.h>
#include <memory_manager/algorithms/first_fit.h>
#include <memory_manager/algorithms/best_fit.h>
#include <memory_manager/algorithms/next_fit.h>
#include <memory_manager/algorithms/worst_fit.h>
#include <memory_manager/paging/pager.h>

int main()
{
   Pager pager(8, 256);

    Process p1(
        1,
        0,
        5,
        1,
        900
    );

    Process p2(
        2,
        1,
        4,
        2,
        500
    );

    if (pager.loadProcess(p1))
    {
        std::cout << "Process 1 Loaded\n";
    }

    if (pager.loadProcess(p2))
    {
        std::cout << "Process 2 Loaded\n";
    }

    std::cout << "\nFrames\n";
    std::cout << "-----------------------------\n";

    for (const Frame& frame : pager.getFrames())
    {
        std::cout
            << "Frame "
            << frame.getFrameNumber()
            << " | PID = "
            << frame.getPid()
            << " | Page = "
            << frame.getPageNumber()
            << " | Free = "
            << std::boolalpha
            << frame.isFree()
            << '\n';
    }

    std::cout << "\nDeallocating Process 1...\n\n";

    pager.deallocateProcess(1);

    for (const Frame& frame : pager.getFrames())
    {
        std::cout
            << "Frame "
            << frame.getFrameNumber()
            << " | PID = "
            << frame.getPid()
            << " | Page = "
            << frame.getPageNumber()
            << " | Free = "
            << std::boolalpha
            << frame.isFree()
            << '\n';
    }
    return 0;
}