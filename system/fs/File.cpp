/* 
 * File:   Files.cpp
 * Author: david
 * 
 * Created on 5 de Setembro de 2015, 16:39
 */

#include "File.h"

File::File() {
    openned = false;
}

//Files::Files(const Files& orig) {
//}
//
//Files::~Files() {
//}

returnCode File::open(const s8 *fileName) {
    offset = 0;
    fileInfo = fat->find(fileName);
   
    if (fileInfo.Attrib != 0) {
        
        if (fat->readCluster(&fileInfo, &fileBuffer) == OK) {
            openned = true;
            fileSectorIndexInBuffer = 0;
            fileSectorsCount = (fileInfo.FileSize / fat->BPB.structure.BytesPerSector);
            if (fileInfo.FileSize > (fileSectorsCount * fat->BPB.structure.BytesPerSector)) {
                fileSectorsCount++;
            }

            fileCurrentSector = ((u32) fileInfo.FstClusHI << 16 | (u32) fileInfo.FstClusLO);
            fileFirstSector = fileCurrentSector;
            return OK;
        } else {
            return Error;
        }
    } else {
        return Error;
    }

    return Error;
}

returnCode File::read(u32 offset, u32 size, u8 *to) {
  
    if ((size + offset) > fileInfo.FileSize) {
        return Error;
    } else {
        u8 *cto = to;
        for (u32 i = offset; i < (offset + size); i++) {
            if ((i / fat->BPB.structure.BytesPerSector) != fileSectorIndexInBuffer) {
                fileSectorIndexInBuffer = (i / fat->BPB.structure.BytesPerSector);
                u32 nextSector = fat->readFAT(fileFirstSector);
                fileCurrentSector = nextSector;
                for (u32 j = 1; j < fileSectorIndexInBuffer; j++) {
                    nextSector = fat->readFAT(fileCurrentSector);
                    fileCurrentSector = nextSector;
                    if (nextSector == EoF || nextSector == EoF2) {
                        break;
                    } else {
                        fileCurrentSector = nextSector;
                    }
                }
                if (fat->readCluster(fileCurrentSector, &fileBuffer) == Error)
                    return Error;
            }
            *cto++ = fileBuffer.dataU8[i - (fileSectorIndexInBuffer * fat->BPB.structure.BytesPerSector)];
        }
        return OK;
    }
}