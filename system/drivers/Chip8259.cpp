/* 
 * File:   Chip8259.cpp
 * Author: davidosantos
 * 
 * Created on July 5, 2015, 12:29 AM
 */

#include "Chip8259.h"

Chip8259::Chip8259() {
}

//Chip8259::Chip8259(const Chip8259& orig) {
//}

//Chip8259::~Chip8259() {
//}

void Chip8259::Mask() {
    HardwareIO::outb(mastersecprt, 0xff);
    HardwareIO::outb(slavesecprt, 0xff);
}

void Chip8259::UnMask() {
    HardwareIO::outb(mastersecprt, 0x00);
    HardwareIO::outb(slavesecprt, 0x00);
}

void Chip8259::remap(u8 base) {

    HardwareIO::outb(mastersecprt, 0xff);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(slavesecprt, 0xff);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(masterfsprt, icw1);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(slavefsprt, icw1);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(mastersecprt, base);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(slavesecprt, (base + 8));
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(mastersecprt, icw3);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(slavesecprt, icw3s);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(mastersecprt, icw4);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(slavesecprt, icw4);
    asm("nop");
    asm("nop");
    asm("nop");
    //-----------------------
    HardwareIO::outb(masterfsprt, 0x0b);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(slavefsprt, 0x0b);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(mastersecprt, 0x00);
    asm("nop");
    asm("nop");
    asm("nop");
    HardwareIO::outb(slavesecprt, 0x00);

}

void Chip8259::AnableRTCIntrs() //must ready the status and the change the bit x1xx xxxx  Periodic Interrupt Enable of REG B
{


    unsigned char tmp;

    HardwareIO::outb(CMOSAddress, StatusRegB); //get status reg B



    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    tmp = (tmp | 0x40); // anable bit x1xx xxxx


    HardwareIO::outb(CMOSAddress, StatusRegB); //get status reg B



    HardwareIO::outb(CMOSData, tmp);



}

void Chip8259::interruptReceiver() {

     HardwareIO::outb(mastersecprt,PIC_EOI);
     HardwareIO::outb(slavesecprt,PIC_EOI);
    
}
