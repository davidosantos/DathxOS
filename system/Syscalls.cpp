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

extern "C" void SyscallsDelivery(u32 parameter){
    Syscalls::interruptReceiver(parameter);
}


void Syscalls::interruptReceiver(u32 function) {
    CallsDirectives *directive = (CallsDirectives*) function;
    switch (directive->Function) {
        case 1:
            switch(directive->Subfunction){
                
                
                case 2 :
                    Console::print(directive->y, directive->x, directive->String, directive->Value);
                    break;
            }
            
            break;
        case 2:
            Console::clear();
            break;
    }

}
//Syscalls::Syscalls(const Syscalls& orig) {
//}
//
//Syscalls::~Syscalls() {
//}

