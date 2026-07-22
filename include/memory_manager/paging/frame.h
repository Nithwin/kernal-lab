#pragma once

class Frame
{
private:
    int frameNumber;
    int pageNumber;
    bool free;

public:
    Frame(int frameNumber);

    int getFrameNumber() const;
    int getPageNumber() const;
    bool isFree() const;

    void setPageNumber(int pageNumber);
    void setFree(bool free);
};