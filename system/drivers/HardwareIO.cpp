/* 
 * File:   HardwareIO.cpp
 * Author: davidosantos
 * 
 * Created on July 5, 2015, 12:21 AM
 */

#include "HardwareIO.h"

HardwareIO::HardwareIO() {
}

//HardwareIO::HardwareIO(const HardwareIO& orig) {
//}

//HardwareIO::~HardwareIO() {
//}

u8 HardwareIO::inb(u16 port) {

    u8 result;

    asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));

    return (result);
}

u16 HardwareIO::inw(u16 port) {

    unsigned short result;

    asm volatile("inw %1, %0" : "=a" (result) : "dN" (port));

    return (result);

}

void HardwareIO::outb(u16 port, u8 cmd) {

    asm volatile("outb %1, %0" : : "dN" (port), "a" (cmd));

}

void HardwareIO::outw(u16 port, u16 cmd) {

    asm volatile("outw %1, %0" : : "dN" (port), "a" (cmd));

}
