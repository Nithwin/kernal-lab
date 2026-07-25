/**
 * @file page_table.cpp
 * @brief Process Page Table implementation mapping logical pages to physical frames.
 *
 * CONCEPT:
 *   Every process has its own Page Table maintained by the OS.
 *   The Page Table acts as an array/vector indexed by Page Number.
 *   Each entry maps `Logical Page Number -> Physical Frame Number`.
 */

#include "memory_manager/paging/page_table.h"

PageTable::PageTable() : pid(-1) {}

PageTable::PageTable(int pid) : pid(pid) {}

int PageTable::getPid() const { return pid; }

void PageTable::addPage(const Page& page)
{
    pages.push_back(page);
}

Page& PageTable::getPage(int pageNumber)
{
    return pages[pageNumber];
}

const std::vector<Page>& PageTable::getPages() const
{
    return pages;
}