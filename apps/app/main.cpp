/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on 14 de Novembro de 2015, 14:51
 */


using namespace std;
#include "util.h"
#include "Syscalls.h"

/*
 * 
 */
int main(int argc, char** argv) {

    const s8 *name = "Test of System Calls %h";

    u32 value = 0;

    static CallsDirectives call, *callp;

    callp = &call;

    while (true) {
        
        value++;
        
        callp->Function = 1;
        callp->Subfunction = 2;
        callp->y = 47;
        callp->x = 0;
        callp->Value = value;
        callp->String = name;
        
        asm("movl %0,%%eax" ::"m" (callp));
        asm("int $0x80");

    }

    return 0;
}

