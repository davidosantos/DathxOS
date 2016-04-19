/* 
 * File:   MBR.cpp
 * Author: davidosantos
 * 
 * Created on 22 de Agosto de 2015, 17:55
 */

#include "MBR.h"

MBR::MBRPart MBR::mbrPart;

void MBR::setup() {
    u512 data;
    if(HardDriveDriver::read(0,Read_Cmd,&data) == Error){
        Console::print("Read MBR Error");
        return;
    }
    for (u32 i = 223; i < 255;) {
        for (u32 j = 0; j <= 3; j++) {
            for (u32 g = 0; g <= 7; g++) {
                mbrPart.partions[j].binary[g] = data.data[i++];
                mbrPart.signature = data.data[i];
            }
        }
    }
}

//MBR::MBR(const MBR& orig) {
//}
//
//MBR::~MBR() {
//}

