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
#include "../../library/DathxLib/Drivers.h"
#include "../../library/DathxLib/Syscalls.h"


extern "C" void SyscallsDelivery(u32 parameter);



class SysCallHandler {
    /**
     
     */


public:

    static void interruptReceiver(u32 function);

    //Syscalls(CPU *cpu);
    // Syscalls(const Syscalls& orig);
    // virtual ~Syscalls();
private:
//    CPU *CPUAddress;

};

#endif	/* SYSCALLS_H */

