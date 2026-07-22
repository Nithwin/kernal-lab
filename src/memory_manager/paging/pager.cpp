#include "memory_manager/paging/pager.h"

Pager::Pager(int numberOfFrames, int pageSize)
    : pageSize(pageSize)
{
    for (int i = 0; i < numberOfFrames; i++)
    {
        frames.emplace_back(i);
    }
}

Frame *Pager::findFreeFrame()
{
    for (Frame &frame : frames)
    {
        if (frame.isFree())
        {
            return &frame;
        }
    }

    return nullptr;
}

bool Pager::loadProcess(const Process &process)
{
    int pid = process.getPid();

    if (pageTables.find(pid) != pageTables.end())
    {
        return false;
    }

    int pagesNeeded =
        (process.getMemorySize() + pageSize - 1) / pageSize;

    PageTable pageTable(pid);

    std::vector<Frame *> allocatedFrames;

    for (int pageNumber = 0;
         pageNumber < pagesNeeded;
         pageNumber++)
    {
        Frame *frame = findFreeFrame();

        if (frame == nullptr)
        {
            // Rollback
            for (Frame *allocated : allocatedFrames)
            {
                allocated->clear();
            }

            return false;
        }

        frame->setFree(false);
        frame->setPid(pid);
        frame->setPageNumber(pageNumber);

        allocatedFrames.push_back(frame);

        Page page(pid, pageNumber);

        page.setLoaded(true);
        page.setFrameNumber(frame->getFrameNumber());

        pageTable.addPage(page);
    }

    pageTables[pid] = pageTable;

    return true;
}

bool Pager::deallocateProcess(int pid)
{
    auto it = pageTables.find(pid);

    if (it == pageTables.end())
    {
        return false;
    }

    for (Frame &frame : frames)
    {
        if (frame.getPid() == pid)
        {
            frame.clear();
        }
    }

    pageTables.erase(it);

    return true;
}

const std::vector<Frame> &Pager::getFrames() const
{
    return frames;
}

const std::unordered_map<int, PageTable> &
Pager::getPageTables() const
{
    return pageTables;
}

int Pager::translateAddress(int pid, int logicalAddress)
{
    auto process = pageTables.find(pid);

    if (process == pageTables.end())
    {
        return -1;
    }

    PageTable &pageTable = process->second;

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if (pageNumber >= pageTable.getPages().size())
    {
        return -1;
    }

    const Page &page = pageTable.getPage(pageNumber);

    if (!page.isLoaded())
    {
        if (!handlePageFault(pid, pageNumber))
        {
            return -1;
        }
    }

    int frameNumber = page.getFrameNumber();

    return frameNumber * pageSize + offset;
}

bool Pager::handlePageFault(int pid, int pageNumber)
{
    auto process = pageTables.find(pid);

    if (process == pageTables.end())
    {
        return false;
    }

    PageTable &table = process->second;

    Page &page = table.getPage(pageNumber);

    if (page.isLoaded())
    {
        return true;
    }

    Frame *frame = findFreeFrame();

    if (frame == nullptr)
    {
        return false;
    }

    frame->setFree(false);
    frame->setPid(pid);
    frame->setPageNumber(pageNumber);

    page.setFrameNumber(frame->getFrameNumber());
    page.setLoaded(true);

    return true;
}