/* 
 * File:   HardDriveDriver.h
 * Author: davidosantos
 *
 * Created on 15 de Agosto de 2015, 15:07
 */


#ifndef HARDDRIVEDRIVER_H
#define	HARDDRIVEDRIVER_H
#include "../../util/util.h"
#include "../memory/Memory.h"
#include "../drivers/HardwareIO.h"

#define HD_DATA        0x1F0    // data port for R/W
#define HD_ERROR       0x1F1    // error register / feature reg
#define HD_SEC_COUNT   0x1F2    // R/W sector count
#define HD_SEC_NUM     0x1F3    // LBA low  byte  bits 0 - 7
#define HD_CYL_LOW     0x1F4    // LBA mid  byte bits 8 - 15
#define HD_CYL_HIG     0x1F5    // LBA high byte bits 16 - 23
#define HD_DRIVEHEAD       0x1F6    // 1B1D0000 => B=LBA, D=drive => 0xE0 or 0xF0 bits 24 - 27
#define HD_CMD         0x1F7    // command : R=0x20 W=0x30
#define HD_STATUS      0x1F7    // status register

#define HD_STATUS_ALT  0x3F6    // status register alternate and control
#define HD_ADRESS      0x3F7    // adress register

//bits test
#define HD_DRQ         0x08
#define HD_RDY         0x40
#define HD_ERR         0x01

// commands

#define DeviceID 	0xEC
#define Read_Cmd 	0x20
#define Write_Cmd	0x30

#define Set 	0x01
#define Reset	0x00

class HardDriveDriver {
    static u8 DriveNumber;
    typedef union _IDENTIFY_DEVICE_DATA {
        u16 words[256];

        struct Data {

            struct {
                u16 Reserved1 : 1;
                u16 Retired3 : 1;
                u16 ResponseIncomplete : 1;
                u16 Retired2 : 3;
                u16 FixedDevice : 1;
                u16 RemovableMedia : 1;
                u16 Retired1 : 7;
                u16 DeviceType : 1;
            } GeneralConfiguration;
            u16 NumCylinders;
            u16 ReservedWord2;
            u16 NumHeads;
            u16 Retired1[2];
            u16 NumSectorsPerTrack;
            u16 VendorUnique1[3];
            s8 SerialNumber[20];
            u16 Retired2[2];
            u16 Obsolete1;
            s8 FirmwareRevision[8];
            s8 ModelNumber[40];
            u8 MaximumBlockTransfer;
            u8 VendorUnique2;
            u16 ReservedWord48;

            struct {
                u8 ReservedByte49;
                u8 DmaSupported : 1;
                u8 LbaSupported : 1;
                u8 IordyDisable : 1;
                u8 IordySupported : 1;
                u8 Reserved1 : 1;
                u8 StandybyTimerSupport : 1;
                u8 Reserved2 : 2;
                u16 ReservedWord50;
            } Capabilities;
            u16 ObsoleteWords51[2];
            u16 TranslationFieldsValid : 3;
            u16 Reserved3 : 13;
            u16 NumberOfCurrentCylinders;
            u16 NumberOfCurrentHeads;
            u16 CurrentSectorsPerTrack;
            u32 CurrentSectorCapacity;
            u8 CurrentMultiSectorSetting;
            u8 MultiSectorSettingValid : 1;
            u8 ReservedByte59 : 7;
            u32 UserAddressableSectors;
            u16 ObsoleteWord62;
            u16 MultiWordDMASupport : 8;
            u16 MultiWordDMAActive : 8;
            u16 AdvancedPIOModes : 8;
            u16 ReservedByte64 : 8;
            u16 MinimumMWXferCycleTime;
            u16 RecommendedMWXferCycleTime;
            u16 MinimumPIOCycleTime;
            u16 MinimumPIOCycleTimeIORDY;
            u16 ReservedWords69[6];
            u16 QueueDepth : 5;
            u16 ReservedWord75 : 11;
            u16 ReservedWords76[4];
            u16 MajorRevision;
            u16 MinorRevision;

            struct {
                u16 SmartCommands : 1;
                u16 SecurityMode : 1;
                u16 RemovableMediaFeature : 1;
                u16 PowerManagement : 1;
                u16 Reserved1 : 1;
                u16 WriteCache : 1;
                u16 LookAhead : 1;
                u16 ReleaseInterrupt : 1;
                u16 ServiceInterrupt : 1;
                u16 DeviceReset : 1;
                u16 HostProtectedArea : 1;
                u16 Obsolete1 : 1;
                u16 WriteBuffer : 1;
                u16 ReadBuffer : 1;
                u16 Nop : 1;
                u16 Obsolete2 : 1;
                u16 DownloadMicrocode : 1;
                u16 DmaQueued : 1;
                u16 Cfa : 1;
                u16 AdvancedPm : 1;
                u16 Msn : 1;
                u16 PowerUpInStandby : 1;
                u16 ManualPowerUp : 1;
                u16 Reserved2 : 1;
                u16 SetMax : 1;
                u16 Acoustics : 1;
                u16 BigLba : 1;
                u16 DeviceConfigOverlay : 1;
                u16 FlushCache : 1;
                u16 FlushCacheExt : 1;
                u16 Resrved3 : 2;
                u16 SmartErrorLog : 1;
                u16 SmartSelfTest : 1;
                u16 MediaSerialNumber : 1;
                u16 MediaCardPassThrough : 1;
                u16 StreamingFeature : 1;
                u16 GpLogging : 1;
                u16 WriteFua : 1;
                u16 WriteQueuedFua : 1;
                u16 WWN64Bit : 1;
                u16 URGReadStream : 1;
                u16 URGWriteStream : 1;
                u16 ReservedForTechReport : 2;
                u16 IdleWithUnloadFeature : 1;
                u16 Reserved4 : 2;
            } CommandSetSupport;

            struct {
                u16 SmartCommands : 1;
                u16 SecurityMode : 1;
                u16 RemovableMediaFeature : 1;
                u16 PowerManagement : 1;
                u16 Reserved1 : 1;
                u16 WriteCache : 1;
                u16 LookAhead : 1;
                u16 ReleaseInterrupt : 1;
                u16 ServiceInterrupt : 1;
                u16 DeviceReset : 1;
                u16 HostProtectedArea : 1;
                u16 Obsolete1 : 1;
                u16 WriteBuffer : 1;
                u16 ReadBuffer : 1;
                u16 Nop : 1;
                u16 Obsolete2 : 1;
                u16 DownloadMicrocode : 1;
                u16 DmaQueued : 1;
                u16 Cfa : 1;
                u16 AdvancedPm : 1;
                u16 Msn : 1;
                u16 PowerUpInStandby : 1;
                u16 ManualPowerUp : 1;
                u16 Reserved2 : 1;
                u16 SetMax : 1;
                u16 Acoustics : 1;
                u16 BigLba : 1;
                u16 DeviceConfigOverlay : 1;
                u16 FlushCache : 1;
                u16 FlushCacheExt : 1;
                u16 Resrved3 : 2;
                u16 SmartErrorLog : 1;
                u16 SmartSelfTest : 1;
                u16 MediaSerialNumber : 1;
                u16 MediaCardPassThrough : 1;
                u16 StreamingFeature : 1;
                u16 GpLogging : 1;
                u16 WriteFua : 1;
                u16 WriteQueuedFua : 1;
                u16 WWN64Bit : 1;
                u16 URGReadStream : 1;
                u16 URGWriteStream : 1;
                u16 ReservedForTechReport : 2;
                u16 IdleWithUnloadFeature : 1;
                u16 Reserved4 : 2;
            } CommandSetActive;
            u16 UltraDMASupport : 8;
            u16 UltraDMAActive : 8;
            u16 ReservedWord89[4];
            u16 HardwareResetResult;
            u16 CurrentAcousticValue : 8;
            u16 RecommendedAcousticValue : 8;
            u16 ReservedWord95[5];
            u32 Max48BitLBA[2];
            u16 StreamingTransferTime;
            u16 ReservedWord105;

            struct {
                u16 LogicalSectorsPerPhysicalSector : 4;
                u16 Reserved0 : 8;
                u16 LogicalSectorLongerThan256Words : 1;
                u16 MultipleLogicalSectorsPerPhysicalSector : 1;
                u16 Reserved1 : 2;
            } PhysicalLogicalSectorSize;
            u16 InterSeekDelay;
            u16 WorldWideName[4];
            u16 ReservedForWorldWideName128[4];
            u16 ReservedForTlcTechnicalReport;
            u16 WordsPerLogicalSector[2];

            struct {
                u16 ReservedForDrqTechnicalReport : 1;
                u16 WriteReadVerifySupported : 1;
                u16 Reserved01 : 11;
                u16 Reserved1 : 2;
            } CommandSetSupportExt;

            struct {
                u16 ReservedForDrqTechnicalReport : 1;
                u16 WriteReadVerifyEnabled : 1;
                u16 Reserved01 : 11;
                u16 Reserved1 : 2;
            } CommandSetActiveExt;
            u16 ReservedForExpandedSupportandActive[6];
            u16 MsnSupport : 2;
            u16 ReservedWord1274 : 14;

            struct {
                u16 SecuritySupported : 1;
                u16 SecurityEnabled : 1;
                u16 SecurityLocked : 1;
                u16 SecurityFrozen : 1;
                u16 SecurityCountExpired : 1;
                u16 EnhancedSecurityEraseSupported : 1;
                u16 Reserved0 : 2;
                u16 SecurityLevel : 1;
                u16 Reserved1 : 7;
            } SecurityStatus;
            u16 ReservedWord129[31];

            struct {
                u16 MaximumCurrentInMA2 : 12;
                u16 CfaPowerMode1Disabled : 1;
                u16 CfaPowerMode1Required : 1;
                u16 Reserved0 : 1;
                u16 Word160Supported : 1;
            } CfaPowerModel;
            u16 ReservedForCfaWord161[8];

            struct {
                u16 SupportsTrim : 1;
                u16 Reserved0 : 15;
            } DataSetManagementFeature;
            u16 ReservedForCfaWord170[6];
            u16 CurrentMediaSerialNumber[30];
            u16 ReservedWord206;
            u16 ReservedWord207[2];

            struct {
                u16 AlignmentOfLogicalWithinPhysical : 14;
                u16 Word209Supported : 1;
                u16 Reserved0 : 1;
            } BlockAlignment;
            u16 WriteReadVerifySectorCountMode3Only[2];
            u16 WriteReadVerifySectorCountMode2Only[2];

            struct {
                u16 NVCachePowerModeEnabled : 1;
                u16 Reserved0 : 3;
                u16 NVCacheFeatureSetEnabled : 1;
                u16 Reserved1 : 3;
                u16 NVCachePowerModeVersion : 4;
                u16 NVCacheFeatureSetVersion : 4;
            } NVCacheCapabilities;
            u16 NVCacheSizeLSW;
            u16 NVCacheSizeMSW;
            u16 NominalMediaRotationRate;
            u16 ReservedWord218;

            struct {
                u8 NVCacheEstimatedTimeToSpinUpInSeconds;
                u8 Reserved;
            } NVCacheOptions;
            u16 ReservedWord220[35];
            u16 Signature : 8;
            u16 CheckSum : 8;
        }data;
    } IDENTIFY_DEVICE_DATA, *PIDENTIFY_DEVICE_DATA;

  
    
    typedef struct HDRegisters {

        struct DataReg {

            u16 inputData() {

                return HardwareIO::inw(HD_DATA);
                
            }

            void outputData(u16 data) {
                HardwareIO::outw(HD_DATA, data);
            }
        } dataReg;

        union ErrorReg_Feature {
            u8 binary;

            struct {
                u8 AMNF : 1,
                TK0 : 1,
                ABRT : 1,
                NotUsed : 1,
                IDNF : 1,
                NotUsed1 : 1,
                ECC : 1,
                CRC : 1;
            };

            void getError() {
                binary = HardwareIO::inb(HD_ERROR);
            }

            void updateFeature(u8 feature) {
                HardwareIO::outb(HD_ERROR, feature);
            }
        } errorReg_Feature;

        struct SectorCountReg {
            u8 data;

            void getCount() {
                data = HardwareIO::inb(HD_SEC_COUNT);
            }

            void updateCount(u8 count) {
                HardwareIO::outb(HD_SEC_COUNT, count);
            }
        } sectorCountReg;

        struct SectorNumber {
            u8 data;

            void getSectorNumber() {
                data = HardwareIO::inb(HD_SEC_NUM);
            }

            void updateSectorNumber(u8 SectorNumber) {
                HardwareIO::outb(HD_SEC_NUM, SectorNumber);
            }
        } sectorNumber;
        
        struct CynlinderLow {
            u8 data;

            void getCynLow() {
                data = HardwareIO::inb(HD_CYL_LOW);
            }

            void updateCynLow(u8 CynLow) {
                HardwareIO::outb(HD_CYL_LOW, CynLow);
            }
        } cynlinderLow;

        struct CynlinderHigh {
            u8 data;

            void getCynHigh() {
                data = HardwareIO::inb(HD_CYL_HIG);
            }

            void updateCynHigh(u8 CynHigh) {
                HardwareIO::outb(HD_CYL_HIG, CynHigh);
            }

            u8 operator>>(u8 &value) {
                value = HardwareIO::inb(HD_CYL_HIG);
                return value;
            }
        } cynlinderHigh;

        union Drive_HeadReg {
            u8 binary;

            struct {
                u8 Head : 4,
                Drive : 1,
                r1 : 1, //must set to 1
                LBA : 1,
                r2 : 1; //must set to 1
            };


            void operator<<(u8 value) {
                binary = value;
                HardwareIO::outb(HD_DRIVEHEAD, binary);
            }
            
            u8 operator>>(u8 &value) {
                binary =  HardwareIO::inb(HD_DRIVEHEAD);
                value = binary;
                return binary;
            }
            
            void update() {
                HardwareIO::outb(HD_DRIVEHEAD, binary);
            }

           
        } drive_HeadReg;

        union StatusReg_Command {
            u8 binary;

            struct {
                u8 Error : 1,
                r1 : 2,
                DRQ : 1,
                DSC : 1,
                DF : 1,
                DRDY : 1,
                Busy : 1;
            };

            void getStatus() {
                binary = HardwareIO::inb(HD_STATUS);
            }

            void issueCommand(u8 commmand) {
                HardwareIO::outb(HD_CMD, commmand);
            }
        } statusReg_Command;
    } HardDriveRegisters;
    
    static _IDENTIFY_DEVICE_DATA config;
    static HardDriveRegisters HardDriveRegs;
    
public: 
    static returnCode read(u32 LBA, u8 cmd, u512 *to);

   // static returnCode write(u512 sect, u32 to);

    static returnCode writeCommand(u8 cmd);

public:
    static void setup(u8 Drive);
    //    HardDriveDriver(const HardDriveDriver& orig);
    //    virtual ~HardDriveDriver();
private:

};

#endif	/* HARDDRIVEDRIVER_H */

