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


extern "C" void IntsReturnTaskSwitch();

class Tasks {
public:

    static void interruptReceiver();

    //void NewTask(const s8 *name, u32 Addrs);

    static void createProcess(const s8 *file);

    static void NewTask(const s8 *name, void (*function)(), Paging::PageDirectory *pageDir, u32 *stack, u32 stackSize, u8 ring);

    static void NewInternalTask(u16 entry, const s8 *name, bool loadTaskReg, void (*Addrs)());

    static void inline saveTask(u32 task_Id);

    static void inline loadTask(u32 task_Id);

    //Tasks(CPU *Cpu);
    //Tasks(const Tasks& orig);
    //virtual ~Tasks();
    static void internalTaskSwitcher();

    static u32 runningTask;

    static u32 TaskCount;

private:

    typedef struct Tss_32 {
        u8 taskPrevLevel;
        Paging::PageDirectory *PageDir;
        u32 eip;
        u32 eflags;
        u32 eax;
        u32 ecx;
        u32 edx;
        u32 ebx;
        u32 esp;
        u32 ebp;
        u32 esi;
        u32 edi;
        u16 es;
        u32 cs;
        u16 ss;
        u16 ds;
        u16 fs;
        u16 gs;
        u16 ldt_selector;

    } TaskState;


public:
    static Tss_32 *lastTss;

    struct Task {
        const s8 *Name;
        u16 Selector; //>> by 3 to get the gdt entry
        u32 PID;
        void (*Addrs)();
        TaskState* taskState;
        Messaging::inbox inboxAddrss;
        bool MessageListener;
    } __attribute__((packed));

    static Task TasksList[50];
public:
    static Task getTask(u32 index);
    
    static Task *getTaskbyPid(u32 pid);

};

#endif /* TASKS_H */

