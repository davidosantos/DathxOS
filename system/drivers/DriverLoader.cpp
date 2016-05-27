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

DriverLoader::DriverLoader() {
}

//DriveLoader::DriveLoader(const DriveLoader& orig) {
//}
//
//DriveLoader::~DriveLoader() {
//}

void DriverLoader::loadDriver(const s8 *file) {

    ElfLoader *exec = new ElfLoader();
    Paging::PagesDir *pageDir;
    Paging::PagesDir *KernelPageDir;
    u8 *loadAddrs; // = (u32*) Paging::getNewPage();

    if (exec->openFile(file) == OK) {

        pageDir = Paging::getNewDir();

        loadAddrs = new u8 [exec->pHeader[0].p_memsz];

        Paging::mapRange(0, 0x800000, pageDir, 0);

        Paging::mapRange(exec->pHeader[0].p_vaddr, (exec->pHeader[0].p_vaddr +
                exec->pHeader[0].p_memsz), pageDir, (u32*) loadAddrs);

        if (exec->loadProgram(pageDir) == Error) {
            Console::print("%cttDriverLoader: Error Loading file %s", file);
        } else {
            Console::print("%ctuDriverLoader: File loaded %s", file);
            KernelPageDir = (Paging::PagesDir*) processor::getPDBR();
            processor::loadPDBR(pageDir);
            (exec->Header->e_entry)();
            processor::loadPDBR(KernelPageDir);
        }
    } else {
        Console::print("%cttDriveLoader: File open error %s", file);
    }
}
