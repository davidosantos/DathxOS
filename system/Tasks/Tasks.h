/* 
 * File:   Tasks.h
 * Author: davidosantos
 *
 * Created on July 19, 2015, 10:34 AM
 */

#ifndef TASKS_H
#define TASKS_H
#include "../../util/util.h"
#include "../../system/memory/Paging.h"
#include "../../system/memory/Memory.h"
#include "../drivers/APIC.h"
#include "../RunTime/ElfLoader.h"
#include "../Providers/Messaging.h"


//Changed via nasm in InterruptsDel... external int one
extern u32 eaxReg, ecxReg, edxReg, ebxReg, espReg, ebpReg, esiReg, ediReg, eflags, eipReg, csReg, cr3Reg;
extern u16 ssReg, dsReg, esReg, fsReg, gsReg;
extern "C" u32 intsStart;
extern "C" u32 intsEnd;

extern "C" u32 SavedPageDirSysCall;
extern "C" u32 sys_call_eax;
extern "C" u32 sys_call_ebx;
extern "C" u32 sys_call_ecx;
extern "C" u32 sys_call_edx;
extern "C" u32 sys_call_esp;
extern "C" u32 sys_call_ebp;
extern "C" u32 sys_call_edi;
extern "C" u32 sys_call_esi;


extern "C" void IntsReturnTaskSwitch(processor::GeneralPurposeRegs regs,processor::LinkBackRng3 linkBack);

class Tasks {
public:

    static void switchTask();

    //void NewTask(const s8 *name, u32 Addrs);

    static void createProcess(const s8 *file);

    static void killProcess(u32 pid);

    static void NewTask(const s8 *name, void (*function)(), Paging::PageDirectory *pageDir, u32 *stack, u32 stackSize, u8 ring);

    static void NewInternalTask(u16 entry, const s8 *name, bool loadTaskReg, void (*Addrs)());

    static void inline saveTask(u32 task_Id);

    static void inline loadTask(u32 task_Id);

    static u32 nextTask(u32 task_Id);



    //Tasks(CPU *Cpu);
    //Tasks(const Tasks& orig);
    //virtual ~Tasks();
    static void internalTaskSwitcher();

    static u32 runningTask;

    static s32 TaskCount;

private:

    enum processStatus {
        unsed,
        Running,
        waiting,
        Destroyed

    };


public:

    struct Task {
        const s8 *Name;
        u16 Selector; //>> by 3 to get the gdt entry
        u32 PID;
        void (*Addrs)();
        processor::TSSEntry* taskState;
        Messaging::inbox inboxAddrss;
        bool MessageListener;
        processStatus pStatus;
        u32 taskIndex;
    } __attribute__((packed));

    static Task TasksList[50];
public:
    static Task getTask(u32 index);

    static Task *getTaskbyPid(u32 pid);

};

#endif /* TASKS_H */

