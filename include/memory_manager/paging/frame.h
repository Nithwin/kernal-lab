#pragma once

class Frame
{
private:
    int frameNumber;

    int pid;
    int pageNumber;

    bool free;

public:
    Frame(int frameNumber);

    int getFrameNumber() const;
    int getPid() const;
    int getPageNumber() const;
    bool isFree() const;

    void setPid(int pid);
    void setPageNumber(int pageNumber);
    void setFree(bool free);

    void clear();
};