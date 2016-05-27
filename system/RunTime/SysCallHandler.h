/* 
 * File:   Syscalls.h
 * Author: davidosantos
 *
 * Created on July 27, 2015, 9:03 PM
 */

#ifndef SYSCALLS_H
#define	SYSCALLS_H

#include "../../util/util.h"
#include "../../system/monitor/Console.h"
#include "../../DathxLib/Drivers.h"
#include "../../system/RunTime/IRQHandler.h"

#define     Print           1
#define     IRQinstall      20

extern "C" void SyscallsDelivery(u32 parameter);


struct CallsDirectives {
    u8 x, y;
    const s8 *String;
    u16 Function;
    u16 Subfunction;
    u32 Value;
}__attribute__((packed));;

class Syscalls {
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

