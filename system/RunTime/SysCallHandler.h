/* 
 * File:   Syscalls.h
 * Author: davidosantos
 *
 * Created on July 27, 2015, 9:03 PM
 */

#ifndef SysCallHandler_h
#define SysCallHandler_h

#include "../../util/util.h"
#include "../../system/monitor/Console.h"
#include "../../system/RunTime/IRQHandler.h"
#include "../../DathxLib/Drivers.h"
#include "../Providers/Messaging.h"


extern "C" void SyscallsDelivery(Paging::PageDirectory *pageDir);

extern "C" u32 sys_call_eax;
extern "C" u32 sys_call_ecx;
extern "C" u32 sys_call_edx;
extern "C" u32 sys_call_ebx;
extern "C" u32 sys_call_esp;
extern "C" u32 sys_call_ebp;
extern "C" u32 sys_call_esi;
extern "C" u32 sys_call_edi;


#define     sys_call_print                   1
#define     sys_call_printwArgs              2
#define     sys_call_printatXY               3
#define     sys_call_printatXYwArgs          4
#define     sys_call_printatXYwString        5
#define     sys_call_printClear              6
/*
 *|sys_call_eax | sys_call_broadCastMessage           |
 *|---------------------------------------------------|
 *|Input                                              |
 *|---------------------------------------------------|
 *|sys_call_ecx |MessageAddrs::keyCode                |
 *|sys_call_edx |MessageAddrs::keyChar                |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 *|---------------------------------------------------|
 *|Output                                             |
 *|---------------------------------------------------|
 *|sys_call_eax |                                     |
 *|sys_call_ecx |                                     |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 */
#define     sys_call_broadCastMessage        10
/*
 *|sys_call_eax | sys_call_initiateMessaging          |
 *|---------------------------------------------------|
 *|Input                                              |
 *|---------------------------------------------------|
 *|sys_call_ecx |                                     |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 *|---------------------------------------------------|
 *|Output                                             |
 *|---------------------------------------------------|
 *|sys_call_eax | Messaging::message *messageAddrss   |
 *|sys_call_ecx | inbox.inboxCapacity                 |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 */
#define     sys_call_initiateMessaging       12

/*
 *|sys_call_eax | sys_call_readMessage                |
 *|---------------------------------------------------|
 *|Input                                              |
 *|---------------------------------------------------|
 *|sys_call_ecx |                                     |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 *|---------------------------------------------------|
 *|Output                                             |
 *|---------------------------------------------------|
 *|sys_call_eax | MessageAddrs::keyCode               |
 *|sys_call_ecx | MessageAddrs::keyChar               |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 */
#define     sys_call_readMessage             13
/*
 *|sys_call_eax | sys_call_isThereMessage             |
 *|---------------------------------------------------|
 *|Input                                              |
 *|---------------------------------------------------|
 *|sys_call_ecx |                                     |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 *|---------------------------------------------------|
 *|Output                                             |
 *|---------------------------------------------------|
 *|sys_call_eax | 1 -> yes,  0 -> no                  |
 *|sys_call_ecx |                                     |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 */
#define     sys_call_isThereMessage          14



#define     sys_call_IRQinstall              20

/*
 *|sys_call_eax | sys_call_alloc                      |
 *|---------------------------------------------------|
 *|Input                                              |
 *|---------------------------------------------------|
 *|sys_call_ecx |size                                 |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 *|---------------------------------------------------|
 *|Output                                             |
 *|---------------------------------------------------|
 *|sys_call_eax | Address                             |
 *|sys_call_ecx |                                     |
 *|sys_call_edx |                                     |
 *|sys_call_ebx |                                     |
 *|sys_call_ebp |                                     |
 *|sys_call_esi |                                     |
 *|sys_call_edi |                                     |
 */
#define     sys_call_alloc                   30






struct CallsDirectives {
    u8 x, y;
    const s8 *String;
    u16 Function;
    u16 Subfunction;
    u32 Value;
} __attribute__((packed));
;

class SysCallHandler {
    /**
     
     */


public:

    static void interruptReceiver(Paging::PageDirectory *pageDir);

    //Syscalls(CPU *cpu);
    // Syscalls(const Syscalls& orig);
    // virtual ~Syscalls();
private:
    //    CPU *CPUAddress;

};

#endif /* SYSCALLS_H */

