/**
 * @file frame.cpp
 * @brief Represents a single physical memory Frame in non-contiguous (paging) memory.
 *
 * CONCEPT:
 *   Physical RAM is divided into fixed-size slots called FRAMES.
 *   Each frame tracks:
 *   - Frame Number: Physical slot index (0, 1, 2...).
 *   - PID: Owner process ID (-1 if free).
 *   - Page Number: Which page of the process is mapped here (-1 if free).
 *   - Free Flag: Whether the frame is available.
 */

#include "memory_manager/paging/frame.h"

Frame::Frame(int frameNumber)
    : frameNumber(frameNumber),
      pid(-1),
      pageNumber(-1),
      free(true)
{
}

int Frame::getFrameNumber() const { return frameNumber; }
int Frame::getPid() const { return pid; }
int Frame::getPageNumber() const { return pageNumber; }
bool Frame::isFree() const { return free; }

void Frame::setPid(int pid) { this->pid = pid; }
void Frame::setPageNumber(int pageNumber) { this->pageNumber = pageNumber; }
void Frame::setFree(bool free) { this->free = free; }

void Frame::clear()
{
    pid = -1;
    pageNumber = -1;
    free = true;
}