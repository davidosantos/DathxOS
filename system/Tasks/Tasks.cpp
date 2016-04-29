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



void IntsReturnTaskSwitch(){
    Tasks::interruptReceiver();
}


/**
 * Cause a task switch to a internal task to save the current task
 * in the internal task, load eipReg that was saved by interrupt 0x00
 * into the outgoing tss's EIP.
 * @param eipReg last task eip.
 */
void Tasks::interruptReceiver() {



    if (runningTask >= TaskCount) {
        saveTask(runningTask);
        runningTask = 0;
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

void Tasks::NewTask(const s8 *name, u32 Addrs, Paging::PagesDir *pageDir, u32 *stack, u32 stackSize) {

    TaskCount++;
    TasksList[TaskCount].Name = name;
    TasksList[TaskCount].PID = TaskCount;
    TasksList[TaskCount].Addrs =  Addrs;
    TasksList[TaskCount].taskState = new TSS();

  

    u16 sel_data = 0x10;//CPUAddress->getNewDataSeg(0, 0xffffffff);
    u16 sel_code = 0x08;//CPUAddress->getNewCodeSeg(0, 0xffffffff);

    TasksList[TaskCount].taskState->eflags = 0x202;
    TasksList[TaskCount].taskState->eip = Addrs;
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
    TasksList[TaskCount].taskState->esp = (u32)stack + stackSize;
    TasksList[TaskCount].taskState->ebp = (u32)stack;
    TasksList[TaskCount].taskState->PageDir = pageDir; //test

    //
    //    //Tss_32 *TaskState = new Tss_32();
    //    
    //    TaskState->eip = (u32) Addrs;
    //    TaskState->cs = CPUAddress->makeSelector(1, 0, 0);
    //    TaskState->ds = CPUAddress->makeSelector(2, 0, 0);
    //    TaskState->es = CPUAddress->makeSelector(2, 0, 0);
    //    TaskState->gs = CPUAddress->makeSelector(2, 0, 0);
    //    TaskState->fs = CPUAddress->makeSelector(2, 0, 0);
    //    TaskState->ss = CPUAddress->makeSelector(2, 0, 0);
    ////    TaskState->ss0 = CPUAddress->makeSelector(2, 0, 0);
    //
    //
    //
    //    //u32 Entry = CPUAddress->addGDTDesc(sizeof (Tss_32), (u32) TaskState, tss_p_rng0, 0x80); //verificar
    //
    //    u16 Sel = CPUAddress->makeSelector(Entry, 0, 0);
    //
    //    if (loadTaskReg) {
    //        CPUAddress->LTR(Sel);
    //    }
    //
    //
    //    // su32 TsNm = 0;
    //
    //    //TaskSels[TsNm++] = Sel;


    // return Sel;
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
}

Tasks::Task Tasks::getTask(u32 index) {
    return TasksList[index];
}