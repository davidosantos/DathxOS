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

extern "C" void SyscallsDelivery(u32 parameter, Paging::PageDirectory *pageDir) {
    SysCallHandler::interruptReceiver(parameter, pageDir);
}

void SysCallHandler::interruptReceiver(u32 function, Paging::PageDirectory *pageDir) {
    if (function > 10) {

        CallsDirectives *directive = (CallsDirectives*) Paging::getPhysAddrs((u32*) function, pageDir);

        switch (directive->Function) {
            case Print: //Print Text
            {
                switch (directive->Subfunction) {
                    case Print:
                        Console::print((const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir));
                        break;
                    case PrintatXY:
                        Console::print(directive->y, directive->x, (const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir));
                        break;

                    case PrintatXYwArgs:
                        Console::print(directive->y, directive->x,
                                (const s8*) Paging::getPhysAddrs((u32*) directive->String, pageDir), directive->Value);
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
            case IRQinstall:
            {
                Drivers::IRQHandlerAddrs *irqHandlerAddrs =
                        (Drivers::IRQHandlerAddrs*) Paging::getPhysAddrs((u32*)
                        directive->Value, pageDir);
                IRQHandler::add(irqHandlerAddrs->IRQid, irqHandlerAddrs->listener, irqHandlerAddrs->driverId);
            }
                break;
            case BroadCastMessage:
            {
                Messaging::message *messageAddrs = (Messaging::message*)
                        Paging::getPhysAddrs((u32*) directive->Value, pageDir);
                Messaging::broadcastMessage(messageAddrs);
    
            }
                break;
            default:
            {
                Console::print("SysCallHandler: no such function: %i", directive->Function);
            }
                break;

        }



    } else {
        static u32 count = 0;
        if (function == 1) {
            Console::print(45, 0, "Integrity check error eax %i", count);
        }
        if (function == 2) {
            Console::print(45, 0, "Integrity check error ebx %i", count);
        }
        if (function == 3) {
            Console::print(45, 0, "Integrity check error ecx %i", count);
        }
        if (function == 4) {
            Console::print(45, 0, "Integrity check error edx %i", count);
        }
        if (function == 5) {
            Console::print(45, 0, "Integrity check error ebp %i", count);
        }
        if (function == 6) {
            Console::print(45, 0, "Integrity check error esp %i", count);
        }
        if (function == 7) {
            Console::print(45, 0, "Integrity check error esi %i", count);
        }
        if (function == 8) {
            Console::print(45, 0, "Integrity check error edi %i", count);
        }

        count++;

    }

}
//Syscalls::Syscalls(const Syscalls& orig) {
//}
//
//Syscalls::~Syscalls() {
//}

