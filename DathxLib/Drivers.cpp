/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drivers.cpp
 * Author: david
 * 
 * Created on 4 de Junho de 2016, 22:24
 */

#include "Drivers.h"

Drivers::Drivers() {
}

u32 Drivers::driverId;

void Drivers::IrqInstall(u32 irqNum) {
    static Drivers::IRQHandlerAddrs irq, *irqp;
    static CallsDirectives call, *callp;
    callp = &call;
    
    irqp = &irq;
    irqp->IRQid = irqNum;
    irqp->driverId = driverId;
    irqp->listener = localListener;
    
    callp->Function = sys_call_IRQinstall;
    callp->Value = (u32) irqp;

    asm (
                "int $0x80;"
                :
                : "a"(sys_call_IRQinstall), "c" (callp) /* input */
                );
}

void DriverMain() {
    asm("movl %%eax,%0" ::"m" (Drivers::driverId) : "eax");
    
    main();

    asm("iret");
}

void localListener() {

    IrqListener();
    asm("iret");
}