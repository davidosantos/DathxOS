/* 
 * File:   HardwareIO.h
 * Author: davidosantos
 *
 * Created on July 5, 2015, 12:21 AM
 */

#ifndef HARDWAREIO_H
#define	HARDWAREIO_H

#include "../../util/util.h"

class HardwareIO {
public:
    HardwareIO();
    HardwareIO(const HardwareIO& orig);
    //virtual ~HardwareIO();
    
    static u8 inb(u16 port);
    static u16 inw(u16 port);
    static void outb(u16 port,u8 cmd);
    static void outw(u16 port,u16 cmd);
    
private:

};

#endif	/* HARDWAREIO_H */

