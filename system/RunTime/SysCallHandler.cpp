/* 
 * File:   Syscalls.cpp
 * Author: davidosantos
 * 
 * Created on July 27, 2015, 9:03 PM
 */

#include "SysCallHandler.h"

//Syscalls::Syscalls(CPU *cpu) {
//
//}

extern "C" void SyscallsDelivery(Paging::PageDirectory *pageDir) {
    SysCallHandler::interruptReceiver(pageDir);
}

void SysCallHandler::interruptReceiver(Paging::PageDirectory *pageDir) {


    CallsDirectives *directive = (CallsDirectives*) Paging::getPhysAddrs((u32*) sys_call_ecx, pageDir);

    switch (sys_call_eax) {
        case sys_call_print: //Print Text
        {
            switch (directive->Subfunction) {
                case sys_call_print:
                    Console::print((const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir));
                    break;
                case sys_call_printwArgs:
                    Console::print((const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir),
                            directive->Value);
                    break;
                case sys_call_printatXY:
                    Console::print(directive->y, directive->x, (const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir));
                    break;

                case sys_call_printatXYwArgs:
                    Console::print(directive->y, directive->x,
                            (const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir), directive->Value);
                    break;
                case sys_call_printatXYwString:
                    Console::print(directive->y, directive->x,
                            (const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir),
                            (const s8*) Paging::getPhysAddrs((u32*) directive->Value, pageDir));
                    break;
                case sys_call_printClear:
                    Console::clear();
                    break;

                default:
                    Console::print("SysCallHandler: no such Sub-function of Print: %i", directive->Function);
                    break;
            }
        }
            break;
        case 2:
        {
            Console::clear();
        }
            break;
        case sys_call_IRQinstall:
        {
            Drivers::IRQHandlerAddrs *irqHandlerAddrs =
                    (Drivers::IRQHandlerAddrs*) Paging::getPhysAddrs((u32*)
                    directive->Value, pageDir);
            IRQHandler::add(irqHandlerAddrs->IRQid, irqHandlerAddrs->listener, irqHandlerAddrs->driverId);
        }
            break;
        case sys_call_broadCastMessage:
        {
            Messaging::MessageAddrs messageAddrs;
            messageAddrs.keycode = sys_call_ecx;
            messageAddrs.keychar = sys_call_edx;
            messageAddrs.type = Type_unread;
            Messaging::broadcastMessage(&messageAddrs);

        }
            break;
        case sys_call_initiateMessaging:
        {
            Messaging::MessageAddrs *messageAddrss = Messaging::initMessaging((u32) pageDir); //pid is the same as page dir address
            Paging::mapRange((u32) messageAddrss, (u32) messageAddrss + pageSize, pageDir, (u32*) messageAddrss, true);
            sys_call_eax = (u32) messageAddrss;
            sys_call_ecx = Tasks::getTaskbyPid((u32) pageDir)->inboxAddrss.inboxCapacity;

        }
            break;
        case sys_call_readMessage:
        {
            Messaging::MessageAddrs message = Messaging::readMessage((u32) pageDir);
            sys_call_eax = message.keycode;
            sys_call_ecx = message.keychar;

        }
            break;
        case sys_call_isThereMessage:
        {
            
            sys_call_eax = Messaging::isThereMessage((u32) pageDir) ? 1 : 0;

        }
            break;
        case sys_call_alloc:
        {
            sys_call_eax = (u32) new u32[sys_call_ecx];


        }
            break;

        default:
        {
            Console::print("SysCallHandler: no such function: %h", directive->Function);
            Console::print("SysCallHandler: sys_call_eax: %h", sys_call_eax);
            Console::print("SysCallHandler: sys_call_ecx: %h", sys_call_ecx);
        }
            break;

    }


    // if (function > 10) {
    //
    //    } else {
    //        static u32 count = 0;
    //        if (function == 1) {
    //            Console::print(45, 0, "Integrity check error eax %i", count);
    //        }
    //        if (function == 2) {
    //            Console::print(45, 0, "Integrity check error ebx %i", count);
    //        }
    //        if (function == 3) {
    //            Console::print(45, 0, "Integrity check error ecx %i", count);
    //        }
    //        if (function == 4) {
    //            Console::print(45, 0, "Integrity check error edx %i", count);
    //        }
    //        if (function == 5) {
    //            Console::print(45, 0, "Integrity check error ebp %i", count);
    //        }
    //        if (function == 6) {
    //            Console::print(45, 0, "Integrity check error esp %i", count);
    //        }
    //        if (function == 7) {
    //            Console::print(45, 0, "Integrity check error esi %i", count);
    //        }
    //        if (function == 8) {
    //            Console::print(45, 0, "Integrity check error edi %i", count);
    //        }
    //
    //        count++;
    //
    //    }

}
//Syscalls::Syscalls(const Syscalls& orig) {
//}
//
//Syscalls::~Syscalls() {
//}

