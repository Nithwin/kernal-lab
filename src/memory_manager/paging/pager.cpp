#include "memory_manager/paging/pager.h"

Pager::Pager(int numberOfFrames, int pageSize)
    : pageSize(pageSize)
{
    for (int i = 0; i < numberOfFrames; i++)
    {
        frames.emplace_back(i);
    }
}

Frame* Pager::findFreeFrame()
{
    for (Frame& frame : frames)
    {
        if (frame.isFree())
        {
            return &frame;
        }
    }

    return nullptr;
}

bool Pager::loadProcess(const Process& process)
{
    int pid = process.getPid();

    if (pageTables.find(pid) != pageTables.end())
    {
        return false;
    }

    int pagesNeeded =
        (process.getMemorySize() + pageSize - 1) / pageSize;

    PageTable pageTable(pid);

    std::vector<Frame*> allocatedFrames;

    for (int pageNumber = 0;
         pageNumber < pagesNeeded;
         pageNumber++)
    {
        Frame* frame = findFreeFrame();

        if (frame == nullptr)
        {
            // Rollback
            for (Frame* allocated : allocatedFrames)
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

    for (Frame& frame : frames)
    {
        if (frame.getPid() == pid)
        {
            frame.clear();
        }
    }

    pageTables.erase(it);

    return true;
}

const std::vector<Frame>& Pager::getFrames() const
{
    return frames;
}

const std::unordered_map<int, PageTable>&
Pager::getPageTables() const
{
    return pageTables;
}