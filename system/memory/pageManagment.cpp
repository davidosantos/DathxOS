/* 
 * File:   pageManagment.cpp
 * Author: david
 * 
 * Created on 7 de Novembro de 2015, 16:12
 */

#include "pageManagment.h"


pageManagment::bitMapPage *pageManagment::bitMapPagePointer;

u32 pageManagment::totalPages;
u32 pageManagment::totalCountReserved; //This pages are reserved for memory manager. Each page manage 128MB
u32 pageManagment::lastPagesBitCount;

void pageManagment::setup(u32 totalPages) {
    pageManagment::totalPages = totalPages;
    totalCountReserved = totalPages / (sizeof (bitMapPage) * byteSize);
    totalCountReserved++; //because pages has base of 0
//    u32 currentPage = ((u32) ((u32) baseMemoryPointer + usedMemoryCounter + pageSize) >> 12);
//    usedMemoryCounter += (pageSize*totalPages);
    
            
    bitMapPagePointer = (bitMapPage*)baseMemoryPointer;
    u32 *to = (u32*)((((u32)bitMapPagePointer>>12)+totalCountReserved) *pageSize);
    pageManagment::setRangeBusy((u32*)bitMapPagePointer,to);
    //bitMapPagePointer = new bitMapPage [sizeof (bitMapPage) * totalCount];
    u32 pagesToMark = ((u32) bitMapPagePointer >> 12);
    for (u16 i = 0; i < totalCountReserved; i++) {
        pageManagment::clearPage((bitMapPage*) (pagesToMark * pageSize));
        pageManagment::setBusy((u32*) (pagesToMark * pageSize));
        pagesToMark++;
    }
}

void pageManagment::setBusy(u32 *adrss) {
    if (((u32) adrss >> 12) > totalPages)
        return;
    u32 pageIndex = ((u32) adrss >> 12) / sizeof (bitMapPage);
    u32 byteIndex = ((u32) adrss >> 12) / byteSize;
    u32 bitIndex = ((u32) adrss >> 12) % byteSize;

    pageManagment::bitMapPagePointer[pageIndex].bytes[byteIndex].setBit(bitIndex, used);
}
void pageManagment::setRangeBusy(u32 *from, u32 *to) {
    u32 start = (u32) from >> 12;
    u32 end = (u32) to >> 12;
    for(;start <= end;start++){
        pageManagment::setBusy((u32*)(start*pageSize));
    }
}

void pageManagment::setFree(u32 *adrss) {
    if (((u32) adrss >> 12) > totalPages)
        return;
    u32 pageIndex = ((u32) adrss >> 12) / sizeof (bitMapPage);
    u32 byteIndex = ((u32) adrss >> 12) / byteSize;
    u32 bitIndex = ((u32) adrss >> 12) % byteSize;

    pageManagment::bitMapPagePointer[pageIndex].bytes[byteIndex].setBit(bitIndex, free);
}

void pageManagment::clearPage(bitMapPage *adrss) {
    for (u32 i = 0; i < sizeof (bitMapPage) / 4; i++)
        adrss->ints[i] = 0;
}

u32 *pageManagment::getFree() {
    u32 pageRet = 0;
    for (u32 pageIndex = 0; pageIndex < totalCountReserved; pageIndex++) {
        for (u32 byteIndex = 0; byteIndex < sizeof (bitMapPage); byteIndex++) {
            for (u32 bitIndex = 0; bitIndex < byteSize; bitIndex++) {
                if (pageManagment::bitMapPagePointer[pageIndex].bytes[byteIndex]
                        .getBit(bitIndex) == free) {
                    pageManagment::bitMapPagePointer[pageIndex].bytes[byteIndex]
                            .setBit(bitIndex, used);
                    if(pageRet <= totalPages){
                    return (u32*) (pageRet * pageSize);
                    } else{
                        return (u32*) - 1;
                    }
                }
                pageRet++;
            }
        }
    }
    return (u32*) - 1;
}


//pageManagment::pageManagment() {
//}
//
//pageManagment::pageManagment(const pageManagment& orig) {
//}
//
//pageManagment::~pageManagment() {
//}

