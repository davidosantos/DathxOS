/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on 19 de Junho de 2016, 08:16
 */

#include <DathxLib/io/out.h>
#include <DathxLib/Drivers.h>
#include <system/drivers/HardwareIO.h>
#include <system/Providers/Messaging.h>

void IrqListener() {
    
    static Messaging::message newChar;
    newChar.keycode = HardwareIO::inb(0x60);

    out::print(41,0,"Test of System Calls by Driver %h", newChar.keycode);
   
    
    HardwareIO::outb(0xA0, 0x20);
    HardwareIO::outb(0x20, 0x20);
    
    Messaging::broadcastMessage(&newChar);

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
    
    Drivers::IrqInstall(2);

    return 0;
}


