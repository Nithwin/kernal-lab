#include "memory_manager/paging/frame.h"

Frame::Frame(int frameNumber)
    : frameNumber(frameNumber),
      pageNumber(-1),
      free(true)
{
}

int Frame::getFrameNumber() const
{
    return frameNumber;
}

int Frame::getPageNumber() const
{
    return pageNumber;
}

bool Frame::isFree() const
{
    return free;
}

void Frame::setPageNumber(int pageNumber)
{
    this->pageNumber = pageNumber;
}

void Frame::setFree(bool free)
{
    this->free = free;
}