#include "memory_manager/paging/page.h"

Page::Page(int pid, int pageNumber)
    : pid(pid),
      pageNumber(pageNumber),
      frameNumber(-1),
      loaded(false)
{
}

int Page::getPageNumber() const
{
    return pageNumber;
}

int Page::getFrameNumber() const
{
    return frameNumber;
}

bool Page::isLoaded() const
{
    return loaded;
}

int Page::getPid() const
{
    return pid;
}

void Page::setFrameNumber(int frameNumber)
{
    this->frameNumber = frameNumber;
}

void Page::setLoaded(bool loaded)
{
    this->loaded = loaded;
}