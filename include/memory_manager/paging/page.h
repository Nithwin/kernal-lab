#pragma once

class Page
{
private:
    int pid;
    int pageNumber;
    int frameNumber;
    bool loaded;

public:
    Page(int pid, int pageNumber);

    int getPid() const;
    int getPageNumber() const;
    int getFrameNumber() const;
    bool isLoaded() const;

    void setFrameNumber(int frameNumber);
    void setLoaded(bool loaded);
};