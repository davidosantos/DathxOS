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

void IntsReturnTaskSwitch(processor::GeneralPurposeRegs regs, processor::LinkBackRng3 linkBack) {

    //eax, ecx, edx, ebx, esp, ebp, esi, edi
    Tasks::TasksList[Tasks::runningTask].taskState->eax = regs.eax;
    Tasks::TasksList[Tasks::runningTask].taskState->ecx = regs.ecx;
    Tasks::TasksList[Tasks::runningTask].taskState->edx = regs.edx;
    Tasks::TasksList[Tasks::runningTask].taskState->ebx = regs.ebx;
    Tasks::TasksList[Tasks::runningTask].taskState->esp = linkBack.esp;
    Tasks::TasksList[Tasks::runningTask].taskState->ebp = regs.ebp;
    Tasks::TasksList[Tasks::runningTask].taskState->esi = regs.esi;
    Tasks::TasksList[Tasks::runningTask].taskState->edi = regs.edi;
    Tasks::TasksList[Tasks::runningTask].taskState->eip = linkBack.eip;
    Tasks::TasksList[Tasks::runningTask].taskState->cs = linkBack.cs;
    Tasks::TasksList[Tasks::runningTask].taskState->eflags = linkBack.eflags;
    Tasks::TasksList[Tasks::runningTask].taskState->ss = linkBack.ss;

    Tasks::switchTask();
    APIC::issueEOI();
}

/**
 * Cause a task switch to a internal task to save the current task
 * in the internal task, load eipReg that was saved by interrupt 0x00
 * into the outgoing tss's EIP.
 * @param eipReg last task eip.
 */
void Tasks::switchTask() {
    runningTask = Tasks::nextTask(runningTask);
    loadTask(TasksList[runningTask].taskIndex);
}

u32 Tasks::runningTask = 0;
s32 Tasks::TaskCount = 0;


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
    Paging::PageDirectory *pageDir;
    u32 *loadAddrs; // = (u32*) Paging::getNewPage();

    if (exec->openFile(file) == OK) {
        pageDir = Paging::getNewDir();
        loadAddrs = new u32 [exec->pHeader[0].p_memsz];
        Paging::mapRange(0x100000, 0x700000, pageDir, (u32*) 0x100000, true);


        Paging::mapRange(exec->pHeader[0].p_vaddr, (exec->pHeader[0].p_vaddr +
                exec->pHeader[0].p_memsz), pageDir, true);

        if (exec->loadProgram(pageDir) == Error) {
            Console::print("%cttELF Loader: Error Loading file %s", file);
        } else {
            u32 *stack = new u32 [1024];
            Paging::mapRange((u32) stack, (u32) stack + pageSize, pageDir, stack, true);
            Tasks::NewTask(file, exec->Header->e_entry, pageDir, stack, 1024, 3);
            Console::print("%ctuELF Loader: File loaded %s", file);

            // Console::print("%ctuELF Loader: File loaded %h", (u32)Paging::getPhysAddrs((u32*)exec->pHeader[0].p_vaddr,pageDir));
            // Console::print("%ctuELF Loader: File loaded %h", exec->pHeader[0].p_vaddr);
        }
    } else {
        Console::print("%cttELF Loader: File open error %s", file);
    }
}

void Tasks::NewTask(const s8 *name, void (*function)(), Paging::PageDirectory *pageDir, u32 *stack, u32 stackSize, u8 ring) {


    TasksList[TaskCount].Name = name;
    TasksList[TaskCount].PID = (u32) pageDir;
    TasksList[TaskCount].Addrs = function;
    TasksList[TaskCount].taskState = new processor::TSSEntry();
    TasksList[TaskCount].MessageListener = false;
    TasksList[TaskCount].pStatus = Running;
    TasksList[TaskCount].taskIndex = TaskCount;

    u16 sel_data = 0;
    u16 sel_code = 0;

    if (ring == 0) {


        sel_data = processor::getRng0Data();
        sel_code = processor::getRng0Code();
        TasksList[TaskCount].taskState->eflags = 0x203202;
    } else {

        sel_data = processor::getRng3Data();
        sel_code = processor::getRng3Code();
        TasksList[TaskCount].taskState->eflags = 0x203202;
    }
    if ((TaskCount - 1) == 0) { //necessary for the first task 0 to be reliable

    }

    TasksList[TaskCount].taskState->eip = (u32) function;
    TasksList[TaskCount].taskState->eax = TasksList[TaskCount].PID; //pass it to the lib
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
    TasksList[TaskCount].taskState->cr3 = (u32) pageDir; //test
    Console::print("%ELF Loader: File loaded %h", TasksList[TaskCount].taskState->cr3);
    u32 espKernel = 0;
    asm("movl %%esp,%0\n" : "=m" (espKernel) ::);
    TasksList[TaskCount].taskState->ss0 = 0x10;
    TasksList[TaskCount].taskState->esp0 = espKernel;
    processor::TSSrng0.prev_tss = 0x38;
    processor::TSSrng3 = *TasksList[TaskCount].taskState;



    TaskCount++;

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
    TasksList[task_Id].taskState->cr3 = cr3Reg;

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
    cr3Reg = (u32) TasksList[task_Id].taskState->cr3;


}

Tasks::Task Tasks::getTask(u32 index) {
    return TasksList[index];
}

Tasks::Task *Tasks::getTaskbyPid(u32 pid) {
    for (s32 i = 0; i <= TaskCount; i++) {

        if (TasksList[i].PID == pid) {
            return &TasksList[i];
        }

    }
    return 0;
}

void Tasks::killProcess(u32 pid) {
    Task *task = getTaskbyPid(pid);
    if (task == 0) {
        Console::print("Task: Error pid not found %h", pid);
    } else {


        Paging::deAlloc((Paging::PageDirectory*)task->taskState->cr3);
        TaskCount--;

        Console::print("killProcess runningTaskb %i", runningTask);
        //runningTask = Tasks::nextTask(TaskCount);
        Console::print("killProcess task->Name %s", task->Name);
        Console::print("killProcess task->taskState->cr3 %h", task->taskState->cr3);
        Console::print("killProcess processor::getPDBR() %h", processor::getPDBR());
        //Console::print(49, 0, "killProcess runningTask %i", task->taskIndex);
        // Console::print("killProcess task->PID %h", task->PID);

        //load next task so that the system call has a task to return to.
        // Console::print("TSSrng3 ss0 %h", processor::TSSrng3.ss0);
        // Console::print("TSSrng3 esp0 %h", processor::TSSrng3.esp0);
        //Console::print("getPDBR %h", processor::getPDBR());
    }
    processor::TSSrng3 = *TasksList[0].taskState;
    // runningTask =0;
    // loadTask(runningTask);
    // Console::print("TasksList[0].taskState %h", TasksList[0].taskState->cr3);

    processor::LTR(processor::makeSelector(processor::TssSelRng3tmp, 0, true));
    processor::GDT[processor::TssSelRng3].type = tss_p_rng3;
    task->pStatus = Destroyed;
    task->MessageListener = false;
    task->taskState = 0;
    task->PID = 0;
    task = 0;
    asm("ljmp $0x33,$0");

}

u32 Tasks::nextTask(u32 RunningTask_Id) {

    for (s32 i = RunningTask_Id + 1; i < TaskCount; i++) {
        if (TasksList[i].pStatus == Running) {
            return TasksList[i].taskIndex;
        }
    }
    return 0;
}
