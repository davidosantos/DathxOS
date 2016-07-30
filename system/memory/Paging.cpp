/* 
 * File:   Paging.cpp
 * Author: davidosantos
 * 
 * Created on 1 de Agosto de 2015, 15:46
 */

#include "Paging.h"
#include "Memory.h"
#include "pageManagment.h"

/**
 * Map from 0 to the top provided by topMemory
 * @param topMemory
 */
Paging::Paging() {



}

/**
 * The memory manager will return a page number of the next page after the
 * current page.
 * @return ((u32) currentDir << 16 |  currentPage);
 */
u32 *Paging::getNewPage() {
    u32 *Address = pageManagment::getFree();
    for (int i = 0; i < pageSize / 4; i++) {
        Address[i] = 0; //clean that page
    }
    return Address;
}

Paging::PageDirectory *Paging::getNewDir() {
    PageDirectory *MountDir = new PageDirectory();
    for (u16 i = 0; i < 1024; i++) {
        MountDir->dir[i].all = 0;
    }
    return MountDir;
}

void Paging::allocPage(u32 Address, u16 pages) {
    u32 pdIndex = ((u32) Address >> 22);
    u32 ptIndex = (u32) Address >> 12 & PageEntry_10Bits;
    for (int i = 0; i <= pages; i++, ptIndex++) {
        // if (ppageDir->dir.pageDir[pdIndex].Present == 1) {
        //        PagesTable *pageTable = (PagesTable*) (ppageDir->dir.pageDir[pdIndex].phys * _4kb);
        //   Console::print("Alraedy alloctd: %i",pageTable->page[ptIndex].Present);
        //         pageTable->page[ptIndex].Present = 1;
        //          pageTable->page[ptIndex].phys = ptIndex; // allocate to itself
        if (ptIndex > _1kb) {
            pdIndex++; //no meaning
        }
        //  } else {
        //get page table and convert to physical address
        //         PagesTable *mountTable = (PagesTable*) getNewPage();
        //     Console::print("new dir alloctd: %i");
        //       mountTable->page[ptIndex].Present = 1;
        //       mountTable->page[ptIndex].phys = ptIndex; // allocate to itself
        //         ppageTable = mountTable; //get address

        //        ppageDir->dir.pageDir[pdIndex].phys = ((u32) ppageTable >> 12 & PageEntry_10Bits);
        //   ppageDir->dir.pageDir[pdIndex].Present = 1;
        //    ppageDir->dir.pageDir[pdIndex].unused = 0;
        //   }
    }


}

/**
 * This function is designed to be used by a trusted code thats knows
 * what is doing, this function maps virtual address directly to 
 * physical memory start at physStart, this is so to allow
 * kernel to map virtual memory do the same address as physical
 * @param virtStart
 * @param virtEnd
 * @param physStart
 */
void Paging::mapRange(u32 virtStart, u32 virtEnd, u32 physStart) {

    // Make sure that both addresses are page-aligned.
    u32 pdIndex = ((u32) virtStart >> 22);
    u32 pdIndexEnd = ((u32) virtEnd >> 22); // & 0x03FF;

    u32 ptIndex = (u32) virtStart >> 12 & PageEntry_10Bits;
    u32 ptIndexEnd = (u32) virtEnd >> 12 & PageEntry_10Bits;

    u32 physIndex = (u32) physStart >> 12;

    for (; pdIndex <= pdIndexEnd; pdIndex++) {
        //get page table and convert to physical address
        //  PagesTable *mountTable = (PagesTable*) getNewPage();
        //  ppageTable = mountTable; //get address
        //  ppageDir->dir.pageDir[pdIndex].phys = ((u32) ppageTable >> 12);
        //  ppageDir->dir.pageDir[pdIndex].Present = 1;
        //   ppageDir->dir.pageDir[pdIndex].unused = 0;

        //check whether is is the last page to allocate, if it is
        //then the End will be pdIndexEnd which might be less than _1kb
        u32 End = (pdIndex == pdIndexEnd) ? ptIndexEnd : _1kb;

        for (ptIndex = 0; ptIndex < End; ptIndex++) {
            Console::clear();
            Console::print(3, 0, "pdIndex %i", pdIndex);
            Console::print(5, 0, "ptIndex %i", ptIndex);
            Console::print(7, 0, "physIndex %h", physIndex);
            //      Console::print(9,0,"mountTable %h",(u32)mountTable);

            //      ppageTable->page[ptIndex].phys = physIndex; //might override already defined pages.
            //      ppageTable->page[ptIndex].Present = 1;
            //     ppageTable->page[ptIndex].unused = 0;
            physIndex++;
        }

    }



}

/**
 * @param virtStart - start of virtual address
 * @param virtEnd - this is where virtual address end.
 */
void Paging::mapRange(u32 virtStart, u32 virtEnd, Paging::PageDirectory *pageDir, u32 *physStart, bool user) {

    // Make sure that both addresses are page-aligned.
    u32 pdIndex = ((u32) virtStart >> 22);

    u32 pdIndexEnd = ((u32) virtEnd >> 22); // & 0x03FF;

    u32 ptIndex = (u32) virtStart >> 12 & PageEntry_10Bits;
    u32 ptIndexEnd = (u32) virtEnd >> 12 & PageEntry_10Bits;
    u32 physIndex = (u32) physStart >> 12;

    for (; pdIndex <= pdIndexEnd; pdIndex++) {
        PageTable *pTable;
        //if the page table pointed by pdIndex is already present, the use the same
        if (pageDir->dir[pdIndex].phys && pageDir->dir[pdIndex].Present) {
            pTable = (PageTable*) (pageDir->dir[pdIndex].phys << 12);
        } else {
            //get page table physical address and convert to logical
            pTable = (PageTable*) getNewPage();
            //Console::print("pTable %h", (u32)pTable);
            pageDir->dir[pdIndex].phys = ((u32) pTable >> 12);
            pageDir->dir[pdIndex].Present = 1;
            pageDir->dir[pdIndex].unused = 0;
            if (user) {
                pageDir->dir[pdIndex].User = 1;
                pageDir->dir[pdIndex].Read = 1;
            }
        }
        //check whether is is the last directory to allocate, if it is
        //then the End will be ptIndexEnd which might be less than _1kb
        u32 End = (pdIndex == pdIndexEnd) ? ptIndexEnd : _1kb;

        for (; ptIndex < End; ptIndex++, physIndex++) { //verificar
            pTable->page[ptIndex].phys = physIndex;
            pTable->page[ptIndex].Present = 1;
            if (user) {
                pTable->page[ptIndex].User = 1;
                pTable->page[ptIndex].Read = 1;
            }
        }
        ptIndex = 0;
    }
}

/**
 * This function is designed to map virtual address into physical address
 * the physical address is chosen by function @getNewPage();
 * the start address will always be at virtual address 0.
 * @param virtEnd
 */
//void Paging::mapRange(u32 virtEnd, Paging::PagesDir *pageDir) {
//
//    // Make sure that both addresses are page-aligned.
//
//    u32 pdIndexEnd = ((u32) virtEnd >> 22); // & 0x03FF;
//
//    u32 ptIndexEnd = (u32) virtEnd >> 12 & PageEntry_10Bits;
//
//    for (u32 pdIndex = 0; pdIndex <= pdIndexEnd; pdIndex++) {
//        //get page table and convert to physical address
//        //   PagesTable *mountTable = (PagesTable*) getNewPage();
//        //   ppageTable = mountTable; //get address
//
//        //   ppageDir->dir.pageDir[pdIndex].phys = ((u32) ppageTable >> 12);
//
//        // ppageDir->dir.pageDir[pdIndex].Present = 1;
//        //  ppageDir->dir.pageDir[pdIndex].unused = 0;
//        //check whether is is the last page to allocate, if it is
//        //then the End will be pdIndexEnd whick might be less than _1kb
//        u32 End = (pdIndex == pdIndexEnd) ? ptIndexEnd : _1kb;
//
//        for (u32 ptIndex = 0; ptIndex <= End; ptIndex++) {
//            //       ppageTable->page[ptIndex].phys = getNewPage();
//
//            //      ppageTable->page[ptIndex].Present = 1;
//            //      ppageTable->page[ptIndex].unused = 0;
//        }
//    }
//}

u32 *Paging::getPhysAddrs(u32 *PhysAddrs, PageDirectory *pageDir) {
    u32 pdIndex = ((u32) PhysAddrs >> 22);
    u32 ptIndex = (u32) PhysAddrs >> 12 & PageEntry_10Bits;
    u32 offset = (u32) PhysAddrs & PageOffset_12Bits;

    PageTable *pTable = (PageTable*) (pageDir->dir[pdIndex].phys * pageSize);
    u32 *physPage = (u32*) (pTable->page[ptIndex].phys * pageSize);

    return (u32*) ((u32) physPage | (offset & PageOffset_12Bits));
}

void Paging::deAlloc(PageDirectory *pageDir) {

    for (int pageDirIndex = 0; pageDirIndex < 1024; pageDirIndex++) {
        if (pageDir->dir[pageDirIndex].Present == 1 &&
                pageDir->dir[pageDirIndex].phys > 0) {

            PageTable *pTable = (PageTable*) (pageDir->dir[pageDirIndex].phys * pageSize);
            for (int pageTableIndex = 0; pageTableIndex < 1024; pageTableIndex++) {
                if (pTable->page[pageTableIndex].Present &&
                        pTable->page[pageTableIndex].phys > 0) {
                    pageManagment::setFree((u32*) (pTable->page[pageTableIndex].phys * pageSize));
                }
            }

        }
    }
    pageManagment::setFree((u32*) pageDir);
}

//void *Paging::get_physaddr(void * virtualaddr) {
//    unsigned long pdindex = (unsigned long) virtualaddr >> 22;
//    unsigned long ptindex = (unsigned long) virtualaddr >> 12 & 0x03FF;
//
//    unsigned long * pd = (unsigned long *) 0xFFFFF000;
//    // Here you need to check whether the PD entry is present.
//
//    unsigned long * pt = ((unsigned long *) 0xFFC00000) + (0x400 * pdindex);
//    // Here you need to check whether the PT entry is present.
//
//    return (void *) ((pt[ptindex] & ~0xFFF) + ((unsigned long) virtualaddr & 0xFFF));
//}

//Paging::Paging(const Paging& orig) {
//}
//
//Paging::~Paging() {
//}

void Paging::dirCopy(PageDirectory *from, PageDirectory *to) {
    for (u32 i = 0; i < 1024; i++) {

        to->dir[i].phys = from->dir[i].phys;
        to->dir[i].Present = from->dir[i].Present;
        to->dir[i].Accessed = from->dir[i].Accessed;
        to->dir[i].Dirty = from->dir[i].Dirty;
        to->dir[i].Read = from->dir[i].Read;
        to->dir[i].User = from->dir[i].User;
        to->dir[i].unused = from->dir[i].unused;

    }
}