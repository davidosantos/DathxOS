/* 
 * File:   FAT32.cpp
 * Author: davidosantos
 * http://www.maverick-os.dk/FileSystemFormats/FileSystemIdentifiers.html
 * Created on 22 de Agosto de 2015, 17:53
 */

#include "FAT32.h"

FAT::_FSInfoSector FAT::FSInfoSector;
FAT::FAT32_Structure FAT::FAT32;
FAT::FAT12_16_Structure FAT::FAT12_16;
FAT::_FATEntry FAT::FATEntry;
FAT::_DirEntry FAT::DirEntry;
u32 FAT::RootDirSectors;
u32 FAT::DataRegionStart;
u32 FAT::RootDirSectorsCount;
u32 FAT::DataSec;
u32 FAT::CountofClusters;
u32 FAT::FATTAbleStartSector;

void FAT::setup() {




    if (HardDriveDriver::read(MBR::mbrPart.partions[0].entries.startingAt, Read_Cmd, &FAT32.data) == Error) {
        Console::print("Error Reading MBR");
        return;
    }


    for (u32 i = 0; i < 256; i++) {
        FAT12_16.data[i] = FAT32.data.data[i]; //same at the beginning
    }

    u32 FATSz = 0;
    u32 TotSec = 0;

    FATTAbleStartSector = MBR::mbrPart.partions[0].entries.startingAt + FAT32.structure.RsvdSecCnt;

    if (FAT32.structure.BytesPerSector != 0) { // void divide error

        RootDirSectorsCount = ((FAT32.structure.RootEntCnt * 32) + (FAT32.structure.BytesPerSector - 1)) / FAT32.structure.BytesPerSector;

        if (FAT32.structure.FATSz16 != 0) {
            FATSz = FAT32.structure.FATSz16;
            TotSec = FAT32.structure.TotalSect16;

        } else {
            FATSz = FAT32.structure.ExtSectorFAT32.FAT_Size;
            TotSec = FAT32.structure.TotalSect32;

        }

        DataSec = TotSec - (FAT32.structure.RsvdSecCnt + (FAT32.structure.NumFATs * FATSz) + RootDirSectorsCount);
        CountofClusters = DataSec / FAT32.structure.SectPerCluster;
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
            + FAT32.structure.ExtSectorFAT32.FSInfo, Read_Cmd, &FSInfoSector.data) == OK) {
        //        for (u32 i = 0; i < 256; i++) {
        //            FSInfoSector.data[i] = data.data[i];
        //        }
    } else {
        Console::print("Read info sector Error");
    }
    //    f(BPB_FATSz16 != 0)
    //FATSz = BPB_FATSz16;
    //Else
    //FATSz = BPB_FATSz32;
    //If(FATType == FAT16)
    //FATOffset = N * 2;
    //Else if (FATType == FAT32)
    //FATOffset = N * 4;
    //ThisFATSecNum = BPB_ResvdSecCnt + (FATOffset / BPB_BytsPerSec);
    //ThisFATEntOffset = REM(FATOffset / BPB_BytsPerSec);
    //    u32 ThisFATSecNum = 0;
    //    u32 ThisFATEntOffset = 0;
    //
    //    if (FAT32.structure.BytesPerSector != 0) {
    //        u32 FAtOffset = (FAT32.structure.ExtSectorFAT32.RootCluster * 4);
    //        ThisFATSecNum = (MBR::mbrPart.partions[0].entries.startingAt + FAT32.structure.RsvdSecCnt) + (FAtOffset / FAT32.structure.BytesPerSector);
    //        ThisFATEntOffset = (FAtOffset % FAT32.structure.BytesPerSector);
    //
    //        HardDriveDriver::read(ThisFATSecNum, Read_Cmd, &FATEntry.data);
    //
    //    }

    RootDirSectors = ((MBR::mbrPart.partions[0].entries.startingAt + FAT32.structure.RsvdSecCnt) + (FAT32.structure.NumFATs * FATSz));

    DataRegionStart = RootDirSectors - 2;

    //    u32 rootSectors = RootDirSectors;
    //    u32 readCount = 0;
    //    u32 firstSectorCluster;
    //    do {
    //        HardDriveDriver::read(rootSectors++, Read_Cmd, &DirEntry.data);
    //
    //
    //
    //        for (u32 i = 0; i <= 16; i++) {
    //            if (DirEntry.structure[i].Attrib == IsLongName &&
    //                    DirEntry.structure[i].Entry != IsDeleted &&
    //                    DirEntry.structure[i].Entry != IsFree &&
    //                    DirEntry.structure[i].Entry == 0x01) {
    //                //Console::print("Long name: %s", DirEntry.structureLongNames[i].getName(i, DirEntry.structureLongNames));
    //
    //            }
    //            if (DirEntry.structure[i].Attrib != IsLongName &&
    //                    DirEntry.structure[i].Attrib != 0 &&
    //                    DirEntry.structure[i].Entry != IsDeleted &&
    //                    DirEntry.structure[i].Entry != IsFree) {
    //
    //                firstSectorCluster = (u32) (DirEntry.structure[i].FstClusHI << 16 | DirEntry.structure[i].FstClusLO);
    //                // Console::print("%ctkFATS:  %s", DirEntry.structure[i].getName());
    //                // Console::print("FAT:  %h", readFATEntry(firstSectorCluster));
    //            }
    //        }
    //
    //
    //    } while ((readCount++) <= 14);


}

//FAT32::FAT32(const FAT32& orig) {
//}
//
//FAT32::~FAT32() {
//}

returnCode FAT::find(const s8 *dirFile, u16 *EntryNumber) {
    u32 rootSectors = RootDirSectors;
    u32 readNextSector = 0;

    do {
        HardDriveDriver::read(rootSectors++, Read_Cmd, &DirEntry.data);

        for (u32 i = 0; i < 16; i++) {

            readNextSector = DirEntry.structure[i].Entry; //end of root dir
            if (readNextSector == 0)
                return Error;

            if (DirEntry.structure[i].Entry != IsDeleted &&
                    DirEntry.structure[i].Entry != IsFree) { // &&


                if (strcmp(dirFile, DirEntry.structureLongNames[i].getName(i, DirEntry.structureLongNames))) {


                    u32 checkSum = DirEntry.structureLongNames[i].CheckSum;

                    rootSectors = RootDirSectors;
                    do {

                        HardDriveDriver::read(rootSectors++, Read_Cmd, &DirEntry.data);

                        for (u32 j = 0; j < 16; j++) {
                            readNextSector = DirEntry.structure[j].Entry; //end of root dir
                            if (readNextSector == 0)
                                return Error;

                            if (DirEntry.structure[j].Attrib != IsLongName &&
                                    DirEntry.structure[j].Attrib != 0 &&
                                    DirEntry.structure[j].Entry != IsDeleted &&
                                    DirEntry.structure[j].Entry != IsFree &&
                                    getCheckSum(DirEntry.structure[j].Name) == checkSum) {

                                *EntryNumber = j;
                                return OK;

                            }

                        }




                    } while (readNextSector != 0);

                }

            }
        }

    } while (readNextSector != 0);
    return Error;
}

returnCode FAT::readFileInfo(const s8 *file, _DirEntryStructure *to) {
    u16 FileEntry = 0;
    if (find(file, &FileEntry) == OK) {
        to->ATTR_ARCHIVE = DirEntry.structure[FileEntry].ATTR_ARCHIVE;
        to->ATTR_DIRECTORY = DirEntry.structure[FileEntry].ATTR_DIRECTORY;
        to->ATTR_HIDDEN = DirEntry.structure[FileEntry].ATTR_HIDDEN;
        to->ATTR_READ_ONLY = DirEntry.structure[FileEntry].ATTR_READ_ONLY;
        to->ATTR_SYSTEM = DirEntry.structure[FileEntry].ATTR_SYSTEM;
        to->ATTR_VOLUME_ID = DirEntry.structure[FileEntry].ATTR_VOLUME_ID;
        to->Attrib = DirEntry.structure[FileEntry].Attrib;
        to->CrtTimeTenth = DirEntry.structure[FileEntry].CrtTimeTenth;
        to->Entry = DirEntry.structure[FileEntry].Entry;
        to->FileSize = DirEntry.structure[FileEntry].FileSize;
        to->FstClusHI = DirEntry.structure[FileEntry].FstClusHI;
        to->FstClusLO = DirEntry.structure[FileEntry].FstClusLO;
        for (u8 i = 0; i < sizeof (DirEntry.structure[FileEntry].Name); i++) {
            to->Name[i] = DirEntry.structure[FileEntry].Name[i];
        }
        to->ReservedNT = DirEntry.structure[FileEntry].ReservedNT;
        to->accessedDay = DirEntry.structure[FileEntry].accessedDay;
        to->accessedMonth = DirEntry.structure[FileEntry].accessedMonth;
        to->accessedYear = DirEntry.structure[FileEntry].accessedYear;
        return OK;
    } else {
        return Error;
    }
    return Error;
}

u8 FAT::getCheckSum(s8 *name) {
    int i;
    u8 sum = 0;

    for (i = 0; i < 11; i++) {
        sum = (sum >> 1) + ((sum & 1) << 7); /* rotate */
        sum += name[i]; /* add next name byte */
    }
    return sum;
}

u32 FAT::readFAT(u32 Cluster) {
    //not treating fat16


    u32 ThisFATSecNum = 0;
    u32 ThisFATEntOffset = 0;

    if (FAT32.structure.BytesPerSector != 0) {

        ThisFATSecNum = ((Cluster * 4) / FAT32.structure.BytesPerSector);
        ThisFATEntOffset = ((Cluster * 4) % FAT32.structure.BytesPerSector) / 4;

        HardDriveDriver::read((FATTAbleStartSector + ThisFATSecNum), Read_Cmd, &FATEntry.data);

    }


    return FATEntry.structure[ThisFATEntOffset].value;

}

returnCode FAT::readSector(const s8 *file, u512 *to) {
    u16 FileEntry = 0;
    if (find(file, &FileEntry) == OK) {

        u32 firstSectorCluster = (u32) (DirEntry.structure[FileEntry].FstClusHI << 16 | DirEntry.structure[FileEntry].FstClusLO);

        if (HardDriveDriver::read(firstSectorCluster + DataRegionStart, Read_Cmd, to) == OK) {

            //FatEntry = readFATEntry(firstSectorCluster);
        } else {
            return Error;
        }

        return OK;
    } else {
        return Error;
    }
    return Error;
}

returnCode FAT::readSector(u32 sectorNumber, u512 *to) {

    if (HardDriveDriver::read(sectorNumber + DataRegionStart, Read_Cmd, to) == OK) {
        return OK;
        //FatEntry = readFATEntry(firstSectorCluster);
    } else {
        return Error;
    }
    return Error;
}