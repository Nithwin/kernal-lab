/**
 * @file page.cpp
 * @brief Represents a single logical memory Page.
 *
 * CONCEPT:
 *   Logical memory (process address space) is divided into fixed-size chunks called PAGES.
 *   Page size equals Frame size.
 *   Each page tracks:
 *   - PID: Owner process ID.
 *   - Page Number: Logical page index (0, 1, 2...).
 *   - Frame Number: The physical RAM frame mapped to this page (-1 if swapped/unmapped).
 *   - Loaded Flag: Present bit (true if loaded in physical RAM, false if page fault).
 */

#include "memory_manager/paging/page.h"

Page::Page(int pid, int pageNumber)
    : pid(pid),
      pageNumber(pageNumber),
      frameNumber(-1),
      loaded(false)
{
}

int Page::getPageNumber() const { return pageNumber; }
int Page::getFrameNumber() const { return frameNumber; }
bool Page::isLoaded() const { return loaded; }
int Page::getPid() const { return pid; }

void Page::setFrameNumber(int frameNumber) { this->frameNumber = frameNumber; }
void Page::setLoaded(bool loaded) { this->loaded = loaded; }