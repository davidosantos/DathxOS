/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IRQHandler.cpp
 * Author: david
 * 
 * Created on 24 de Maio de 2016, 20:08
 */

#include "IRQHandler.h"

IRQHandler::IRQHandler() {
}

//IRQHandler::IRQHandler(const IRQHandler& orig) {
//}
//
//IRQHandler::~IRQHandler() {
//}

IRQHandler::Irq *IRQHandler::handlers;

void IRQHandler::setup() {

    handlers = new Irq();
    for (int i = 0; i < maxFunction; i++) {
        handlers->irqId[i] = 0;
        handlers->driverId[i] = 0;
    }

}

void IRQHandler::add(u32 id, void (* listener)(),u32 driverId) {
    bool added = false;
    if(driverId == 0){
        Console::print("IRQ add: driverId is 0, something is wrong");
        return;
    }
    if (id < maxIRQ) {
        u32 base = id * 64;
        for (u32 i = base; i < (base + 64); i++) {
            if (handlers->irqId[i] == 0 || handlers->irqId[i] == msgDisplayed) { // if empty
                handlers->irqId[i] = id;
                handlers->driverId[i] = driverId;
                driverManager::updateDriverIRQAddrs(driverId,listener);
                Console::print("IRQ: added handler for IRQ %i.", id);
                Console::print("IRQ: driverId for IRQ handler %h.", driverId);
                added = true;
                break;
            }
        }
        if (!added)
            Console::print("IRQ: Handler not added for IRQ %i queue is full", id);
    } else {
        Console::print("IRQ: Not add, id is greater than maximum %i", maxIRQ);
        return;
    }

}

void IRQHandler::dispatch(u32 id) {
    bool dispached = false;
    if (id < maxIRQ) {
        u32 base = id * 64;
        for (u32 i = base; i < (base + 64); i++) {
            if (handlers->irqId[i] && handlers->irqId[i] != msgDisplayed) {
                if(handlers->driverId[i] ==0){
                    Console::print("IRQ dispatch: driverId is 0, something is wrong");
                    return;
                }
            
                driverManager::callDriverByIRQ(handlers->driverId[i]);
                dispached = true;
            } else {
                if (!dispached && handlers->irqId[i] != msgDisplayed) {
                    Console::print("IRQ dispatch: No handler for IRQ %i", id);
                }
                handlers->irqId[i] = msgDisplayed;
                break;
            }
        }
    } else {
        Console::print("IRQ dispatch: id is greater than maximum %i", maxIRQ);
    }
}

extern "C" void HandlerIRQ00() {

    IRQHandler::dispatch(1);
}

extern "C" void HandlerIRQ01() {

    IRQHandler::dispatch(2);
}

extern "C" void HandlerIRQ02() {
    
    IRQHandler::dispatch(3);
}

extern "C" void HandlerIRQ03() {
    
    IRQHandler::dispatch(4);
}

extern "C" void HandlerIRQ04() {
    
    IRQHandler::dispatch(5);
}

extern "C" void HandlerIRQ05() {
    Console::print("IRQ05");
    IRQHandler::dispatch(6);
}

extern "C" void HandlerIRQ06() {
    
    IRQHandler::dispatch(7);
}

extern "C" void HandlerIRQ07() {
    Console::print("IRQ07");
    IRQHandler::dispatch(8);
}

extern "C" void HandlerIRQ08() {
    
    IRQHandler::dispatch(9);
}

extern "C" void HandlerIRQ09() {
    
    IRQHandler::dispatch(10);
}

extern "C" void HandlerIRQ10() {
    
    IRQHandler::dispatch(11);
}

extern "C" void HandlerIRQ11() {
    
    IRQHandler::dispatch(12);
}

extern "C" void HandlerIRQ12() {
    
    IRQHandler::dispatch(13);
}

extern "C" void HandlerIRQ13() {
    
    IRQHandler::dispatch(14);
}

extern "C" void HandlerIRQ14() {
    
    IRQHandler::dispatch(15);
}

extern "C" void HandlerIRQ15() {
    
    IRQHandler::dispatch(16);
}
