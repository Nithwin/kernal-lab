#pragma once

class Memory
{
private:
    int startAddress;
    int size;
    bool allocated;
    int pid;
public:
    Memory(int startAddress, int size);

    //Getters
    int getStartAddress() const;
    int getSize() const;
    bool getIsAllocated() const;
    int getPid() const;


    // Setters
    void setIsAllocated(bool allocated);
    void setPid(int pid);
};