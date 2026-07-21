#include "memory_manager/utils/memory_printer.h"

#include <iomanip>
#include <iostream>

void MemoryPrinter::print(const std::vector<Memory> &blocks)
{
    std::cout << "| Status | PID | Start | Size |\n";
    std::cout << "| -----: | --: | ----: | ---: |\n";

    for (const auto &block : blocks)
    {
        std::cout << "| "
                  << std::setw(6)
                  << (block.getIsAllocated() ? "Used" : "Free")
                  << " | ";

        if (block.getIsAllocated())
        {
            std::cout << std::setw(3) << block.getPid();
        }
        else
        {
            std::cout << std::setw(3) << "-";
        }

        std::cout << " | ";

        std::cout << std::setw(5) << block.getStartAddress()
                  << " | "
                  << std::setw(4) << block.getSize()
                  << " |\n";
    }
}