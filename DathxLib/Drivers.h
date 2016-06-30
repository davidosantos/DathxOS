/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drivers.h
 * Author: david
 *
 * Created on 4 de Junho de 2016, 22:24
 */

#ifndef DRIVERS_H
#define DRIVERS_H
#include "../../Dathx OS/util/util.h"
#include "../system/RunTime/SysCallHandler.h"
/**
 * Warning: Dathx calls this function by a task switch, therefore by leaving NT
 *  flag in the eflags register on, system drivers must return the function with
 *  iret and never change the NT flags on the register, or else the system 
 * will crash.
 * 
 * This function is called once when de driver is first loaded, so the driver 
 * can initiate resources or system dependencies.
 * 
 * This function is defined inside the static library. And declared as extern
 * so that the compiler doesn't mess up its name, because it is referenced by
 * the linker script.
 */
extern "C" void DriverMain();

/**
 * Warning: Dathx calls this function by a task switch, therefore by leaving NT
 *flag in the eflags register on, system drivers must return the function with
 *iret and never change the NT flags on the register, or else the system 
 *will crash.
 */
void localListener();


extern "C" int main();
extern "C" void IrqListener();

class Drivers {
public:
    static u32 driverId;
    
    struct IRQHandlerAddrs {
        u32 IRQid;
        u32 driverId;
        void (*listener)();
    }__attribute__((packed));
    
    static void IrqInstall(u32 irqNum);
    
    Drivers();
    
    static void IRQListener();
private:
    

};


#endif /* DRIVERS_H */

