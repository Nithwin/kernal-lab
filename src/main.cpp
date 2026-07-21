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

int main()
{
    FirstFit memory(1024);

    memory.allocate(1, 200);
    memory.allocate(2, 300);
    memory.allocate(3, 100);

    std::cout << "Initial Layout\n";
    MemoryPrinter::print(memory.getBlocks());

    std::cout << "\nDeallocate PID 2\n";
    memory.deallocate(2);
    MemoryPrinter::print(memory.getBlocks());

    std::cout << "\nDeallocate PID 3\n";
    memory.deallocate(3);
    MemoryPrinter::print(memory.getBlocks());

    return 0;
}