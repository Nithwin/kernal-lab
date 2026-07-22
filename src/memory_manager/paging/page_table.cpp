#include "memory_manager/paging/page_table.h"

PageTable::PageTable(int numberOfPages)
{
    for (int i = 0; i < numberOfPages; i++)
    {
        pages.emplace_back(i);
    }
}

Page& PageTable::getPage(int pageNumber)
{
    return pages[pageNumber];
}

const std::vector<Page>& PageTable::getPages() const
{
    return pages;
}