/**
 * @file memory_printer.cpp
 * @brief Formatting and printing utilities for Memory Allocation and Paging States.
 *
 * FUNCTIONS:
 *   - print(): Displays a clean Markdown table of contiguous memory blocks.
 *   - page_print(): Displays comprehensive status of Physical Memory frames,
 *                   Page Tables per process, and Overall Memory Usage summary statistics.
 */

#include "memory_manager/utils/memory_printer.h"
#include "memory_manager/paging/pager.h"

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

void MemoryPrinter::page_print(const Pager& pager)
{
    using std::cout;
    using std::left;
    using std::setw;

    cout << "\n";
    cout << "=============================================================\n";
    cout << "                  MEMORY MANAGEMENT STATE\n";
    cout << "=============================================================\n\n";

    // ------------------------------------------------------------
    // 1. Physical Memory Frame Status
    // ------------------------------------------------------------

    cout << "PHYSICAL MEMORY\n";
    cout << "-------------------------------------------------------------\n";

    cout << left
         << setw(10) << "Frame"
         << setw(10) << "PID"
         << setw(10) << "Page"
         << setw(10) << "Free"
         << '\n';

    cout << "-------------------------------------------------------------\n";

    int usedFrames = 0;

    for (const Frame& frame : pager.getFrames())
    {
        if (!frame.isFree())
            usedFrames++;

        cout << left
             << setw(10) << frame.getFrameNumber()
             << setw(10) << frame.getPid()
             << setw(10) << frame.getPageNumber()
             << setw(10) << (frame.isFree() ? "Yes" : "No")
             << '\n';
    }

    // ------------------------------------------------------------
    // 2. Page Tables per Process
    // ------------------------------------------------------------

    cout << "\nPAGE TABLES\n";
    cout << "-------------------------------------------------------------\n";

    for (const auto& entry : pager.getPageTables())
    {
        const PageTable& table = entry.second;

        cout << "\nProcess " << table.getPid() << "\n\n";

        cout << left
             << setw(10) << "Page"
             << setw(10) << "Frame"
             << setw(10) << "Present"
             << '\n';

        cout << "------------------------------\n";

        for (const Page& page : table.getPages())
        {
            cout << left
                 << setw(10) << page.getPageNumber()
                 << setw(10) << page.getFrameNumber()
                 << setw(10) << (page.isLoaded() ? "Yes" : "No")
                 << '\n';
        }
    }

    // ------------------------------------------------------------
    // 3. System Memory Summary Statistics
    // ------------------------------------------------------------

    int totalFrames = pager.getFrames().size();
    int freeFrames = totalFrames - usedFrames;

    cout << "\n=============================================================\n";
    cout << "SUMMARY\n";
    cout << "-------------------------------------------------------------\n";
    cout << "Total Frames : " << totalFrames << '\n';
    cout << "Used Frames  : " << usedFrames << '\n';
    cout << "Free Frames  : " << freeFrames << '\n';
    cout << "Memory Usage : "
         << (usedFrames * 100 / totalFrames)
         << "%\n";
    cout << "=============================================================\n";
}