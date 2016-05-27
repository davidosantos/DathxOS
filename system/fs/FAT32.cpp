/* 
 * File:   FAT32.cpp
 * Author: davidosantos
 * http://www.maverick-os.dk/FileSystemFormats/FileSystemIdentifiers.html
 * Created on 22 de Agosto de 2015, 17:53
 */

#include "FAT32.h"

FAT::_FSInfoSector FAT::FSInfoSector;
FAT::FAT32_Structure FAT::BPB;
FAT::FAT12_16_Structure FAT::FAT12_16;
FAT::_FATEntry FAT::FATEntry;
FAT::_Cluster FAT::DirEntry;
u32 FAT::RootDirSectors;
u32 FAT::DataRegionStart;
u32 FAT::RootDirSectorsCount;
u32 FAT::DataSec;
u32 FAT::CountofClusters;
u32 FAT::FATTAbleStartSector;

void FAT::setup() {




    if (HardDriveDriver::read(MBR::mbrPart.partions[0].entries.startingAt, Read_Cmd, &BPB.data) == Error) {
        Console::print("Error Reading MBR");
        return;
    }


    for (u32 i = 0; i < 256; i++) {
        FAT12_16.data[i] = BPB.data.data[i]; //same at the beginning
    }

    u32 FATSz = 0;
    u32 TotSec = 0;

    FATTAbleStartSector = MBR::mbrPart.partions[0].entries.startingAt + BPB.structure.RsvdSecCnt;

    if (BPB.structure.BytesPerSector != 0) { // void divide error

        RootDirSectorsCount = ((BPB.structure.RootEntCnt * 32) + (BPB.structure.BytesPerSector - 1)) / BPB.structure.BytesPerSector;

        if (BPB.structure.FATSz16 != 0) {
            FATSz = BPB.structure.FATSz16;
            TotSec = BPB.structure.TotalSect16;

        } else {
            FATSz = BPB.structure.ExtSectorFAT32.FAT_Size;
            TotSec = BPB.structure.TotalSect32;

        }

        DataSec = TotSec - (BPB.structure.RsvdSecCnt + (BPB.structure.NumFATs * FATSz) + RootDirSectorsCount);
        CountofClusters = DataSec / BPB.structure.SectPerCluster;
    }

    if (CountofClusters < 4085) {
        // * Volume is FAT12 * / 
        Console::print("FAT12 is not supported");
        return;
    } else if (CountofClusters < 65525) {
        // * Volume is FAT16 * / 
        Console::print("FAT16 is not supported");
        return;
    } else {
        // * Volume is FAT32 !!! !!! * /
    }

    //Read info
    if (HardDriveDriver::read(MBR::mbrPart.partions[0].entries.startingAt
            + BPB.structure.ExtSectorFAT32.FSInfo, Read_Cmd, &FSInfoSector.data) == OK) {
        //        for (u32 i = 0; i < 256; i++) {
        //            FSInfoSector.data[i] = data.data[i];
        //        }
    } else {
        Console::print("Read info sector Error");
    }


    /*
    FAT Data Structure
    The next data structure that is important is the FAT itself. What this data structure does is define a
    singly linked list of the “extents” (clusters) of a file. Note at this point that a FAT directory or file
    container is nothing but a regular file that has a special attribute indicating it is a directory. The only
    other special thing about a directory is that the data or contents of the “file” is a series of 32=byte FAT
    directory entries (see discussion below). In all other respects, a directory is just like a file. The FAT
    maps the data region of the volume by cluster number. The first data cluster is cluster 2.
    The first sector of cluster 2 (the data region of the disk) is computed using the BPB fields for the
    volume as follows. First, we determine the count of sectors occupied by the root directory:
     * 
     * RootDirSectors = ((BPB_RootEntCnt * 32) + (BPB_BytsPerSec – 1)) / BPB_BytsPerSec;
     */

    RootDirSectors = ((BPB.structure.RootEntCnt * 32) + (BPB.structure.BytesPerSector - 1)) /
            BPB.structure.BytesPerSector;

    //RootDirSector = ((MBR::mbrPart.partions[0].entries.startingAt + FAT32.structure.RsvdSecCnt) + (FAT32.structure.NumFATs * FATSz));

    /*
     * The start of the data region, the first sector of cluster 2, is computed as follows:
     * BPB_ResvdSecCnt + (BPB_NumFATs * FATSz) + RootDirSectors;
     */

    DataRegionStart = (MBR::mbrPart.partions[0].entries.startingAt +
            BPB.structure.RsvdSecCnt)+
            ((BPB.structure.NumFATs * FATSz) + RootDirSectors);

    if (BPB.structure.SectPerCluster > 1) {
        Console::print("FS Error: Cluster greater than 512 bytes is not yet supported!");
    }


}

//FAT32::FAT32(const FAT32& orig) {
//}
//
//FAT32::~FAT32() {
//}

/**
 * Unlike other directories, the root directory itself on any FAT type does not have any date or time
    stamps, does not have a file name (other than the implied file name “\”), and does not contain “.” and
    “..” files as the first two directory entries in the directory. The only other special aspect of the root
    directory is that it is the only directory on the FAT volume for which it is valid to have a file that has
    only the ATTR_VOLUME_ID attribute bit set
 * @param dirFile
 * @param EntryNumber
 * @return 
 */
FAT::shortNameEntry FAT::find(const s8 *dirFileName) {
    //u32 nextCluster = BPB.structure.ExtSectorFAT32.RootCluster;
    u32 nextCluster = RootDirSectors;
    // u32 readNextEntry = 0;
    bool isFinished = false;
    bool shortNameFound = false;
    bool longNameFound = false;
    u16 nameIndex = 0;
    _Cluster cluster;
    s8 string[255]; //Max file or dir name

    shortNameEntry shortNameEnt;
    shortNameEntry longNameEnt;
    HardDriveDriver::read((DataRegionStart + nextCluster), Read_Cmd, &cluster.data);

    for (int i = 0;; i++) {
        if (dirFileName[nameIndex + i] != slash) {
            string[i] = dirFileName[nameIndex + i];
            if (string[i] == 0) {

                break;
            }
        } else {
            string[i] = 0;
            nameIndex += i + 1; //skip the slash
            break;
        }
    }

    do {

        if (shortNameFound == true || longNameFound == true) {
            for (int i = 0;; i++) {
                if (dirFileName[nameIndex + i] != slash) {
                    string[i] = dirFileName[nameIndex + i];
                    if (string[i] == 0) {

                        break;
                    }
                } else {
                    string[i] = 0;
                    nameIndex += i + 1; //skip the slash
                    break;
                }
            }
        }



        shortNameEnt = isThereShortNameEntry(&cluster, string);

        if (shortNameEnt.Attrib != 0) {

            if (shortNameEnt.ATTR_DIRECTORY == isON) {
                if (HardDriveDriver::read(getSector(shortNameEnt.getClusterNumber()), Read_Cmd, &cluster.data) == Error) {
                    Console::print("Error Reading hard drive.");
                }
                shortNameEnt.Attrib = 0;
                shortNameFound = true;
            } else if (shortNameEnt.ATTR_ARCHIVE == isON) {
                return shortNameEnt;
            }
        } else {
            shortNameFound = false;
        }


        if (!shortNameFound) {
            longNameEnt = isThereLongNameEntry(&cluster, string);
            if (longNameEnt.Attrib != 0) {
                if (longNameEnt.ATTR_DIRECTORY == isON) {
                    HardDriveDriver::read(getSector(longNameEnt.getClusterNumber()), Read_Cmd, &cluster.data);
                    longNameFound = true;
                } else if (longNameEnt.ATTR_ARCHIVE == isON) {
                    return longNameEnt;
                }
            } else {
                longNameFound = false;
            }
        }

        if (shortNameFound == false && longNameFound == false) {
            if (nextCluster < BPB.structure.ExtSectorFAT32.RootCluster) {
                nextCluster++;
                //Console::print("nextCluster++;: %h", nextCluster);
            } else {
                nextCluster = readFAT(nextCluster);
                //Console::print("nextCluster readFAT;: %h", nextCluster);
            }

            if (nextCluster == EoF || nextCluster == EoF2) {
                //  Console::print("teste++;: %i", teste);
                //Console::print("nextCluster: %h", nextCluster);
                isFinished = true;
            } else {
                if (getSector(nextCluster) > 0x4ec65)
                    //  Console::print("getSector(nextCluster):::: %h", getSector(nextCluster));
                    HardDriveDriver::read(getSector(nextCluster), Read_Cmd, &cluster.data);
            }
        }

    } while (isFinished == false);

    shortNameEnt.Attrib = 0;
    return shortNameEnt;

}

FAT::shortNameEntry FAT::isThereShortNameEntry(_Cluster *data, const s8 *name) {
    u16 charIndexShortNames = 0;
    bool foundShortName = false;
    shortNameEntry shortNameEnt;

    for (u32 entryIndex = 0; entryIndex < (BPB.structure.BytesPerSector / 32 * BPB.structure.SectPerCluster); entryIndex++) {
        charIndexShortNames =0;
        if (data->shortName[entryIndex].Entry != IsDeleted &&
                data->shortName[entryIndex].Entry != IsFree &&
                data->shortName[entryIndex].Attrib != IsLongName) {

            for (int j = 0; j < 8; j++) {

                if (data->shortName[entryIndex].shortName[j] != space) {
                    //to lower case
                    if ((data->shortName[entryIndex].shortName[j] ^ 0x20) != name[charIndexShortNames]) {
                        foundShortName = false;
                        break;
                    } else {
                        foundShortName = true;
                        charIndexShortNames++;
                    }

                }
            }
            
            if(name[charIndexShortNames] == dot){
                charIndexShortNames++; //skip the dot
            }
           
            for (int j = 0; j < 3; j++) {

                if (data->shortName[entryIndex].extention[j] != space) {
                    //to lower case
                    if ((data->shortName[entryIndex].extention[j] ^ 0x20) != name[charIndexShortNames]) {
                        foundShortName = false;
                    
                        break;
                    } else {
                        foundShortName = true;
                        charIndexShortNames++;
                    }

                }
            }

            if (foundShortName) {
                
                return data->shortName[entryIndex];
            }

        }
    }
    shortNameEnt.Attrib = 0;
    return shortNameEnt;
}

FAT::shortNameEntry FAT::isThereLongNameEntry(_Cluster *data, const s8 *name) {

    longNameEntry longNameEnt;
    shortNameEntry shortNameEnt;



    for (u32 entryIndex = 0; entryIndex < (BPB.structure.BytesPerSector / 32 * BPB.structure.SectPerCluster); entryIndex++) {
        if (data->shortName[entryIndex].Entry != IsDeleted &&
                data->shortName[entryIndex].Entry != IsFree &&
                data->shortName[entryIndex].Attrib != IsLongName) {

            u8 checkSum = getCheckSum((u8*) data->shortName[entryIndex].shortName);
            u8 sequence = 1;
            u16 charIndexLongNames = 0;

            bool isEntryFindFinished = false;
            bool foundLongName = false;

            do {
                longNameEnt = findNextLongNameEntry(data, checkSum, sequence++);
                if (longNameEnt.Attrib != 0) {
                    for (int j = 0; j < 5; j++) {
                        if (name[charIndexLongNames++] != longNameEnt.chars1[j].character) {
                            isEntryFindFinished = true;
                            break;
                        }
                        if (name[charIndexLongNames] == 0 && longNameEnt.lastLongFlag == isON) {
                            isEntryFindFinished = true;
                            foundLongName = true;
                            break;
                        }

                    }

                    if (!isEntryFindFinished) {
                        for (int j = 0; j < 6; j++) {
                            if (name[charIndexLongNames++] != longNameEnt.chars2[j].character) {
                                isEntryFindFinished = true;

                                break;
                            }
                            if ((name[charIndexLongNames] == 0)
                                    && longNameEnt.lastLongFlag == isON) {
                                isEntryFindFinished = true;
                                foundLongName = true;
                                break;
                            }
                        }
                    }

                    if (!isEntryFindFinished) {
                        for (int j = 0; j < 2; j++) {
                            if (name[charIndexLongNames++] != longNameEnt.chars3[j].character) {
                                isEntryFindFinished = true;

                                break;
                            }
                            if (name[charIndexLongNames] && longNameEnt.lastLongFlag == isON) {

                                isEntryFindFinished = true;
                                foundLongName = true;
                                break;
                            }
                        }
                    }

                    if (foundLongName) {
                        if (name[charIndexLongNames] == 0) {

                            return data->shortName[entryIndex];
                        }
                    }

                } else {
                    isEntryFindFinished = true;

                }
            } while (isEntryFindFinished == false);

        }
    }

    shortNameEnt.Attrib = 0;
    return shortNameEnt;
}

FAT::longNameEntry FAT::findNextLongNameEntry(_Cluster *data, u8 checksum, u8 sequece) {
    _Cluster entries;

    for (u32 i = 0; i < (BPB.structure.BytesPerSector / 32 * BPB.structure.SectPerCluster); i++) {
        if (data->longName[i].CheckSum == checksum &&
                data->longName[i].Sequence == sequece) {
            if (checksum == 51) {
                Console::print("242::: %i", data->longName[i].Sequence);
            }
            return data->longName[i];
        }
    }

    entries.longName[0].Attrib = 0;
    return entries.longName[0];
}

FAT::shortNameEntry FAT::findNextShortNameEntry(_Cluster *data) {

}

u32 FAT::getSector(u32 Cluster) {
    //FirstSectorofCluster = ((N – 2) * BPB_SecPerClus) + FirstDataSector;
    return ((Cluster - 2) * BPB.structure.SectPerCluster + DataRegionStart);
}

u8 FAT::getCheckSum(u8 *pFcbName) {

    int i;
    u8 sum = 0;

    for (i = 0; i < 11; i++) {

        sum = (sum >> 1) + ((sum & 1) << 7); /* rotate */
        sum += pFcbName[i]; /* add next name byte */
    }
    return sum;

}

u32 FAT::readFAT(u32 Cluster) {
    //not treating fat16


    u32 ThisFATSecNum = 0;
    u32 ThisFATEntOffset = 0;



    ThisFATSecNum = ((Cluster * 4) / BPB.structure.BytesPerSector);
    ThisFATEntOffset = ((Cluster * 4) % BPB.structure.BytesPerSector) / 4;

    if (HardDriveDriver::read((FATTAbleStartSector + ThisFATSecNum), Read_Cmd, &FATEntry.data) == Error) {
        Console::print("Error reading FAT table %h ", Cluster);
    }
    return FATEntry.structure[ThisFATEntOffset].value;
}

returnCode FAT::readCluster(FAT::shortNameEntry *file, u512 *to) {

    if (file->Attrib != 0) {

        if (HardDriveDriver::read(getSector(file->getClusterNumber()), Read_Cmd, to) == Error) {
            return Error;
        }
        return OK;
    } else {

        return Error;
    }
    return Error;
}

returnCode FAT::readCluster(u32 clusterNumber, u512 *to) {

    if (HardDriveDriver::read(getSector(clusterNumber), Read_Cmd, to) == OK) {
        return OK;
        //FatEntry = readFATEntry(firstSectorCluster);
    } else {
        return Error;
    }
    return Error;
}