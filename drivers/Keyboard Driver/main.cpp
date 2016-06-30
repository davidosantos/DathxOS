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
#include <system/Providers/Keyboard.h>

void IrqListener() {

    Messaging::MessageAddrs newChar;
    newChar.keycode = 0;
    newChar.keycode = HardwareIO::inb(0x60);
    newChar.type = Type_unread;

    if (newChar.upKey == 1) {
        if (newChar.keycode == 0x9c) {
            newChar.keychar = 0x9c;

            Messaging::broadcastMessage(&newChar);
        }
    } else {
        newChar.keychar = keys_ptbr[newChar.keycode];
        Messaging::broadcastMessage(&newChar);
    }



    HardwareIO::outb(0xA0, 0x20);
    HardwareIO::outb(0x20, 0x20);
    out::print(45, 0, "newChar.upKey %i", newChar.upKey);
    out::print(41, 0, "newChar.keycode %i", newChar.keycode);
    out::print(43, 0, "newChar.keychar %i", newChar.keychar);


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


