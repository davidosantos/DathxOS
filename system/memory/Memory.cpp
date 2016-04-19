
#include "Memory.h"

void *operator new( unsigned int size) {

    bool firstPage = true;
    u32 *pageAddrs;
    if (size == pageSize) {

        return (u32*) Paging::getNewPage();
    } else {
        for (u32 i = 0; i <= size / pageSize; i++) {
            u32 *addrs = Paging::getNewPage();
            if (firstPage) {
                firstPage = false;
                pageAddrs = addrs;
            }
        }
    }
    return pageAddrs;

    //    if ((baseMemoryPointer + (usedMemoryCounter + size)) <= topMemoryPointer) {
    //        usedMemoryCounter += size;
    //        
    //        if(PagingEnabled){
    //            Paging::allocPage(((u32) baseMemoryPointer + (usedMemoryCounter - size)),size/pageSize);
    //        }
    //        return (u32*) ((u32) baseMemoryPointer + usedMemoryCounter - size); //calc the base to return;
    //    } else {
    //
    //        return topMemoryPointer; //teste
    //    }
    //    topMemoryPointer++; //Point to first unused byte
    //    topMemoryPointer += size; //points to the last used byte
    //    
    //    usedMemoryCounter += size; //calc the used bytes * 4 bytes each allocation
    //    return (void *) base;
}

void *operator new[](unsigned int size) {
   bool firstPage = true;
    u32 *pageAddrs;
    if (size == pageSize) {

        return (u32*) Paging::getNewPage();
    } else {
        for (u32 i = 0; i <= size / pageSize; i++) {
            u32 *addrs = Paging::getNewPage();
            if (firstPage) {
                firstPage = false;
                pageAddrs = addrs;
            }
        }
    }
    return pageAddrs;
    //    if ((baseMemoryPointer + (usedMemoryCounter + size)) <= topMemoryPointer) {
    //        usedMemoryCounter += size;
    //        if(PagingEnabled){
    //            Paging::allocPage(((u32) baseMemoryPointer + usedMemoryCounter - size),size/pageSize);
    //        }
    //        return (u32*) ((u32) baseMemoryPointer + usedMemoryCounter - size); //calc the base to return;
    //    } else {
    //
    //        return topMemoryPointer; //teste
    //    }
}
//
//void operator delete(void *p) {
//}
//
//void operator delete[](void *p) {
//}

u32 getUsedMemory() {
  return 0;//  return (u32) baseMemoryPointer + usedMemoryCounter;
}

