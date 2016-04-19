/* 
 * File:   MBR.h
 * Author: davidosantos
 *
 * Created on 22 de Agosto de 2015, 17:55
 */

#ifndef MBR_H
#define	MBR_H
#include "../../util/util.h"
#include "../monitor/Console.h"
#include "../drivers/HardDriveDriver.h"

class MBR {
public:
    MBR();
    
    static void setup();
    //    MBR(const MBR& orig);
    //    virtual ~MBR();
public:

    typedef union _PartionEntry {
        u16 binary[8];
        struct {
            u8 Boot;
            u8 head;

            struct {
                u16 Cylinder : 10;
                u8 sector : 6;
            };
            u8 type;
            u8 HeadEnd;

            struct {
                u16 CylinderEnd : 10;
                u8 sectorEnd : 6;
            };
            u32 startingAt;
            u32 PartTotalSize;
        }entries;
        
    } PartionEntry;

    typedef struct _MBRPart {
        PartionEntry partions[4];
        u16 signature;

    } MBRPart;

    static MBRPart mbrPart;
};

#endif	/* MBR_H */

