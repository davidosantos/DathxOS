/* 
 * File:   Files.h
 * Author: david
 *
 * Created on 5 de Setembro de 2015, 16:39
 */

#ifndef FILES_H
#define	FILES_H
#include "../../util/util.h"
#include "FAT32.h"


extern FAT *fat;

class File {
public:
    
    FAT::shortNameEntry fileInfo;

    returnCode open(const s8 *fileName);

    returnCode read(u32 offset, u32 size, u8 *to);

    void close();

    u32 offset;


    File();
    //    Files(const Files& orig);
    //    virtual ~Files();
private:
    u512 fileBuffer;
    bool openned;
    u32 fileSectorsCount; //total sectors of the file
    u32 fileSectorIndexInBuffer; //which of the sector of the file is in the buffer
    u32 fileCurrentSector; //sector in the file pointing to
    u32 fileFirstSector; 
};

#endif	/* FILES_H */

