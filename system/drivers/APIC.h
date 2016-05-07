/* 
 * File:   APIC.h
 * Author: david
 *
 * Created on May 7, 2016, 4:46 PM
 */

#ifndef APIC_H
#define	APIC_H

#include "../../util/util.h"


class APIC {
public:
    
    struct Registers {
//        u32[4] : 256,
//        APICID : 128,
//        APICVersion : 128,
//        : 512,
//        TaskPriority : 128,
//        ArbitrationPriority : 128,
//        ProcessorPriority : 128,
//        EndOfInterrupt : 128,
//        RemoteRead : 128,
//        LogicalDestination : 128;
    }__attribute__((packed));
    
    APIC();
//    APIC(const APIC& orig);
//    virtual ~APIC();
private:

};

#endif	/* APIC_H */

