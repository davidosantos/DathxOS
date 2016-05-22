/* 
 * File:   Syscalls.cpp
 * Author: davidosantos
 * 
 * Created on July 27, 2015, 9:03 PM
 */

#include "Syscalls.h"

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
            case 1: //Print Text
                switch (directive->Subfunction) {


                    case 2:
                        Console::print(directive->y, directive->x, directive->String, directive->Value);
                        break;
                }

                break;
            case 2:
                Console::clear();
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

