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

    std::cout << "Initial Memory\n";
    MemoryPrinter::print(memory.getBlocks());

    memory.allocate(1, 200);
    std::cout << "\nAfter Allocating PID 1 (200)\n";
    MemoryPrinter::print(memory.getBlocks());

    memory.allocate(2, 300);
    std::cout << "\nAfter Allocating PID 2 (300)\n";
    MemoryPrinter::print(memory.getBlocks());

    memory.allocate(3, 100);
    std::cout << "\nAfter Allocating PID 3 (100)\n";
    MemoryPrinter::print(memory.getBlocks());
    return 0;
}