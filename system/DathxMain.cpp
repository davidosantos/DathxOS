/* 
 * File:   DathxMain.cpp
 * Author: david
 *
 * Created on November 6, 2015, 11:06 PM
 */
#include "multiboot.h"
#include "../util/util.h"
#include "memory/Memory.h"
#include "memory/Paging.h"
#include "processor.h"
#include "memory/pageManagment.h"
#include "drivers/HardDriveDriver.h"
#include "fs/MBR.h"
#include "fs/FAT32.h"
#include "fs/File.h"
#include "RunTime/ElfLoader.h"
#include "Cmos.h"
#include "drivers/Chip8259.h"
#include "drivers/APIC.h"
#include "RunTime/IRQHandler.h"
#include "drivers/DriverLoader.h"
#include "Providers/InputProvider.h"

#define KernelStackSize 0x1000
#define initFs yes
//#define DEBUG
//#define showMultiboot


Time time;
Date date;

extern "C" u32 Kernel_Code_Start;
extern "C" u32 Kernel_Code_End;
extern "C" u32 Kernel_Data_Start;
extern "C" u32 Kernel_Data_End;
extern "C" u32 Kernel_BSS_Start;
extern "C" u32 Kernel_BSS_End;

//u32 usedMemoryCounter = 0;
static u32 totalMemoryInKB = 0;
u32 totalMemoryAdress = 0;
u32 *baseMemoryPointer;
//u32 *topMemoryPointer;

#ifndef Regs
#define Regs
//Changed via nasm in InterruptsDel... external int one
u32 eaxReg, ecxReg, edxReg, ebxReg, espReg, ebpReg, esiReg, ediReg, eflags, eipReg, csReg, cr3Reg, kerPageDir, oldespReg, oldssReg;
u16 ssReg, dsReg, esReg, fsReg, gsReg;
#endif

extern "C" u32 intsStart;
extern "C" u32 intsEnd;

static u32 Kernel_Stack_END = 0;
static u32 Kernel_Stack_START = 0;

static multiboot_info_t *multiboot_Info;
static u32 magic_code;
static processor::CPUString cpustr;
static processor::CPUFeatures cpuFeature;

static Paging::PagesDir *kernel_Page_Directory;

extern "C" void ExternalInterrupt00();

void test() {
    Console::print("My Handler");
}


/*
 * 
 */
int main() {

    asm("cli");
    asm("movl %%ebx,%0 " ::"m" (multiboot_Info));
    asm("movl %%eax,%0 " ::"m" (magic_code));

    totalMemoryInKB = (multiboot_Info->mem_lower + multiboot_Info->mem_upper);
    totalMemoryAdress = (multiboot_Info->mem_lower + multiboot_Info->mem_upper)*1024 / 4;

    baseMemoryPointer = (u32*) ((((u32) & Kernel_BSS_End >> 12) + 2) * 0x1000); //2 pages after the kernel
    Kernel_Stack_END = ((((u32) & Kernel_BSS_End >> 12) + 1) * 0x1000) - 1;
    Kernel_Stack_START = (u32) & Kernel_BSS_End + 1;
    asm("movl %0,%%esp " ::"m" (Kernel_Stack_END));
    asm("movl %0,%%ebp " ::"m" (Kernel_Stack_START));


    //--------------------------Memory config ------------------------
    pageManagment::setup(totalMemoryInKB * 1024 / 4096);
    pageManagment::setRangeBusy(0, baseMemoryPointer);

    if (multiboot_Info->mmap_info == 1) {
        memory_map_t *mmap = (memory_map*) multiboot_Info->mmap_addr;

        for (mmap = (memory_map_t *) multiboot_Info->mmap_addr;
                (unsigned long) mmap < multiboot_Info->mmap_addr + multiboot_Info->mmap_length;
                mmap = (memory_map_t *) ((unsigned long) mmap
                + mmap->size + sizeof (mmap->size))) {
            if (mmap->type != MULTIBOOT_MEMORY_AVAILABLE) {
                u32 *rsvd_start = (u32*) (mmap->base_addr_low + mmap->base_addr_high);
                u32 *rsvd_end = (u32*) ((mmap->base_addr_low + mmap->base_addr_high) + (u32) (mmap->length_low + mmap->length_high));
                pageManagment::setRangeBusy(rsvd_start, rsvd_end);
            }
        }
    }

    kernel_Page_Directory = Paging::getNewDir();

    processor::setupGDT();
    processor::setupIDT();
    //processor::setupLDT();
    processor::setupTR();

    kerPageDir = (u32) kernel_Page_Directory;
    Paging::mapRange(0, totalMemoryAdress, kernel_Page_Directory, 0,false);
    processor::loadPDBR(kernel_Page_Directory);
    processor::enablePaging();

    cpustr = processor::getCPUString();
    cpuFeature = processor::getCPUFeatures();
    //    Console::print("CPU: %s", cpustr.String);
    //    Console::print("CPU has Apic: %s", cpuFeature.APIC == 1 ? "Yes" : "No");
    //    Console::print("CPU ApicID %h", cpuFeature.ApicID);
    //    Console::print("CPU FamilyId %h", cpuFeature.FamilyId);
    //    Console::print("CPU Model Specific %h", cpuFeature.MSR);
    //    Console::print("CPU x2APIC  %h", cpuFeature.x2APIC);
    //    Console::print("CPU Brand Name  %s", processor::getCPUBrandString(&cpuFeature).String);
    //    Console::print("CPU Processor Type: %s", processor::getTypeStr(cpuFeature.ProcessorType));


    Console::print("%ct9Welcome to Dathx OS RUTH E DAVID");
    Console::print("CPU Brand Name  %s", processor::getCPUBrandString(&cpuFeature).String);

    //--------------------------Hardware config ------------------------
    IRQHandler::setup();
   //IRQHandler::add(0, test2);

    if (cpuFeature.APIC == ON) {
        Chip8259::remap(32); // remap to 32
        APIC::setup(&cpuFeature, kernel_Page_Directory);
        APIC::startTimer(100000);
        APIC::enableAPIC();
    } else {
        Chip8259::remap(32); // remap to 32
        Chip8259::UnMask();
        Chip8259::AnableRTCIntrs();
    }




    //--------------------------- File System -------------------------
#ifdef initFs
    HardDriveDriver::setup(0);
    MBR::setup();
    FAT::setup();
    Tasks::createProcess("bin/apptorunonkernel.bin");

   Tasks::createProcess("bin/integrit_checker");

   DriverLoader::loadDriver("drivers/keyboard.dri");
  
#endif
#ifdef showMultiboot

    Console::print("%ct\12mem_info %h", multiboot_Info->mem_info);
    Console::print("%ct\12mmap_info %h", multiboot_Info->mmap_info);
    if (multiboot_Info->mmap_info == 1) {
        memory_map_t *mmap = (memory_map*) multiboot_Info->mmap_addr;

        for (mmap = (memory_map_t *) multiboot_Info->mmap_addr;
                (unsigned long) mmap < multiboot_Info->mmap_addr + multiboot_Info->mmap_length;
                mmap = (memory_map_t *) ((unsigned long) mmap
                + mmap->size + sizeof (mmap->size))) {
            if (mmap->type != MULTIBOOT_MEMORY_AVAILABLE) {
                u32 *rsvd_start = (u32*) (mmap->base_addr_low + mmap->base_addr_high);
                u32 *rsvd_end = (u32*) ((mmap->base_addr_low + mmap->base_addr_high) + (u32) (mmap->length_low + mmap->length_high));
                Console::print("Reserved from %h", (u32) rsvd_start);
                Console::print("Reserved to %h", (u32) rsvd_end);
            }
        }


    }

#endif
#ifdef DEBUG
    Console::print("%ct\12Multiboot Magic Code %h", magic_code);
    Console::print("%ct\12Kernel_Code_Start %h", (u32) & Kernel_Code_Start);
    Console::print("%ct\12intsStart %h", (u32) & intsStart);
    Console::print("%ct\12intsEnd %h", (u32) & intsEnd);
    Console::print("%ct\12Kernel_Code_End %h", (u32) & Kernel_Code_End);
    Console::print("%ct\12Kernel_Data_Start %h", (u32) & Kernel_Data_Start);
    Console::print("%ct\12Kernel_Data_End %h", (u32) & Kernel_Data_End);
    Console::print("%ct\12Kernel_BSS_Start %h", (u32) & Kernel_BSS_Start);
    Console::print("%ct\12Kernel_BSS_End %h", (u32) & Kernel_BSS_End);
    Console::print("%ct\12Kernel_Stack_START %h", Kernel_Stack_START);
    Console::print("%ct\12Kernel_Stack_END %h", Kernel_Stack_END);
    Console::print("%ct\12Kernel_Page_Dir %h", (u32) kernel_Page_Directory);

    Console::print("%ct\12totalMemoryAdress %i", totalMemoryAdress);
    Console::print("%ct\12totalMemoryInKB %i", totalMemoryInKB);
    Console::print("%ct\12Machine Memory: %i MB", (totalMemoryInKB / 1024));
    Console::print("%ct\12Machine Memory: %i bytes", totalMemoryInKB * 1024);
    Console::print("%ct\12Machine Memory: %i pages", totalMemoryInKB * 1024 / 4096);

#endif
    
    //--------------------------- System Resources -------------------------
    
    InputProvider::setup();
    
    
    
    
    //--------------------------- Kernel load Finished -------------------------
    asm("ljmp $0x33,$0"); // jmp to the first task, ring 3
    
    /**
     * Kernel loading is done, from now on, no code will execute in ring 0,
     * except for interrupts 
     * @return 
     */
    
   
    while (true) {
        static u32 var = 0;

        var++;
        //asm("int $32");
        // asm("sti");
        //Console::print("%getFree: %h", (u32) pageManagment::getFree());
        // Console::print(39, 0, "%cb7pageManagment::totalPages: %i     ", (u32) pageManagment::totalPages);
        //Console::print(41, 0, "%cb7pageManagment::totalCount: %i     ", (u32) pageManagment::totalCountReserved);
        //Console::print(43, 0, "%cb7pageManagment::getFree(): %i     ", (u32) pageManagment::getFree());
        //Console::print(45, 0, "%cb5APIC::getCurrentCount(): %h     ", APIC::getCurrentCount());
        Console::print(49, 0, "%cb2Loop: %h", var);
        Console::print(49, 26, "%cb2CR3: %h", processor::getPDBR());
        Console::print(49, 54, "%cb2KPD: %h", (u32) kernel_Page_Directory);
        //Console::print(45, 0, "%ct\13%cbbUsed Memory: %h bytes", (u32) getUsedMemory());
        //Console::print(47, 0, "%ct\13%cbtTopMemory: %h bytes", (u32) topMemoryPointer);
        //asm("ljmp $0x190,$0 ");
        // asm("sti");
        // asm("nop");
    }
}

