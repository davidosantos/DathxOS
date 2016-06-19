/* 
 * File:   Syscalls.h
 * Author: davidosantos
 *
 * Created on July 27, 2015, 9:03 PM
 */

#ifndef SysCallHandler_h
#define	SysCallHandler_h

#include "../../util/util.h"
#include "../../system/monitor/Console.h"
#include "../../system/RunTime/IRQHandler.h"
#include "../../DathxLib/Drivers.h"
#include "../../DathxLib/Syscalls.h"
#include "../Providers/Messaging.h"


extern "C" void SyscallsDelivery(u32 parameter, Paging::PageDirectory *pageDir);



class SysCallHandler {
    /**
     
     */


public:

    static void interruptReceiver(u32 function, Paging::PageDirectory *pageDir);

    //Syscalls(CPU *cpu);
    // Syscalls(const Syscalls& orig);
    // virtual ~Syscalls();
private:
//    CPU *CPUAddress;

};

#endif	/* SYSCALLS_H */

