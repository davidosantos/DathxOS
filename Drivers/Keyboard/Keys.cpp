/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Keys.cpp
 * Author: david
 *
 * Created on 25 de Maio de 2016, 21:54
 */

#include "../../DathxLib/Drivers.h"
#include "../../DathxLib/Syscalls.h"
#include "../../system/drivers/HardwareIO.h"

static void listener() {
    const s8 *name = "Test of System Calls by Driver %h";

    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = Print;
    callp->Subfunction = 2;
    callp->y = 41;
    callp->x = 0;
    callp->String = name;
    callp->Value = HardwareIO::inb(0x60);
    HardwareIO::outb(0xA0,0x20);
    HardwareIO::outb(0x20,0x20);
    asm("movl %0,%%eax" ::"m" (callp) : "eax");
    asm("int $0x80");
}

u8 HardwareIO::inb(u16 port) {

    u8 result;

    asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));

    return (result);
}

void HardwareIO::outb(u16 port, u8 cmd) {

    asm volatile("outb %1, %0" : : "dN" (port), "a" (cmd));

}

/*
 * 
 */
int main() {

    static CallsDirectives call, *callp;
    static Drivers::IRQHandlerAddrs irq, *irqp;

    callp = &call;
    irqp = &irq;

    irqp->IRQid = 1;
    irqp->listener = listener;


    callp->Function = IRQinstall;
    //callp->Subfunction = 2;
    // callp->y = 47;
    //callp->x = 0;
    callp->Value = (u32) irqp;
    //callp->String = name;

    //pony++;
    //asm("movl %0,%%eax" ::"m" (*pony) : "eax");
    asm("movl %0,%%eax" ::"m" (callp) : "eax");
    asm("int $0x80");

    return 0;
}

