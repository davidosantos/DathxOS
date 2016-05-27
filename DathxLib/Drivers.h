/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Driver.h
 * Author: david
 *
 * Created on 25 de Maio de 2016, 21:48
 */

#ifndef DRIVERS_H
#define DRIVERS_H
#include "../util/util.h"

class Drivers {
public:
    
    struct IRQHandlerAddrs {
        u32 IRQid;
        void (*listener)();
    }__attribute__((packed));
    
    Drivers();
   // Driver(const Driver& orig);
    //virtual ~Driver();
    
    static void IRQListener();
    
private:

};

#endif /* DRIVERS_H */

