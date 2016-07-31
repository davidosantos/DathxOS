/* 
 * File:   pageManagment.cpp
 * Author: david
 * 
 * Created on 7 de Novembro de 2015, 16:12
 */

#include "physManagment.h"


physManagment::bitMapPage *physManagment::bitMapPagePointer;

u32 physManagment::totalPages;
u32 physManagment::totalCountReserved; //This pages are reserved for memory manager. Each page manage 128MB
u32 physManagment::lastPagesBitCount;

void physManagment::setup(u32 totalPages) {
    physManagment::totalPages = totalPages;
    totalCountReserved = totalPages / (sizeof (bitMapPage) * byteSize);
    totalCountReserved++; //because pages has base of 0
//    u32 currentPage = ((u32) ((u32) baseMemoryPointer + usedMemoryCounter + pageSize) >> 12);
//    usedMemoryCounter += (pageSize*totalPages);
    
            
    bitMapPagePointer = (bitMapPage*)baseMemoryPointer;
    u32 *to = (u32*)((((u32)bitMapPagePointer>>12)+totalCountReserved) *pageSize);
    physManagment::setRangeBusy((u32*)bitMapPagePointer,to);
    //bitMapPagePointer = new bitMapPage [sizeof (bitMapPage) * totalCount];
    u32 pagesToMark = ((u32) bitMapPagePointer >> 12);
    for (u16 i = 0; i < totalCountReserved; i++) {
        physManagment::clearPage((bitMapPage*) (pagesToMark * pageSize));
        physManagment::setBusy((u32*) (pagesToMark * pageSize));
        pagesToMark++;
    }
}

void physManagment::setBusy(u32 *adrss) {
    if (((u32) adrss >> 12) > totalPages)
        return;
    u32 pageIndex = ((u32) adrss >> 12) / sizeof (bitMapPage);
    u32 byteIndex = ((u32) adrss >> 12) / byteSize;
    u32 bitIndex = ((u32) adrss >> 12) % byteSize;

    physManagment::bitMapPagePointer[pageIndex].bytes[byteIndex].setBit(bitIndex, used);
}
void physManagment::setRangeBusy(u32 *from, u32 *to) {
    u32 start = (u32) from >> 12;
    u32 end = (u32) to >> 12;
    for(;start <= end;start++){
        physManagment::setBusy((u32*)(start*pageSize));
    }
}

void physManagment::setFree(u32 *adrss) {
    if (((u32) adrss >> 12) > totalPages)
        return;
    u32 pageIndex = ((u32) adrss >> 12) / sizeof (bitMapPage);
    u32 byteIndex = ((u32) adrss >> 12) / byteSize;
    u32 bitIndex = ((u32) adrss >> 12) % byteSize;

    physManagment::bitMapPagePointer[pageIndex].bytes[byteIndex].setBit(bitIndex, free);
}

void physManagment::clearPage(bitMapPage *adrss) {
    for (u32 i = 0; i < sizeof (bitMapPage) / 4; i++)
        adrss->ints[i] = 0;
}

u32 *physManagment::getFree() {
    u32 pageRet = 0;
    for (u32 pageIndex = 0; pageIndex < totalCountReserved; pageIndex++) {
        for (u32 byteIndex = 0; byteIndex < sizeof (bitMapPage); byteIndex++) {
            for (u32 bitIndex = 0; bitIndex < byteSize; bitIndex++) {
                if (physManagment::bitMapPagePointer[pageIndex].bytes[byteIndex]
                        .getBit(bitIndex) == free) {
                    physManagment::bitMapPagePointer[pageIndex].bytes[byteIndex]
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

