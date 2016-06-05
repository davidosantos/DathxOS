/* 
 * File:   FAT32.h
 * Author: davidosantos
 *
 * Created on 22 de Agosto de 2015, 17:53
 */

#ifndef FAT32_H
#define	FAT32_H
#include "../../util/util.h"
#include "../../util/util.h"
#include "../drivers/HardDriveDriver.h"
#include "../monitor/Console.h"
#include "MBR.h"

#define bootable    0x80
#define FAT32D         0x0C
#define EoF         0xFFFFFF8
#define EoF2         0xFFFFFFF
#define IsLongName         0xF
#define IsDeleted         0xE5
#define IsFree         0x00
#define isON         1
#define slash 0x2f
#define dot 0x2e
#define space 0x20
 
class FAT {
public:

    struct _ExtSectorFAT12_16 {
        u8 DrvNum;
        u8 Reserved;
        u8 BootSig;
        u32 VolumeID;
        s8 VolumeLabel[11];
        s8 FileSysInfo[8];
        u8 Reserved1[420];
        u16 Signature;
        u8 Ramaining;
    } __attribute__((packed));

    struct _ExtSectorFAT32 {
        u32 FAT_Size;

        struct {
            u16 ActiveFat : 4,
            Reserved : 3,
            Mirrored : 1,
            /**
              0 means the FAT is mirrored at runtime into
                all FATs.
                -- 1 means only one FAT is active; it is the one
                referenced in bits 0-3. 
             */
            Reserved1 : 8;

        };
        u16 FSVer;
        u32 RootCluster;
        u16 FSInfo;
        u16 BkBootSect;
        u8 Reserved2[12];
        u8 DrvNum;
        u8 Reserved3;
        u8 BootSig;
        u32 VolumeID;
        s8 VolumeLabel[11];
        s8 FileSysInfo[8];
        u8 Reserved4[420];
        u16 Signature;
        u8 Ramaining;
    } __attribute__((packed));

    struct Fat12_16_Structure {
        u8 boot [3];
        s8 OEM_Name [8];
        u16 BytesPerSector;
        u8 SectPerCluster;
        u16 RsvdSecCnt;
        u8 NumFATs;
        u16 RootEntCnt;
        u16 TotSec16;
        u8 Media;
        u16 FATSz16;
        u16 SecPerTrk;
        u16 NumHeads;
        u32 HiddenSect;
        u32 TotalSect32;
        _ExtSectorFAT12_16 ExtSectorFAT12_16;

    } __attribute__((packed));

    struct Fat32_Structure {
        u8 boot [3];
        s8 OEM_Name [8];
        u16 BytesPerSector;
        u8 SectPerCluster;
        u16 RsvdSecCnt;
        u8 NumFATs;
        u16 RootEntCnt;
        u16 TotalSect16;
        u8 Media;
        u16 FATSz16;
        u16 SecPerTrk;
        u16 NumHeads;
        u32 HiddenSect;
        u32 TotalSect32;
        _ExtSectorFAT32 ExtSectorFAT32;

    } __attribute__((packed));

    typedef union _FAT32 {
        u512 data;
        Fat32_Structure structure;
    } __attribute__((packed)) FAT32_Structure;

    typedef union FAT12_16 {
        u16 data[256];
        Fat12_16_Structure structure;
    } __attribute__((packed)) FAT12_16_Structure;

    struct _FSInfoSect {
        u32 Signature;
        u8 Reserved[480];
        u32 StructSig;
        u32 Free_sect_count;
        u32 NextFreeSect;
        u8 Reserved1[12];
        u32 TrailSignature;
    } __attribute__((packed));

    typedef union _FSInfoSecto {
        u512 data;
        _FSInfoSect structure;
    } __attribute__((packed)) _FSInfoSector;

    struct shortNameEntry {

        union {
            u8 Entry;
            s8 shortName[8];
        };
        
        s8 extention[3];

        union {

            struct {
                u8 Attrib : 6;
            };

            struct {
                u8 ATTR_READ_ONLY : 1,
                ATTR_HIDDEN : 1,
                ATTR_SYSTEM : 1,
                ATTR_VOLUME_ID : 1,
                ATTR_DIRECTORY : 1,
                ATTR_ARCHIVE : 1,
                : 2;
            } __attribute__((packed));
        } __attribute__((packed));

        u8 ReservedNT;
        u8 CrtTimeTenth;

        struct {
            u16 createdSeconds : 5,
            createdMinutes : 5,
            createdHour : 6;
        };

        struct {
            u16 createdDay : 5,
            createdMonth : 4,
            createdYear : 7;
        };

        struct {
            u16 accessedDay : 5,
            accessedMonth : 4,
            accessedYear : 7;
        };

        u16 FstClusHI;

        struct {
            u16 writeSeconds : 5,
            writeMinutes : 5,
            writeHour : 6;
        };

        struct {
            u16 writeDay : 5,
            writeMonth : 4,
            writeYear : 7;
        };
        u16 FstClusLO;
        u32 FileSize;

        s8 *getName() {
            s8 *name;


            name = new s8 [11];
            for (u8 i = 0; i < sizeof (shortName); i++) {
                name[i] = shortName[i];
            }
            return name;

        }

        u32 getClusterNumber() {
            return (FstClusHI << 16 | FstClusLO);
        }

    } __attribute__((packed));

    struct longNameEntry {

        union {

            struct {
                u8 Sequence : 6,
                lastLongFlag : 1;
            };
        };

        union {
            s8 Name1[10];

            struct {
                s8 character : 8,
                : 8;
            } chars1[5];
        };

        union {

            struct {
                u8 Attrib : 6;
            };

            struct {
                u8 ATTR_READ_ONLY : 1,
                ATTR_HIDDEN : 1,
                ATTR_SYSTEM : 1,
                ATTR_VOLUME_ID : 1,
                ATTR_DIRECTORY : 1,
                ATTR_ARCHIVE : 1,
                : 2;
            } __attribute__((packed));
        } __attribute__((packed));

        u8 subComp;
        u8 CheckSum;

        union {
            s8 Name2[12];

            struct {
                s8 character : 8,
                : 8;
            } chars2[6];
        };
        u16 ClusterLow;

        union {
            s8 Name3[4];

            struct {
                s8 character : 8,
                : 8;
            } chars3[2];
        };

        s8 *getName(u16 index, longNameEntry *structure) {
            s8* name;


            u16 arraySize = 0;

            for (s16 i = index; i > -1; i--) { //determine the size of array

                if (structure[i].lastLongFlag == 0) {

                    arraySize = arraySize + 13;
                }
            }

            name = new s8 [arraySize];
            u8 nameIndex = 0;
            for (s16 i = index; i > -1; i--) { //copy the array


                if (structure[i].lastLongFlag == 0) {

                    for (u8 j = 0; j < 10; j++) {
                        if (structure[i].Name1[j] != 0)
                            name[nameIndex++] = structure[i].Name1[j];
                    }
                    for (u8 j = 0; j < 12; j++) {
                        if (structure[i].Name2[j] != 0)
                            name[nameIndex++] = structure[i].Name2[j];
                    }
                    for (u8 j = 0; j < 4; j++) {
                        if (structure[i].Name3[j] != 0)
                            name[nameIndex++] = structure[i].Name3[j];
                    }
                } else {

                    for (u8 j = 0; j < 10; j++) {
                        if (structure[i].Name1[j] == 0 && structure[i].Name1[j + 1] == 0) //if null
                            return name;

                        if (structure[i].Name1[j] != 0)
                            name[nameIndex++] = structure[i].Name1[j];

                    }
                    for (u8 j = 0; j < 12; j++) {
                        if (structure[i].Name2[j] == 0 && structure[i].Name2[j + 1] == 0) //if null
                            return name;

                        if (structure[i].Name2[j] != 0)
                            name[nameIndex++] = structure[i].Name2[j];

                    }
                    for (u8 j = 0; j < 4; j++) {

                        if (structure[i].Name3[j] == 0 && structure[i].Name3[j + 1] == 0) //if null
                            return name;

                        if (structure[i].Name3[j] != 0)
                            name[nameIndex++] = structure[i].Name3[j];

                    }

                    return name;
                }

            }
            return name;
        }
    } __attribute__((packed));

    typedef union __DirEntryStructure {
        u512 data;

        union {
            shortNameEntry shortName[16];
            longNameEntry longName[16];
        };
    } __attribute__((packed)) _Cluster;

    struct ___FATEntry {
        u32 value : 28,
        Reserved : 4;
    };

    typedef union __FATEntry {
        u512 data;

        union {

            struct {
                u32 Media : 8,
                ReservedSetToOnes : 24;

                u32 ReservedSetToOnes2 : 30,
                CleanShutBitMask : 1,
                HrdErrBitMask : 1;


            };
            ___FATEntry structure[128];
        };
    } __attribute__((packed)) _FATEntry;

    static _FSInfoSector FSInfoSector;
    static FAT32_Structure BPB;
    static FAT12_16_Structure FAT12_16;
    static _FATEntry FATEntry;
    static _Cluster DirEntry;
    static u32 RootDirSectors;
    static u32 DataRegionStart;
    static u32 RootDirSectorsCount;
    static u32 DataSec;
    static u32 CountofClusters;
    static u32 FATTAbleStartSector;

public:

    static returnCode readCluster(FAT::shortNameEntry *file, u512 *to);

    static returnCode readCluster(u32 sectorNumber, u512 *to);

    static u32 readFAT(u32 Cluster);

    static void setup();
    
    static shortNameEntry find(const s8 *dirFile);
    
    //    FAT32(const FAT32& orig);
    //    virtual ~FAT32();
private:

    



    static u8 getCheckSum(u8 *pFcbName);

    static FAT::longNameEntry findNextLongNameEntry(_Cluster *data, u8 checksum, u8 sequece);
    
    static FAT::shortNameEntry isThereShortNameEntry(_Cluster *data, const s8 *name);
    static FAT::shortNameEntry isThereLongNameEntry(_Cluster *data, const s8 *name);
    static u32 getSector(u32 Cluster);


};

#endif	/* FAT32_H */

