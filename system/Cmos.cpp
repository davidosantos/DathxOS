/* 
 * File:   Cmos.cpp
 * Author: davidosantos
 * 
 * Created on July 5, 2015, 11:46 AM
 */

#include "Cmos.h"

Cmos::Cmos() {
    IOHardware = new HardwareIO();
}

//Cmos::Cmos(const Cmos& orig) {
//}

//Cmos::~Cmos() {
//}

void Cmos::IRQCMOSHandler() {

}

Tstorage& Cmos::GetTime() //remember this Tstorage&
{

    for (;;) {

        if (IsRegsReady(StatusRegA)) {

            //cli(); //clear ints

            HardwareIO::outb(CMOSAddress, RegHour);

            nop();
            nop();
            nop();

            time.Hour.ch = HardwareIO::inb(CMOSData);

            nop();
            nop();
            nop();

            HardwareIO::outb(CMOSAddress, RegMin);

            nop();
            nop();
            nop();

            time.Min.ch = HardwareIO::inb(CMOSData);

            nop();
            nop();
            nop();

            HardwareIO::outb(CMOSAddress, RegSec);

            nop();
            nop();
            nop();

            time.Sec.ch = HardwareIO::inb(CMOSData);

            //sti(); // ints back on


        }
    }
    return time;
}

Dstorage& Cmos::GetDate() {
    // Returns a ref to a arrey of unsigned char Containing Day,month,year and day of week in hex

    static Date date;
    for (;;) {

        if (IsRegsReady(StatusRegA)) {

            //cli(); //clear ints

            HardwareIO::outb(CMOSAddress, RegDay);

            nop();
            nop();
            nop();

            date.Day.ch = HardwareIO::inb(CMOSData);

            nop();
            nop();
            nop();

            HardwareIO::outb(CMOSAddress, RegMonth);

            nop();
            nop();
            nop();

            date.Month.ch = HardwareIO::inb(CMOSData);

            nop();
            nop();
            nop();

            HardwareIO::outb(CMOSAddress, RegYear);

            nop();
            nop();
            nop();

            date.Year.ch = HardwareIO::inb(CMOSData);

            nop();
            nop();
            nop();

            HardwareIO::outb(CMOSAddress, RegDayWeek);

            nop();
            nop();
            nop();

            date.DayOfWeek.ch = HardwareIO::inb(CMOSData);

            //sti(); // ints back on

            break; // break the loop
        }
    }
    return date;
}

bool Cmos::IsRegsReady(s8 Reg) {

    unsigned char localtmp;

    HardwareIO::outb(CMOSAddress, Reg);

    nop();
    nop();
    nop();

    localtmp = HardwareIO::inb(CMOSData);

    if (localtmp & 0x80) {

        return true;

    } else {

        return false;
    }
}

void Cmos::AnableRTCIntrs() //must ready the status and the change the bit x1xx xxxx  Periodic Interrupt Enable of REG B
{

    //cli(); // Clears ints

    unsigned char tmp;

    HardwareIO::outb(CMOSAddress, StatusRegB); //get status reg B

    nop();
    nop();
    nop();

    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    tmp = (tmp | 0x40); // anable bit x1xx xxxx
    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, StatusRegB); //get status reg B

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSData, tmp);

    ////sti();

}

void Cmos::DisableRTCIntrs() //must ready the status and the change the bit x1xx xxxx  Periodic Interrupt Enable of REG B
{

    //cli(); // Clears ints

    unsigned char tmp;

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, StatusRegB); //get status reg B

    nop();
    nop();
    nop();

    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    tmp = (tmp ^ 0x40); // disable bit x1xx xxxx
    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, StatusRegB); //get status reg B

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSData, tmp);

    ////sti();

}

bool Cmos::WasItUpdateEnded() // xxx1 xxxx  Update-Ended Interrupt Enabled
{
    //When set to 1, this bit enables the update-
    //ended interrupt. The system initializes
    //this bit to 0.


    //cli(); // Clears ints

    unsigned char tmp;

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, StatusRegC); //get status reg C

    nop();
    nop();
    nop();

    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    //sti(); // ints bakc on

    if (tmp & 0x10) // is it xxx1 xxxx
    {

        return true;

    } else {

        return false;

    }
}

bool Cmos::WasItaAlarmIntrr() //xx1x xxxx  Alarm Interrupt Flag REG C
{
    //When set to 1, this bit indicates that an alarm
    //interrupt occured.
    //cli(); // Clears ints

    unsigned char tmp;

    HardwareIO::outb(CMOSAddress, StatusRegC); //get status reg C

    nop();
    nop();
    nop();

    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    //sti(); // ints bakc on

    if (tmp & 0x20) {

        return true;

    } else {

        return false;

    }



}

bool Cmos::IsDisketteInstalled() //1111 xxxx  First Diskette Drive Type
{
    //xxxx 1111  Second Diskette Drive Type

    //0000  No drive presend
    //0001  Double-sided diskette drive (48 tracks per inch, 360 Kb)
    //0010  High-capacity diskette drive (720 Kb)
    //0100  High-density diskette drive (1.44 Mb)
    //cli(); // Clears ints

    unsigned char tmp;

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, EquipmentByteReg); //get status reg DisketteDriveTypeReg

    nop();
    nop();
    nop();

    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    //sti(); // ints bakc on

    if (tmp & 0x01) //xxxx xxx1
    {

        return true;

    } else {

        return false;

    }
}

char Cmos::WhichDisketteType() // returns: 1 = Double-sided diskette drive (48 tracks per inch, 360 Kb)
{
    //   2 = High-capacity diskette drive (720 Kb)
    //   3 = High-density diskette drive (1.44 Mb
    //   0 = Not Installed
    //cli(); // Clears ints

    unsigned char tmp;

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, DisketteDriveTypeReg); //get status reg DisketteDriveTypeReg

    nop();
    nop();
    nop();

    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    //sti(); // ints bakc on

    if (tmp & 0x10) //xxxx xxx1
    {

        return 1;

    } else if (tmp & 0x20) // xxxx xx1x
    {

        return 2;

    } else if (tmp & 0x40) //xxxx x1xx
    {

        return 3;

    } else {

        return 0;

    }
}

u16 Cmos::VideoOPMode() //returns 1, 2 or 3
{
    //xx11 xxxx  Display Operating Mode
    //  These bits indicate the operating mode of the display
    //   attached to the video port, as shown in the following
    // figure.
    //   00 = Reserved
    //   01 = 40-Column Color Mode
    //   10 = 80-Column Color Mode
    //  11 = 80-Column Monochrome Mode


    //cli(); // Clears ints

    unsigned char tmp;

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, EquipmentByteReg); //get status reg DisketteDriveTypeReg

    nop();
    nop();
    nop();

    tmp = HardwareIO::inb(CMOSData); //get data from status reg be

    //sti(); // ints bakc on

    tmp = (tmp ^ 0xcf); //set all bits to zero but xx11 xxxx (xor)

    if (tmp == 0x10) //xx01 xxxx
    {

        return 1;

    } else if (tmp == 0x20) // xx10 xxxx
    {

        return 2;

    } else if (tmp == 0x30) //xx11 xxxx
    {

        return 3;

    } else {

        return 0; // reserved

    }
}

u32 Cmos::IsntalledMemory() // Returns the amount of memory in kb
{
    //017-018   Low and High Expansion Memory Bytes

    //These bytes define the amount of memory above the 1 Mb address space.
    //The value from these bytes represents the number of 1 Kb blocks of
    //expansion memory. For example 800h is equal to 2048Kb.
    int MBs = 0;

    //cli(); // Clears ints

    HardwareIO::outb(CMOSAddress, MemoryBytesReg2); //get MemoryBytesReg2

    nop();
    nop();
    nop();

    MBs = HardwareIO::inb(CMOSData); //get data
    MBs = (MBs << 8);
    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, MemoryBytesReg); //get MemoryBytesReg

    nop();
    nop();
    nop();

    MBs = ((MBs | HardwareIO::inb(CMOSData)) & 0xFF); //get data
    //sti(); // ints bakc on


    return (MBs);

}

void Cmos::MaskCmosInts() {

    //cli();

    HardwareIO::outb(CMOSAddress, StatusRegB);

    nop();
    nop();
    nop();

    unsigned char tmp = HardwareIO::inb(CMOSData);

    tmp = (tmp | 0x80);

    HardwareIO::outb(CMOSAddress, StatusRegB);

    nop();
    nop();
    nop();

    HardwareIO::outb(CMOSAddress, tmp);

}

/*
00E - Diagno//stics Status Byte

                    1xxx xxxx  Real-Time Clock Chip Power
                                 When set to 1, this bit indicates the real-
                                 time clock chip lost power.
                    x1xx xxxx  Configuration Record and Chechsum Status
                                 When this bit is set to 1, the checksum is
                                 incorrect.
                    xx1x xxxx  Incorrect Configuration
                                 This is a check, at power-on time, of the
                                 Equipment byte. When set to 1, the confi-
                                 guration information is incorrect. Power-on
                                 checks require that at least on diskette
                                 drive be installed (bit 0 of the equipment
                                 byte - 014 - is set to 1).
                    xxx1 xxxx  Memory Size Miscompare
                                 When set to 1, the power-on check determined
                                 that the memory size is not the same as in
                                 the configuration record.
                    xxxx 1xxx  Fixed Disk Controller
                                 When set to 1, this bit indicates that the
                                 controller or drive C failed initialization,
                                 which prevents the system from attempting
                                 a power-on reset.
                    xxxx x1xx  Time Status Indicator
                                 When set to 0, this bit indicates the time
                                 is valid. When set to 1, this bit indicates
                                 the time is invalid.
                    xxxx xx1x  Adapter Configuration Miscompare
                                 This bit indicates if the installed adapters
                                 match the configuration information. When
                                 set to 1, the adapter do not match the
                                 configuration information.
                    xxxx xxx1  Adapter ID Time-Out
                                 When set to 1, this bit indicates a time-out
                                 while an adapter ID was being read.
 */

