/* 
 * File:   Chip8259.h
 * Author: davidosantos
 *
 * Created on July 5, 2015, 12:29 AM
 */

#ifndef CHIP8259_H
#define	CHIP8259_H

#define masterfsprt				0x20	//20h for the master controller
#define mastersecprt			0x21	//21h for the master mask controller
#define slavefsprt				0xa0	//a0h for the slave controller
#define slavesecprt				0xa1	//a1h for the slave mask controller
#define icw1					0x11	//* start init sequence */
//#define icw2					32	    //* vector base */
//#define icw2s				    40	    //* vector base */
#define icw3					0x04	//;* edge tiggered, cascade (slave) on irq2
#define icw3s					0x02	//;/* edge triggered, cascade (slave) on irq2
#define icw4                    0x8f	//;pc mode	/* select 8086 mode */

#define CMOSAddress 0x70
#define	CMOSData 0x71
#define StatusRegA 0x0A
#define StatusRegB 0x0B
#define StatusRegC 0x0C
#define StatusRegD 0x0D
#define RegSec 0x00
#define RegMin 0x02
#define RegHour 0x04
#define RegDay 0x07
#define RegDayWeek 0x06
#define RegMonth 0x08
#define RegYear 0x09
#define RegAlrSec 0x01
#define RegAlrMin 0x03
#define RegAlrHour 0x05
#define DisketteDriveTypeReg 0x10
#define FirstFixedDiskDriveReg 0x11
#define SeconFixedDiskDriveReg 0x12
#define EquipmentByteReg 0x14
#define MemoryBytesReg 0x17
#define MemoryBytesReg2 0x18

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define PIC_EOI		0x20		/* End-of-interrupt command code */

#include "HardwareIO.h"
#include "../../util/util.h"

class Chip8259 {
public:
    Chip8259();
    // Chip8259(const Chip8259& orig);
    //  virtual ~Chip8259();

    static void Mask();
    static void UnMask();
    static void remap(u8 base);
    static void AnableRTCIntrs();
    
   static void interruptReceiver();
private:

};

#endif	/* CHIP8259_H */

