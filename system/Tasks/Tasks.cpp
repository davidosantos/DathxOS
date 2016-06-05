/*
 * File:   Tasks.cpp
 * Author: davidosantos
 *
 * Created on July 19, 2015, 10:34 AM
 */
#include "Tasks.h"



Tasks::Task Tasks::TasksList[50];


//Tasks::Tasks(CPU *Cpu) {
//    CPUAddress = Cpu;
//
//    debug = new Console();
//
//  //  TasksList = new TaskList [50];
//
//}

//Tasks::Tasks(const Tasks& orig) {
//}
//
//Tasks::~Tasks() {
//}

void IntsReturnTaskSwitch() {
    Tasks::interruptReceiver();
    APIC::issueEOI();
}

/**
 * Cause a task switch to a internal task to save the current task
 * in the internal task, load eipReg that was saved by interrupt 0x00
 * into the outgoing tss's EIP.
 * @param eipReg last task eip.
 */
void Tasks::interruptReceiver() {



    if (runningTask >= TaskCount) {
        runningTask = 1;
        saveTask(runningTask);

        loadTask(runningTask);
    } else {
        saveTask(runningTask);
        runningTask++;
        loadTask(runningTask);
    }

    //        debug->print(18, 0, "Task %1", runningTask);
    //        debug->print(19, 0, "Task %i", runningTask+1);
    //        debug->print(20, 0, "Task 1 eflags %h", (u32) TasksList[runningTask].taskState->eflags);
    //        debug->print(22, 0, "Task 1 addres %h", (u32) TasksList[runningTask].Addrs);
    //        debug->print(24, 0, "Task 1 eip %h", (u32) TasksList[runningTask].taskState->eip);
    //        debug->print(26, 0, "Task 1 esp %h", (u32) TasksList[runningTask].taskState->esp);
    //
    //        debug->print(30, 0, "Task 1 eax %h", (u32) TasksList[runningTask].taskState->eax);
    //        debug->print(32, 0, "Task 1 ecx %h", (u32) TasksList[runningTask].taskState->ecx);
    //        debug->print(34, 0, "Task 1 ebx %h", (u32) TasksList[runningTask].taskState->ebx);
    //        debug->print(36, 0, "Task 1 esi %h", (u32) TasksList[runningTask].taskState->esi);
    //        debug->print(38, 0, "Task 1 edi %h", (u32) TasksList[runningTask].taskState->edi);
    //        debug->print(40, 0, "Task 1 ebp %h", (u32) TasksList[runningTask].taskState->ebp);
    //        debug->print(42, 0, "Task 1 ss %h", (u32) TasksList[runningTask].taskState->ss);
    //
    //        debug->print(21, 0, "Task 2 eflags %h", (u32) TasksList[runningTask+1].taskState->eflags);
    //        debug->print(23, 0, "Task 2 addres %h", (u32) TasksList[runningTask+1].Addrs);
    //        debug->print(25, 0, "Task 2 eip %h", (u32) TasksList[runningTask+1].taskState->eip);
    //        debug->print(27, 0, "Task 2 esp %h", (u32) TasksList[runningTask+1].taskState->esp);
    //        debug->print(31, 0, "Task 2 eax %h", (u32) TasksList[runningTask+1].taskState->eax);
    //        debug->print(33, 0, "Task 2 ecx %h", (u32) TasksList[runningTask+1].taskState->ecx);
    //        debug->print(35, 0, "Task 2 ebx %h", (u32) TasksList[runningTask+1].taskState->ebx);
    //        debug->print(37, 0, "Task 2 esi %h", (u32) TasksList[runningTask+1].taskState->esi);
    //        debug->print(39, 0, "Task 2 edi %h", (u32) TasksList[runningTask+1].taskState->edi);
    //        debug->print(41, 0, "Task 2 ebp %h", (u32) TasksList[runningTask+1].taskState->ebp);
    //        debug->print(43, 0, "Task 2 ss %h", (u32) TasksList[runningTask+1].taskState->ss);

    //    CPU::GDTEntry GDTEntry = CPUAddress->GDT[CPUAddress->STRGDTIndex()];
    //    lastTss = (Tss_32*) ((u32) ((GDTEntry.base_31_24 << 24) | (GDTEntry.base_23_16 << 16) | (GDTEntry.base)));
    //
    //
    //    debug->print("eip %h", eipReg);
    //    lastTss->eip = (u32) anotherTask;
    //    lastTss->eax = eaxReg;
    //    lastTss->ecx = ecxReg;
    //    lastTss->edx = edxReg;
    //    lastTss->esp = espReg;
    //    lastTss->ebp = ebpReg;
    //    lastTss->esi = esiReg;
    //    lastTss->edi = ediReg;
    //    lastTss->eflags = eflags;
    //
    //    //    //GDTEntry.type = tss_p_rng0b;
    //    //
    //    //CPUAddress->LTR(0x190);
    //
    //    GDTEntry = CPUAddress->GDT[CPUAddress->STRGDTIndex()];
    //    lastTss = (Tss_32*) ((u32) ((GDTEntry.base_31_24 << 24) | (GDTEntry.base_23_16 << 16) | (GDTEntry.base)));
    //    //    lastTss->prev_task_link = 0x1a8;
    //    //GDTEntry.type = tss_p_rng0;
    //
    //
    //    //    CPUAddress->Set_NT();
    //    //    //while(1){}
    //    //    //asm("ljmp $0x1a8,$0"); //goto internalTaskSwitcher task 50 in the GDT.
    //    //    asm("iret"); //goto internalTaskSwitcher task 50 in the GDT.
    //
    //    //asm("jmp %0 " : : "m" (eipReg) );
}




Tasks::Tss_32* Tasks::lastTss;

u32 Tasks::runningTask = 0;
u32 Tasks::TaskCount = 0;
u8 Tasks::CurrPrevLevel = 0;

//Tasks::TaskList Tasks::TasksList[50];

//void Tasks::NewTask(const s8 *name, u32 Addrs) {
//
//    TaskCount++;
//    TasksList[TaskCount].Name = name;
//    TasksList[TaskCount].PID = TaskCount;
//    TasksList[TaskCount].Addrs = Addrs;
//    TasksList[TaskCount].taskState = new TSS();
//
//    u32 *stackFrame = new u32[200]; //800 bytes
//
//    u16 sel_ss = CPUAddress->getNewDataSeg(0, 0xffffffff);
//    u16 sel_code = CPUAddress->getNewCodeSeg(0, 0xffffffff);
//
//    TasksList[TaskCount].taskState->eflags = 0x202;
//    TasksList[TaskCount].taskState->eip = (u32) Addrs;
//    TasksList[TaskCount].taskState->ss = sel_ss;
//    TasksList[TaskCount].taskState->ds = sel_ss;
//    TasksList[TaskCount].taskState->es = sel_ss;
//    TasksList[TaskCount].taskState->fs = sel_ss;
//    TasksList[TaskCount].taskState->gs = sel_ss;
//    TasksList[TaskCount].taskState->cs = sel_code;
//    TasksList[TaskCount].taskState->esp = (u32) stackFrame + 4 * 200;
//    TasksList[TaskCount].taskState->ebp = (u32) stackFrame;
//    TasksList[TaskCount].taskState->cr3 = (u32) paging->getNewDir(); //test
//
//    //
//    //    //Tss_32 *TaskState = new Tss_32();
//    //
//    //    TaskState->eip = (u32) Addrs;
//    //    TaskState->cs = CPUAddress->makeSelector(1, 0, 0);
//    //    TaskState->ds = CPUAddress->makeSelector(2, 0, 0);
//    //    TaskState->es = CPUAddress->makeSelector(2, 0, 0);
//    //    TaskState->gs = CPUAddress->makeSelector(2, 0, 0);
//    //    TaskState->fs = CPUAddress->makeSelector(2, 0, 0);
//    //    TaskState->ss = CPUAddress->makeSelector(2, 0, 0);
//    ////    TaskState->ss0 = CPUAddress->makeSelector(2, 0, 0);
//    //
//    //
//    //
//    //    //u32 Entry = CPUAddress->addGDTDesc(sizeof (Tss_32), (u32) TaskState, tss_p_rng0, 0x80); //verificar
//    //
//    //    u16 Sel = CPUAddress->makeSelector(Entry, 0, 0);
//    //
//    //    if (loadTaskReg) {
//    //        CPUAddress->LTR(Sel);
//    //    }
//    //
//    //
//    //    // su32 TsNm = 0;
//    //
//    //    //TaskSels[TsNm++] = Sel;
//
//
//    // return Sel;
//}

void Tasks::createProcess(const s8 *file) {

    ElfLoader *exec = new ElfLoader();
    Paging::PagesDir *pageDir;
    u8 *loadAddrs; // = (u32*) Paging::getNewPage();

    if (exec->openFile(file) == OK) {
        pageDir = Paging::getNewDir();
        loadAddrs = new u8 [exec->pHeader[0].p_memsz];
        Paging::mapRange(0, 0x800000, pageDir, 0, true);
        Paging::mapRange(exec->pHeader[0].p_vaddr, (exec->pHeader[0].p_vaddr +
                exec->pHeader[0].p_memsz), pageDir, (u32*) loadAddrs, true);
        if (exec->loadProgram(pageDir) == Error) {
            Console::print("%cttELF Loader: Error Loading file %s", file);
        } else {
            u32 *stack = new u32 [1024];
            Tasks::NewTask(file, exec->Header->e_entry, pageDir, stack, 1024, 3);
            Console::print("%ctuELF Loader: File loaded %s", file);
        }
    } else {
        Console::print("%cttELF Loader: File open error %s", file);
    }
}

void Tasks::NewTask(const s8 *name, void (*function)(), Paging::PagesDir *pageDir, u32 *stack, u32 stackSize, u8 ring) {

    TaskCount++;
    TasksList[TaskCount].Name = name;
    TasksList[TaskCount].PID = TaskCount;
    TasksList[TaskCount].Addrs = function;
    TasksList[TaskCount].taskState = new TaskState();
    u16 sel_data = 0;
    u16 sel_code = 0;

    if (ring == 0) {

        TasksList[TaskCount].taskState->taskPrevLevel = 0;
        sel_data = processor::getRng0Data();
        sel_code = processor::getRng0Code();
        TasksList[TaskCount].taskState->eflags = 0x203202;
    } else if (ring == 3) {
        TasksList[TaskCount].taskState->taskPrevLevel = 3;
        sel_data = processor::getRng3Data();
        sel_code = processor::getRng3Code();
        TasksList[TaskCount].taskState->eflags = 0x203202;
    }
    if ((TaskCount - 1) == 0) { //necessary for the first task 0 to be reliable
        TasksList[0].taskState->taskPrevLevel = 0;
    }

    TasksList[TaskCount].taskState->eip = (u32) function;
    TasksList[TaskCount].taskState->eax = 0;
    TasksList[TaskCount].taskState->ebx = 0;
    TasksList[TaskCount].taskState->ecx = 0;
    TasksList[TaskCount].taskState->edx = 0;
    TasksList[TaskCount].taskState->edi = 0;
    TasksList[TaskCount].taskState->esi = 0;
    TasksList[TaskCount].taskState->ss = sel_data;
    TasksList[TaskCount].taskState->ds = sel_data;
    TasksList[TaskCount].taskState->es = sel_data;
    TasksList[TaskCount].taskState->fs = sel_data;
    TasksList[TaskCount].taskState->gs = sel_data;
    TasksList[TaskCount].taskState->cs = sel_code;
    TasksList[TaskCount].taskState->esp = (u32) stack + stackSize;
    TasksList[TaskCount].taskState->ebp = (u32) stack;
    TasksList[TaskCount].taskState->PageDir = pageDir; //test

    processor::TSSrng3->eip = TasksList[TaskCount].taskState->eip;
    processor::TSSrng3->eax = TasksList[TaskCount].taskState->eax;
    processor::TSSrng3->ebx = TasksList[TaskCount].taskState->ebx;
    processor::TSSrng3->ecx = TasksList[TaskCount].taskState->ecx;
    processor::TSSrng3->edx = TasksList[TaskCount].taskState->edx;
    processor::TSSrng3->esp = TasksList[TaskCount].taskState->esp;
    processor::TSSrng3->ebp = TasksList[TaskCount].taskState->ebp;
    processor::TSSrng3->esi = TasksList[TaskCount].taskState->esi;
    processor::TSSrng3->edi = TasksList[TaskCount].taskState->edi;
    processor::TSSrng3->eflags = TasksList[TaskCount].taskState->eflags;
    processor::TSSrng3->ss = TasksList[TaskCount].taskState->ss;
    processor::TSSrng3->cs = TasksList[TaskCount].taskState->cs;
    processor::TSSrng3->ds = TasksList[TaskCount].taskState->ds;
    processor::TSSrng3->es = TasksList[TaskCount].taskState->es;
    processor::TSSrng3->fs = TasksList[TaskCount].taskState->fs;
    processor::TSSrng3->gs = TasksList[TaskCount].taskState->gs;
    processor::TSSrng3->cr3 = (u32) TasksList[TaskCount].taskState->PageDir;

    u32 espKernel = 0;
    asm("movl %%esp,%0\n" : "=m" (espKernel) ::);
    processor::TSSrng3->ss0 = 0x10; 
    processor::TSSrng3->esp0 = espKernel;
    processor::TSS->prev_tss = 0x38;

}

void inline Tasks::saveTask(u32 task_Id) {

    TasksList[task_Id].taskState->eip = eipReg;
    TasksList[task_Id].taskState->eax = eaxReg;
    TasksList[task_Id].taskState->ebx = ebxReg;
    TasksList[task_Id].taskState->ecx = ecxReg;
    TasksList[task_Id].taskState->edx = edxReg;
    TasksList[task_Id].taskState->esp = espReg;
    TasksList[task_Id].taskState->ebp = ebpReg;
    TasksList[task_Id].taskState->esi = esiReg;
    TasksList[task_Id].taskState->edi = ediReg;
    TasksList[task_Id].taskState->eflags = eflags;
    TasksList[task_Id].taskState->ss = ssReg;
    TasksList[task_Id].taskState->cs = csReg;
    TasksList[task_Id].taskState->ds = dsReg;
    TasksList[task_Id].taskState->es = esReg;
    TasksList[task_Id].taskState->fs = fsReg;
    TasksList[task_Id].taskState->gs = gsReg;
    TasksList[task_Id].taskState->PageDir = (Paging::PagesDir*) cr3Reg;
}

void inline Tasks::loadTask(u32 task_Id) {


    eipReg = TasksList[task_Id].taskState->eip;
    eaxReg = TasksList[task_Id].taskState->eax;
    ebxReg = TasksList[task_Id].taskState->ebx;
    ecxReg = TasksList[task_Id].taskState->ecx;
    edxReg = TasksList[task_Id].taskState->edx;
    espReg = TasksList[task_Id].taskState->esp;
    ebpReg = TasksList[task_Id].taskState->ebp;
    esiReg = TasksList[task_Id].taskState->esi;
    ediReg = TasksList[task_Id].taskState->edi;
    eflags = TasksList[task_Id].taskState->eflags;
    ssReg = TasksList[task_Id].taskState->ss;
    csReg = TasksList[task_Id].taskState->cs;
    dsReg = TasksList[task_Id].taskState->ds;
    esReg = TasksList[task_Id].taskState->es;
    fsReg = TasksList[task_Id].taskState->fs;
    gsReg = TasksList[task_Id].taskState->gs;
    cr3Reg = (u32) TasksList[task_Id].taskState->PageDir;

    processor::TSSrng3->eip = eipReg;
    processor::TSSrng3->eax = eaxReg;
    processor::TSSrng3->ebx = ebxReg;
    processor::TSSrng3->ecx = ecxReg;
    processor::TSSrng3->edx = edxReg;
    processor::TSSrng3->esp = espReg;
    processor::TSSrng3->ebp = ebpReg;
    processor::TSSrng3->esi = esiReg;
    processor::TSSrng3->edi = ediReg;
    processor::TSSrng3->eflags = eflags;
    processor::TSSrng3->ss = ssReg;
    processor::TSSrng3->cs = csReg;
    processor::TSSrng3->ds = dsReg;
    processor::TSSrng3->es = esReg;
    processor::TSSrng3->fs = fsReg;
    processor::TSSrng3->gs = gsReg;
    processor::TSSrng3->cr3 = cr3Reg;

//    processor::TSSrng3->ss0 = processor::TSS->ss;
//    processor::TSSrng3->esp0 = processor::TSS->esp0;
//    processor::TSS->prev_tss = 0x40;
    // asm("cli");
    //asm("hlt");
    //processor::Set_NT();
    //processor::GDT[7].type = tss_p_rng3;


    //asm("ljmp $0x38,$0");
    //asm("iret");

}

Tasks::Task Tasks::getTask(u32 index) {
    return TasksList[index];
}