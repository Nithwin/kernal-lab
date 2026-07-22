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

int main()
{
    WorstFit memory(1000);

    memory.allocate(1, 200);
    memory.allocate(2, 300);
    memory.allocate(3, 100);

    memory.deallocate(1);
    memory.deallocate(3);

    MemoryPrinter::print(memory.getBlocks());

    memory.allocate(4, 90);

    MemoryPrinter::print(memory.getBlocks());
    return 0;
}