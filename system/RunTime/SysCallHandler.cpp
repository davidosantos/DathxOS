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

extern "C" void SyscallsDelivery(u32 parameter) {
    SysCallHandler::interruptReceiver(parameter);
}

void SysCallHandler::interruptReceiver(u32 function) {
    if (function > 10) {

        CallsDirectives *directive = (CallsDirectives*) function;

        switch (directive->Function) {
            case Print: //Print Text
            {
                switch (directive->Subfunction) {
                    case Print:
                        Console::print(directive->String);
                        break;
                    case PrintatXY:
                        Console::print(directive->y, directive->x, directive->String);
                        break;

                    case PrintatXYwArgs:
                        Console::print(directive->y, directive->x, directive->String, directive->Value);
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
                Drivers::IRQHandlerAddrs *irqHandlerAddrs = (Drivers::IRQHandlerAddrs*) directive->Value;
                IRQHandler::add(irqHandlerAddrs->IRQid, irqHandlerAddrs->listener);
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
            Console::print(45, 0, "Integrity check error eax %i",count);
        }
        if (function == 2) {
            Console::print(45, 0, "Integrity check error ebx %i",count);
        }
        if (function == 3) {
            Console::print(45, 0, "Integrity check error ecx %i",count);
        }
        if (function == 4) {
            Console::print(45, 0, "Integrity check error edx %i",count);
        }
        if (function == 5) {
            Console::print(45, 0, "Integrity check error ebp %i",count);
        }
        if (function == 6) {
            Console::print(45, 0, "Integrity check error esp %i",count);
        }
        if (function == 7) {
            Console::print(45, 0, "Integrity check error esi %i",count);
        }
        if (function == 8) {
            Console::print(45, 0, "Integrity check error edi %i",count);
        }
        
        count++;
        
    }

}
//Syscalls::Syscalls(const Syscalls& orig) {
//}
//
//Syscalls::~Syscalls() {
//}

