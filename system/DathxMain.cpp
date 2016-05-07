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

#define KernelStackSize 0x1000
#define initFs yes
//#define DEBUG



Time time;
Date date;

extern "C" u32 Kernel_Code_Start;
extern "C" u32 Kernel_Data_Start;
extern "C" u32 Kernel_BSS_Start;
extern "C" u32 Kernel_BSS_End;

//u32 usedMemoryCounter = 0;
static u32 totalMemoryInKB = 0;
u32 totalMemoryAdress = 0;
u32 *baseMemoryPointer;
//u32 *topMemoryPointer;

#ifndef Regs
#define	Regs
//Changed via nasm in InterruptsDel... external int one
u32 eaxReg, ecxReg, edxReg, ebxReg, espReg, ebpReg, esiReg, ediReg, eflags, eipReg, csReg, cr3Reg;
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

static Paging::PagesDir *kernelPageDir;

extern "C" void ExternalInterrupt00();

/*
 * 
 */
int main() {

    asm("cli");
    asm("movl %%ebx,%0 " ::"m" (multiboot_Info));
    asm("movl %%eax,%0 " ::"m" (magic_code));

    totalMemoryInKB = (multiboot_Info->mem_lower + multiboot_Info->mem_upper);
    totalMemoryAdress = (multiboot_Info->mem_lower + multiboot_Info->mem_upper)*1024 / 4;
    baseMemoryPointer = (u32*) ((((u32) & Kernel_BSS_End >> 12) + 2) * 0x1000); //base memory begins 2 pages after the kernel
    // static u8 *Kernel_Stack = new u8 [KernelStackSize];
    Kernel_Stack_END = ((((u32) & Kernel_BSS_End >> 12) + 1) * 0x1000) - 1; //(u32) Kernel_Stack + KernelStackSize - 1;
    Kernel_Stack_START = (u32) & Kernel_BSS_End; //(u32) Kernel_Stack;
    asm("movl %0,%%esp " ::"m" (Kernel_Stack_END));
    asm("movl %0,%%ebp " ::"m" (Kernel_Stack_START));



    // topMemoryPointer = (u32*) ((multiboot_Info->mem_lower + multiboot_Info->mem_upper)*1024 / 4);

    pageManagment::setup(totalMemoryInKB * 1024 / 4096);
    pageManagment::setRangeBusy(0, baseMemoryPointer);


    processor::setupGDT();
    processor::setupIDT();
    //processor::setupLDT();
    kernelPageDir = Paging::getNewDir();
    Paging::mapRange(0, totalMemoryAdress, kernelPageDir, 0);
    processor::loadPDBR(kernelPageDir);
    processor::enablePaging();

    cpustr = processor::getCPUString();
    cpuFeature = processor::getCPUFeatures();
    Console::print("CPU: %s", cpustr.String);
    Console::print("CPU has Apic: %s", cpuFeature.APIC == 1 ? "Yes" : "No");
    Console::print("CPU ApicID %h", cpuFeature.ApicID);
    Console::print("CPU x2APIC  %h", cpuFeature.x2APIC);
    Console::print("CPU Brand Name  %s", processor::getCPUBrandString(&cpuFeature).String);
    Console::print("CPU Processor Type: %s", processor::getTypeStr(cpuFeature.ProcessorType));




    //--------------------------- File System -------------------------
#ifdef initFs
    HardDriveDriver::setup(0);
    MBR::setup();
    FAT::setup();
#endif

    //--------------------------Hardware config ------------------------

    Chip8259::remap(32); // remap to 32
    Chip8259::UnMask();
    Chip8259::AnableRTCIntrs();


    Console::print("%ct9Welcome to Dathx OS RUTH E DAVID");
#ifdef DEBUG
    Console::print("%ct\12Kernel_Stack_START %h", Kernel_Stack_START);
    Console::print("%ct\12Kernel_Stack_END %h", Kernel_Stack_END);
    Console::print("%ct\12Kernel Magic Code %h", magic_code);

    Console::print("%ct\12Kernel_Code_Start %h", (u32) & Kernel_Code_Start);
    Console::print("%ct\12Kernel_Data_Start %h", (u32) & Kernel_Data_Start);
    Console::print("%ct\12Kernel_BSS_Start %h", (u32) & Kernel_BSS_Start);
    Console::print("%ct\12Kernel_BSS_End %h", (u32) & Kernel_BSS_End);
    Console::print("%ct\12intsStart %h", (u32) & intsStart);
    Console::print("%ct\12intsEnd %h", (u32) & intsEnd);
    Console::print("%ct\12totalMemoryInKB %h", totalMemoryInKB);

    Console::print("%ct\12Machine Memory: %i MB", (totalMemoryInKB / 1024));
    Console::print("%ct\12Machine Memory: %i bytes", totalMemoryInKB * 1024);
    //  Console::print("%ct\12Machine Memory Top: %h bytes", (multiboot_Info->mem_lower + multiboot_Info->mem_upper)*1024/4);
    //    u32 *t = paging->getPhysAddrs((u32)(multiboot_Info->mem_lower + multiboot_Info->mem_upper)*1024/4,paging->ppageDir);
    //    Console::print("%ct\12Machine Memory Top: %h bytes",(u32)t);

    Console::print("%ct\12Machine Memory: %h pages", totalMemoryInKB * 1024 / 4096);
#endif
#ifdef initFs
    ElfLoader *exec = new ElfLoader();

    for (int i = 0; i < 1; i++) {

        if (exec->openFile("bin/apptorunonkernel.bin") == OK) {

            if (exec->loadProgram() == Error) {
                Console::print("%cttLoadError");
            }

            Console::print("%ctuapp.bin Opened");
        } else {
            Console::print("%cttapp.bin open error");
        }
    }

    ElfLoader *exec2 = new ElfLoader();

    for (int i = 0; i < 1; i++) {

        if (exec2->openFile("bin/integrit_checker") == OK) {

            if (exec2->loadProgram() == Error) {
                Console::print("%cttintegrit_checker load error");
            }

            Console::print("%ctuintegrit_checker Opened");
        } else {
            Console::print("%cttintegrit_checker open error");
        }
    }

#endif

    asm("sti");
    while (true) {
        static u32 var = 0;

        var++;
        //asm("int $32");
        // asm("sti");
        //Console::print(47,0,"%getFree: %h", (u32) pageManagment::getFree());
        Console::print(49, 0, "%cb2Loop: %h", var);
        // Console::print(45, 0, "%ct\13%cbbUsed Memory: %h bytes", (u32) getUsedMemory());
        //Console::print(47, 0, "%ct\13%cbtTopMemory: %h bytes", (u32) topMemoryPointer);
        //asm("ljmp $0x190,$0 ");
        // asm("sti");
        // asm("nop");
    }
}

