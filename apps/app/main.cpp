/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on 14 de Novembro de 2015, 14:51
 */


//using namespace std;
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
    //u32 *pony = 0;
    while (true) {

        value++;

        callp->Function = 1;
        callp->Subfunction = 2;
        callp->y = 47;
        callp->x = 0;
        callp->Value = value;
        callp->String = name;

        //pony++;
        //asm("movl %0,%%eax" ::"m" (*pony) : "eax");
       asm("movl %0,%%eax" ::"m" (callp): "eax");
       asm("int $0x80");
        
        ;

    const u8 msg[] = {"Ring 3 Task"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 14;
        *(videoPtr + 20) = i;
    }

    }

    return 0;
}

