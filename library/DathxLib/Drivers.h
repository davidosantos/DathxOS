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
#include "../../util/util.h"
#include "../DathxLib/Syscalls.h"

class Drivers {
public:
    struct IRQHandlerAddrs {
        u32 IRQid;
        void (*listener)();
    }__attribute__((packed));
    
    static void IrqInstall(u32 irqNum, void (*listener)());
    
    Drivers();
    
    static void IRQListener();
private:
    

};

#endif /* DRIVERS_H */

