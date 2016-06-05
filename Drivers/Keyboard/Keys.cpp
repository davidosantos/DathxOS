/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Keys.cpp
 * Author: david
 *
 * Created on 25 de Maio de 2016, 21:54
 */

#include "../../library/DathxLib/Drivers.h"
#include "../../system/drivers/HardwareIO.h"
#include "../../library/DathxLib/io/out.h"

static void listener() {


    out::print(41,0,"Test of System Calls by Driver %h", HardwareIO::inb(0x60));
   
    
    HardwareIO::outb(0xA0, 0x20);
    HardwareIO::outb(0x20, 0x20);
}

u8 HardwareIO::inb(u16 port) {

    u8 result;

    asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));

    return (result);
}

void HardwareIO::outb(u16 port, u8 cmd) {

    asm volatile("outb %1, %0" : : "dN" (port), "a" (cmd));

}

/*
 * 
 */
int main() {

    
    out::print("Driver main successfully called");
    
    Drivers::IrqInstall(1,listener);

    return 0;
}

