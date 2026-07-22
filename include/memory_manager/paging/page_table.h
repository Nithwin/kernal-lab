#pragma once

#include "memory_manager/paging/page.h"

#include <vector>

class PageTable
{
private:
    std::vector<Page> pages;

public:
    PageTable(int numberOfPages);

    Page& getPage(int pageNumber);

    const std::vector<Page>& getPages() const;
};