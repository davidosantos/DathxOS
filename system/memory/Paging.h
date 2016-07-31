/* 
 * File:   Paging.h
 * Author: davidosantos
 *
 * Created on 1 de Agosto de 2015, 15:46
 */

#ifndef PAGING_H
#define PAGING_H
#include "../../util/util.h"
#include "../monitor/Console.h"


#define To_20Bits 0x000FFFFF
#define PageDir_10Bits 0xFFC
#define PageEntry_10Bits 0x3FF
#define PageOffset_12Bits 0xFFF
#define _4kb 4096
#define pageSize 4096
#define _1kb 1024


//extern "C" u32 usedMemoryCounter;
extern "C" u32 *baseMemoryPointer;
//extern "C" u32 *topMemoryPointer;

class Paging {
public:
    static void allocPage(u32 Address, u16 pages);

    Paging();
    //    Paging(const Paging& orig);
    //    virtual ~Paging();



private:




    static void *get_physaddr(void * virtualaddr);
    //    struct PageDirEntry {
    //        u32 Present : 1,
    //        Read : 1,
    //        User : 1,
    //        WriteThrough : 1,
    //        Cashe : 1,
    //        Accessed : 1,
    //        Reserved : 1,
    //        PageSize : 1,
    //        Ignored : 1,
    //        Available : 2,
    //        Frame : 20;
    //    } __attribute__((packed)); //__attribute__((aligned(4096)));
    //    u32int present    : 1;   // Page present in memory
    //   u32int rw         : 1;   // Read-only if clear, readwrite if set
    //   u32int user       : 1;   // Supervisor level only if clear
    //   u32int accessed   : 1;   // Has the page been accessed since last refresh?
    //   u32int dirty      : 1;   // Has the page been written to since last refresh?
    //   u32int unused     : 7;   // Amalgamation of unused and reserved bits
    //   u32int frame      : 20;  // Frame address (shifted right 12 bits)

    struct PageTableEntry {
        u32 Present : 1,
        Read : 1,
        User : 1,
        Accessed : 1,
        Dirty : 1,
        unused : 7,
        phys : 20;
    } __attribute__((aligned(4), packed));

    struct PageDirEntry {

        union {

            struct {
                u32 Present : 1,
                Read : 1,
                User : 1,
                Accessed : 1,
                Dirty : 1,
                unused : 7,
                phys : 20;
            };
            u32 all;
        };
    } __attribute__((aligned(4), packed));

    //    struct PageDir {
    //        PageDirEntry dirs [1024];
    //    } __attribute__((packed));
    //
    //    struct PagePage {
    //        PageTableEntry pages [1024];
    //    } __attribute__((packed));
public:

    struct PageDirectory {
        PageDirEntry dir[1024];
    } __attribute__((aligned(4096), packed));

    struct PageTable {
        PageTableEntry page[1024];
    } __attribute__((aligned(4096), packed));



    static void mapRange(u32 virtStart, u32 virtEnd, Paging::PageDirectory *pageDir, bool user);

    static void mapRange(u32 virtStart, u32 virtEnd, Paging::PageDirectory *pageDir, u32 *physStart, bool user);
   
    //static void mapRange(u32 virtEnd, Paging::PagesDir *pageDir);

    static u32 *getPhysAddrs(u32 *Addrs, PageDirectory *pageDir);
    
    static void deAlloc(PageDirectory *pageDir);

    static void dirCopy(PageDirectory *from, PageDirectory *to);

    static PageDirectory *getNewDir();
    static u32 *getNewPage();

};

#endif /* PAGING_H */

