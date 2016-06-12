/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   driverManager.cpp
 * Author: david
 * 
 * Created on 10 de Junho de 2016, 21:00
 */

#include "driverManager.h"


driverManager::Drivers *driverManager::drvManager;
u16 driverManager::maxDrivers;
u16 driverManager::currDrivers;

driverManager::driverManager() {

}

//driverManager::driverManager(const driverManager& orig) {
//}
//
//driverManager::~driverManager() {
//}

void driverManager::setup() {
    maxDrivers = pageSize / sizeof (driverManager::Drivers);
    drvManager = new Drivers [maxDrivers];
    currDrivers = 0;
}

void driverManager::addDriver(const s8 *name, u32 *address, u32 irqID, processor::TSSEntry *drvTss) {
    drvManager[currDrivers].name = name;
    drvManager[currDrivers].address = address;
    drvManager[currDrivers].irqID = irqID;
    drvManager[currDrivers].drvTss = drvTss;
    currDrivers++;
}

void driverManager::callDriverByIRQ(u16 IRQId) {
    u16 currTrSel;
    for (int i = 0; i < currDrivers; i++) {
        if (drvManager[i].irqID == IRQId) {
            *processor::TSSInts = *drvManager[i].drvTss;
//            currTrSel = processor::STR();
//            
//            if (currTrSel != processor::makeSelector(processor::TssSelRng0, false, false)){
//                processor::LTR(processor::makeSelector(processor::TssSelRng0, false, false));
//                Console::print("currTrSel: %h",currTrSel);
//                processor::LTR(currTrSel);
//            }
            asm("lcall   $0x40,$0");
           

        }
    }

}
