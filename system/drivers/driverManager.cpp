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
    currDrivers = 1;
}

u32 driverManager::addDriver(const s8 *name, processor::TSSEntry *drvTss) {
    if(currDrivers <= maxDrivers){
    drvManager[currDrivers].name = name;
    drvManager[currDrivers].drvTss = drvTss;
    drvManager[currDrivers].driverId = currDrivers;
    return currDrivers++;
    } else {
        Console::print("driverManager: Cannot add no more drivers");
    }
    return 0;
}

void driverManager::callDriverByIRQ(u16 driverId) {

    for (int i = 1; i < currDrivers; i++) {
        if (drvManager[i].driverId == driverId) {
            processor::TSSInts = *drvManager[i].drvTss;
            if (drvManager[i].irqListener) {
                processor::TSSInts = *drvManager[i].drvTss;
                processor::TSSInts.eax =0;
                processor::TSSInts.ebx =0;
                processor::TSSInts.ecx =0;
                processor::TSSInts.edx =0;
                processor::TSSInts.esi =0;
                processor::TSSInts.edi =0;
                processor::TSSInts.eip = (u32) drvManager[i].irqListener;
                asm("lcall   $0x40,$0");
            } else {
                Console::print("driverManager: driver %i has no irqListener.", i);
            }


        }
    }

}

void driverManager::callDriverMain(u32 driverId) {
    if (drvManager[driverId].drvTss->eip) {
        processor::TSSInts = *drvManager[driverId].drvTss;
        processor::TSSInts.eax = driverId; //inform the driver its Id
        asm("lcall   $0x40,$0");
    } else {
        Console::print("driverManager: driver %i has no entry point.", driverId);
    }
}

void driverManager::updateDriverIRQAddrs(u32 driverId, void (* irqListener)()) {
    if (driverId <= currDrivers && driverId > 0) {
        drvManager[driverId].irqListener = irqListener;
    } else {
        Console::print("driverManager: driverId %i doesn't exists.", driverId);
    }
}