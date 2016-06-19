/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DriveLoader.cpp
 * Author: david
 * 
 * Created on 26 de Maio de 2016, 18:39
 */

#include "DriverLoader.h"
#include "driverManager.h"

DriverLoader::DriverLoader() {
}

//DriveLoader::DriveLoader(const DriveLoader& orig) {
//}
//
//DriveLoader::~DriveLoader() {
//}

void DriverLoader::loadDriver(const s8 *file) {

    ElfLoader *exec = new ElfLoader();
    processor::TSSEntry *tss = new processor::TSSEntry();
    Paging::PageDirectory *pageDir;
    u8 *loadAddrs; // = (u32*) Paging::getNewPage();
    if (exec->openFile(file) == OK) {

        pageDir = Paging::getNewDir();

        loadAddrs = new u8 [exec->pHeader[0].p_memsz];

        Paging::mapRange(0, 0x800000, pageDir, 0, false);

        Paging::mapRange(exec->pHeader[0].p_vaddr, (exec->pHeader[0].p_vaddr +
                exec->pHeader[0].p_memsz), pageDir, (u32*) loadAddrs, false);

        if (exec->loadProgram(pageDir) == Error) {
            Console::print("%cttDriverLoader: Error Loading file %s", file);
        } else {
            Console::print("%ctuDriverLoader: File loaded %s", file);


            u16 sel_data = 0;
            u16 sel_code = 0;
            sel_data = processor::getRng0Data();
            sel_code = processor::getRng0Code();

            tss->eax = 0;
            tss->ebx = 0;
            tss->ecx = 0;
            tss->edx = 0;
            tss->edi = 0;
            tss->esi = 0;
            tss->ss = sel_data;
            tss->ss0 = sel_data;
            tss->ds = sel_data;
            tss->es = sel_data;
            tss->fs = sel_data;
            tss->gs = sel_data;
            tss->cs = sel_code;
            u32 *stack = new u32[pageSize];
            tss->esp = (u32) stack + pageSize - 1;
            tss->ebp = (u32) stack;

            tss->eip = (u32) exec->Header->e_entry;
            tss->cr3 = (u32) pageDir;
            tss->eflags = 0x203002;
            
            asm("movl %%esp,%0" : "=m" (tss->esp0));


            driverManager::callDriverMain(driverManager::addDriver(file,tss));

        }
    } else {
        Console::print("%cttDriveLoader: File open error %s", file);
    }
}
