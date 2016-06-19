/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   driverManager.h
 * Author: david
 *
 * Created on 10 de Junho de 2016, 21:00
 */

#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include "../../util/util.h"
#include "../processor.h"

class driverManager {
public:

    struct Drivers {
        const s8 *name;
        void (* irqListener)();
        u32 driverId;
        processor::TSSEntry *drvTss;
    } __attribute__((packed));

    

    driverManager();
    // driverManager(const driverManager& orig);
    // virtual ~driverManager();

    static void setup();
    static u32 addDriver(const s8 *name, processor::TSSEntry *drvTss);
    static void callDriverByIRQ(u16 IRQId);
    static void callDriverMain(u32 driverId);
    static void updateDriverIRQAddrs(u32 driverID, void (* irqListener)());

private:
    
    static Drivers *drvManager;
    static u16 maxDrivers;
    static u16 currDrivers;

};

#endif /* DRIVERMANAGER_H */

