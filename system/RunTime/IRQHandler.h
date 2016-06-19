/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IRQHandler.h
 * Author: david
 *
 * Created on 24 de Maio de 2016, 20:08
 */

#ifndef IRQHANDLER_H
#define IRQHANDLER_H

#include "../../util/util.h"
#include "../memory/Memory.h"
#include "../processor.h"
#include "../drivers/driverManager.h"

#define maxFunction 1024
#define maxIRQ 16
#define msgDisplayed 0xffffffff


class IRQHandler {
    struct Irq {
        u32 irqId [maxFunction];
        u32 driverId [maxFunction];
    } __attribute((packed));
    static Irq *handlers;
   
public:
    static void setup();
    static void add(u32 id, void (* funtion)(), u32 driverId);
    static void dispatch(u32 id);
    IRQHandler();
    //    IRQHandler(const IRQHandler& orig);
    //    virtual ~IRQHandler();
private:

};

#endif /* IRQHANDLER_H */

