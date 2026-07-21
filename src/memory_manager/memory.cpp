#include "memory_manager/memory.h"

Memory::Memory(
    int startAddress, int size
) : startAddress(startAddress),
    size(size),
    allocated(false),
    pid(-1)

{

}


int Memory::getStartAddress() const
{
    return startAddress;
}

int Memory::getSize() const
{
    return size;
}

bool Memory::getIsAllocated() const
{
    return allocated;
}

int Memory::getPid() const
{
    return pid;
}

// Setters 

void Memory::setIsAllocated(bool allocated)
{
    this->allocated = allocated;
}

void Memory::setPid(int pid)
{
    this->pid = pid;
}

void Memory::setSize(int size){
    this->size = size;
}