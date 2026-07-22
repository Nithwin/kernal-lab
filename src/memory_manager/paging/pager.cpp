#include "memory_manager/paging/pager.h"

Pager::Pager(int numberOfFrames,
             int numberOfPages)
    : pageTable(numberOfPages)
{
    for (int i = 0; i < numberOfFrames; i++)
    {
        frames.emplace_back(i);
    }
}

bool Pager::loadPage(int pageNumber)
{
    Page& page = pageTable.getPage(pageNumber);

    if (page.isLoaded())
    {
        return true;
    }

    for (Frame& frame : frames)
    {
        if (frame.isFree())
        {
            frame.setFree(false);
            frame.setPageNumber(pageNumber);

            page.setLoaded(true);
            page.setFrameNumber(frame.getFrameNumber());

            return true;
        }
    }

    return false;
}

const std::vector<Frame>& Pager::getFrames() const
{
    return frames;
}

const PageTable& Pager::getPageTable() const
{
    return pageTable;
}