/* 
 * File:   autoCheck.cpp
 * Author: david
 * 
 * Created on 12 de Novembro de 2015, 20:23
 */

#include "autoCheck.h"

//autoCheck::autoCheck() {
//}
//
//autoCheck::autoCheck(const autoCheck& orig) {
//}
//
//autoCheck::~autoCheck() {
//}

/**
 * 1. Check Paging
 * 2. check GDT
 * 3. check IDT
 * 4. check LDT (not implemented)
 */
//void autoCheck::runCheck() {
//    Paging::PagesDir *systemPagesDir =
//            (Paging::PagesDir*) processor::getPDBR();
//
//    Paging::PagesTable *systemPagesTable;
//
//    u32 totalSystemPagesDir = (totalMemoryAdress >> 22);
//    
//    processor::GDTEntry *gdt;
//    processor::IDTEntry *idt;
//    
//
//    //Console::clear();
//    Console::print("totalSystemPages %i", totalSystemPagesDir);
//    Console::print("totalSystemPagesDir %i", totalSystemPagesDir);
//    Console::print("processor::getPDBR() %h", (u32) processor::getPDBR());
//    for (u32 index = 0; index < totalSystemPagesDir; index++) {
//        if (systemPagesDir->dir[index].Present == notPresent && systemPagesDir->dir[index].phys) {
//            //Console::print("%ctuPagedir entry not preset %i", index);
//            //Console::print("%ctuPagedir entry Adrses to %h", systemPagesDir->dir[index].phys * pageSize);
//        }
//
//        systemPagesTable = (Paging::PagesTable*) (systemPagesDir->dir[index].phys * pageSize);
//        u32 End = (index == totalSystemPagesDir) ? totalSystemPagesDir : _1kb;
//
//        for (u32 tbIndex = 0; tbIndex < End; tbIndex++) {
//            if (systemPagesTable->page[tbIndex].Present == notPresent && systemPagesTable->page[tbIndex].phys) {
//               // Console::print("%ctuPageTable entry not preset %i", tbIndex);
//                //Console::print("%ctuPageTable entry Adrses to %h", systemPagesTable->page[tbIndex].phys * pageSize);
//            }
//        }
//    }
//    
//    gdt = (processor::GDTEntry*) processor::getSGDT();
//    Console::print("processor::getSGDT() %h", (u32) gdt);
//    
//    idt = (processor::IDTEntry*) processor::getSIDT();
//    Console::print("processor::getISDT() %h", (u32) idt);
//
//}

