#include "memory_manager/paging/frame.h"

Frame::Frame(int frameNumber)
    : frameNumber(frameNumber),
      pid(-1),
      pageNumber(-1),
      free(true)
{
}

int Frame::getFrameNumber() const
{
    return frameNumber;
}

int Frame::getPid() const
{
    return pid;
}

int Frame::getPageNumber() const
{
    return pageNumber;
}

bool Frame::isFree() const
{
    return free;
}

void Frame::setPid(int pid)
{
    this->pid = pid;
}

void Frame::setPageNumber(int pageNumber)
{
    this->pageNumber = pageNumber;
}

void Frame::setFree(bool free)
{
    this->free = free;
}

void Frame::clear()
{
    pid = -1;
    pageNumber = -1;
    free = true;
}