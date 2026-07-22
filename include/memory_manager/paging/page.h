#pragma once

class Page
{
private:
    int pageNumber;
    int frameNumber;
    bool loaded;

public:
    Page(int pageNumber);

    int getPageNumber() const;
    int getFrameNumber() const;
    bool isLoaded() const;

    void setFrameNumber(int frameNumber);
    void setLoaded(bool loaded);
};