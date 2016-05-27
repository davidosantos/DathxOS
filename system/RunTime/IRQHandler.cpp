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
Paging::PagesDir *IRQHandler::pageDirs[maxFunction];

void IRQHandler::setup() {

    handlers = new Irq();
    for (int i = 0; i < maxFunction; i++) {
        handlers->functions[i] = 0;
    }

}

void IRQHandler::add(u32 id, void (* funtion)()) {
    bool added = false;
    if (id < maxIRQ) {
        u32 base = id * 64;
        for (u32 i = base; i < (base + 64); i++) {
            if (handlers->functions[i] == 0) { // if empty
                handlers->functions[i] = funtion;
                pageDirs[i] = (Paging::PagesDir*) processor::getPDBR();
                Console::print("IRQ: added handler for IRQ %i.", id);
                Console::print("IRQ: handler address is %h.", (u32)Paging::getPhysAddrs((u32*)handlers->functions[i],pageDirs[i]));
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
            if (*handlers->functions[i]) {
                 processor::loadPDBR(pageDirs[i]);
                (*handlers->functions[i])();
                dispached = true;
            } else {
                if (!dispached)
                    Console::print("IRQ dispatch: No handler for IRQ %i", id);
                break;
            }
        }
    } else {
        Console::print("IRQ dispatch: id is greater than maximum %i", maxIRQ);
    }
}

extern "C" void HandlerIRQ00() {

    //Console::print("IRQ00");

    IRQHandler::dispatch(0);
}

extern "C" void HandlerIRQ01() {
    
    IRQHandler::dispatch(1);
}

extern "C" void HandlerIRQ02() {
    Console::print("IRQ02");
    IRQHandler::dispatch(2);
}

extern "C" void HandlerIRQ03() {
    Console::print("IRQ03");
    IRQHandler::dispatch(3);
}

extern "C" void HandlerIRQ04() {
    Console::print("IRQ04");
    IRQHandler::dispatch(4);
}

extern "C" void HandlerIRQ05() {
    Console::print("IRQ05");
    IRQHandler::dispatch(5);
}

extern "C" void HandlerIRQ06() {
    Console::print("IRQ06");
    IRQHandler::dispatch(6);
}

extern "C" void HandlerIRQ07() {
    Console::print("IRQ07");
    IRQHandler::dispatch(7);
}

extern "C" void HandlerIRQ08() {
    Console::print("IRQ08");
    IRQHandler::dispatch(8);
}

extern "C" void HandlerIRQ09() {
    Console::print("IRQ09");
    IRQHandler::dispatch(9);
}

extern "C" void HandlerIRQ10() {
    Console::print("IRQ10");
    IRQHandler::dispatch(10);
}

extern "C" void HandlerIRQ11() {
    Console::print("IRQ11");
    IRQHandler::dispatch(11);
}

extern "C" void HandlerIRQ12() {
    Console::print("IRQ12");
    IRQHandler::dispatch(12);
}

extern "C" void HandlerIRQ13() {
    Console::print("IRQ13");
    IRQHandler::dispatch(13);
}

extern "C" void HandlerIRQ14() {
    Console::print("IRQ14");
    IRQHandler::dispatch(14);
}

extern "C" void HandlerIRQ15() {
    Console::print("IRQ15");
    IRQHandler::dispatch(15);
}
