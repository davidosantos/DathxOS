/* 
 * File:   Cmos.h
 * Author: davidosantos
 *
 * Created on July 5, 2015, 11:46 AM
 */

#ifndef CMOS_H
#define	CMOS_H

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

#include "drivers/HardwareIO.h"
#include "memory/Memory.h"
#include "../util/util.h"

class Cmos {
public:

    Cmos();
    //Cmos(const Cmos& orig);
    // virtual ~Cmos();
    
    Date date;
    Time time;

    /**
     * // Receives the signal from IRQ
     */
    static void IRQCMOSHandler();
    /**
     * // Returns a ref to a arrey of s8 Containing hour,min,secs in BCD
     * @return 
     */
    Tstorage &GetTime();
    /**
     * //Used to set time
     * @param hour
     * @param min
     * @param secs
     */
    static void SetTime(s8 hour, s8 min, s8 secs);

    /**
     * // Returns a ref to a arrey of s8 Containing hour,min,secs for alarm in BCD
     * @return 
     */
    Tstorage &GetAlarm();

    /**
     * //Used to set alarm
     * @param hour
     * @param min
     * @param secs
     */
    static void SetAlarm(s8 hour, s8 min, s8 secs);

    /**
     * // Returns a ref to a array of s8 Containing Day,month,year for alarm
     * @return 
     */
    static Dstorage &GetDate();

    /**
     * //Used to set date
     * @param day
     * @param month
     * @param year
     * @param dayofweek
     */
    static void SetDate(s8 day, s8 month, s8 year, s8 dayofweek);

    /**
     * // Used to indicate whether REGs of time and date can be read/written
     * @param Reg
     * @return 
     */
    static bool IsRegsReady(s8 Reg);

    /**
     * //must ready the status and the change the bit x1xx xxxx  Periodic Interrupt Enable of REG B
     */
    static void AnableRTCIntrs();

    /**
     * //must ready the status and the change the bit x1xx xxxx  Periodic Interrupt Enable of REG B
     */
    static void DisableRTCIntrs();

    /**
     * //xx1x xxxx  Alarm Interrupt Enable
     * // When set to 1, this bit enables the alarm static u32er-
     * //  rupt. The system initializes this bit to 0.
     */
    static void AnableAlarm();

    static void DisableAlarm();

    /**
     * // xxx1 xxxx  Update-Ended Interrupt Enabled
     * //       When set to 1, this bit enables the update-
     * //     ended static u32errupt. The system initializes
     * //   this bit to 0.
     * @return 
     */
    static bool WasItUpdateEnded();

    /**
     * //xx1x xxxx  Alarm Interrupt Flag REG C
    //When set to 1, this bit indicates that an alarm
    //static u32errupt occured.

     * @return 
     */
    static bool WasItaAlarmIntrr();
    /**
     * //1111 xxxx  First Diskette Drive Type
    //xxxx 1111  Second Diskette Drive Type

    //0000  No drive presend
    //0001  Double-sided diskette drive (48 tracks per inch, 360 Kb)
    //0010  High-capacity diskette drive (720 Kb)
    //0100  High-density diskette drive (1.44 Mb)
     * @return 
     */
    static bool IsDisketteInstalled();

    /**
     * // returns: 1 = Double-sided diskette drive (48 tracks per inch, 360 Kb)
    //   2 = High-capacity diskette drive (720 Kb)
    //   3 = High-density diskette drive (1.44 Mb
    //static static bool IsFirsDiskInstalled();	//	0 = Not Installed
    //static static bool IsSecDiskInstalled(); //011 - First Fixed Disk Drive Type Byte

    //This byte defined the type of the first fixed disk drive (drive C).
    //00h indicates that a fixed disk drive is not installed.

    //012 - Seccond Fixed Disk Drive Type Byte

    //This byte defined the type of the seccond fixed disk drive (drive D).
    //00h indicates that a fixed disk drive is not installed.


    //  The equipment byte defines the basic equipment in the system for
    // the power-on diagnostic tests.

    //   11xx xxxx  Number of diskette drives
    //               These bits indicate the mumber of diskette drives
    //               installed.
    //              00 = One Drive
    //               01 = Two Drives
    //               10 = Reserved
    //             11 = Reserved
     * @return 
     */
    static s8 WhichDisketteType();

    static u16 VideoOPMode(); //returns 1, 2 or 3
    //xx11 xxxx  Display Operating Mode
    //  These bits indicate the operating mode of the display
    //   attached to the video port, as shown in the following
    // figure.
    //   00 = Reserved
    //   01 = 40-Column Color Mode
    //   10 = 80-Column Color Mode
    //  11 = 80-Column Monochrome Mode

    /**
     *  // Returns the amount of memory in kb
    //017-018   Low and High Expansion Memory Bytes

    //These bytes define the amount of memory above the 1 Mb address space.
    //The value from these bytes represents the number of 1 Kb blocks of
    //expansion memory. For example 800h is equal to 2048Kb.
     * @return 
     */
    static u32 IsntalledMemory();

    static void MaskCmosInts();

private:
    HardwareIO *IOHardware;

};

#endif	/* CMOS_H */

