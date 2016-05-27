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
    Syscalls::interruptReceiver(parameter);
}

void Syscalls::interruptReceiver(u32 function) {
    if (function > 10) {

        CallsDirectives *directive = (CallsDirectives*) function;

        switch (directive->Function) {
            case Print: //Print Text
                switch (directive->Subfunction) {
                    case 1:
                        Console::print(directive->y, directive->x, directive->String);
                        break;

                    case 2:
                        Console::print(directive->y, directive->x, directive->String, directive->Value);
                        break;
                    case 3:
                        Console::print(directive->y, directive->x, directive->String);
                        break;
                }

                break;
            case 2:
                Console::clear();
                break;
            case IRQinstall:
                Drivers::IRQHandlerAddrs *irqHandlerAddrs = (Drivers::IRQHandlerAddrs*) directive->Value;
                IRQHandler::add(irqHandlerAddrs->IRQid, irqHandlerAddrs->listener);
                break;
        }
    } else {

        if (function == 3) {
            Console::print(45, 0, "Integrity check error");
        }
    }

}
//Syscalls::Syscalls(const Syscalls& orig) {
//}
//
//Syscalls::~Syscalls() {
//}
