#pragma once

#include "memory_manager/paging/page.h"

#include <vector>

class PageTable
{
private:
    int pid;
    std::vector<Page> pages;

public:
    PageTable();
    PageTable(int pid);

    int getPid() const;

    void addPage(const Page& page);

    Page& getPage(int pageNumber);

    const std::vector<Page>& getPages() const;
};