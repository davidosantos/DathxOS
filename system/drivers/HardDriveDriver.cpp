/* 
 * File:   HardDriveDriver.cpp
 * Author: davidosantos
 * 
 * Created on 15 de Agosto de 2015, 15:07
 */

#include "HardDriveDriver.h"

HardDriveDriver::_IDENTIFY_DEVICE_DATA HardDriveDriver::config;
HardDriveDriver::HardDriveRegisters HardDriveDriver::HardDriveRegs;
u8 HardDriveDriver::DriveNumber;

void HardDriveDriver::setup(u8 Drive) {
    DriveNumber = Drive;


    u512 st;

    if (read(0, DeviceID, &st) == Error) {
        Console::print("Error get dev ID");
    }

    for (u32 i = 0; i < sizeof config.words / 2; i++) {
        config.words[i] = st.data[i];
    }

}

//HardDriveDriver::HardDriveDriver(const HardDriveDriver& orig) {
//}
//
//HardDriveDriver::~HardDriveDriver() {
//}

/**
 * On LBA addressing mode the LBA value is set to the following register:
 * Device/Head <- - - LBA bits 27–24
 * Cylinder High <- - - LBA bits 23–16
 * Cylinder Low <- - - LBA bits 15–8
 * Sector Number <- - - LBA bits 7–0
 * @param from
 * @return 
 */
returnCode HardDriveDriver::read(u32 LBA, u8 cmd, u512 *to) {

    if (config.data.Capabilities.LbaSupported == Set) {
        HardDriveRegs.sectorNumber.updateSectorNumber(LBA);
        HardDriveRegs.cynlinderLow.updateCynLow((LBA >> 8));
        HardDriveRegs.cynlinderHigh.updateCynHigh((LBA >> 16));
        HardDriveRegs.drive_HeadReg.Head = (LBA >> 24);
        HardDriveRegs.drive_HeadReg.Drive = HardDriveDriver::DriveNumber;
        HardDriveRegs.drive_HeadReg.r1 = 1;
        HardDriveRegs.drive_HeadReg.r2 = 1;
        HardDriveRegs.drive_HeadReg.LBA = 1;
        HardDriveRegs.drive_HeadReg.update();
        HardDriveRegs.sectorCountReg.updateCount(1);
        if (writeCommand(cmd) == Error) {
            Console::print("There was Error for Issue Command");
        }
    } else {
        if ((config.data.NumberOfCurrentHeads * config.data.NumSectorsPerTrack) != 0) {

            u16 cylinder = LBA / (config.data.NumHeads * config.data.NumSectorsPerTrack);
            u32 temp = LBA % (config.data.NumHeads * config.data.NumSectorsPerTrack);
            u8 head = temp / config.data.NumSectorsPerTrack;
            u8 sector = temp % config.data.NumSectorsPerTrack + 1;

            HardDriveRegs.sectorNumber.updateSectorNumber(sector);
            HardDriveRegs.cynlinderLow.updateCynLow(cylinder);
            HardDriveRegs.cynlinderHigh.updateCynHigh((cylinder >> 8));
            HardDriveRegs.drive_HeadReg.Head = (head);


        }

        HardDriveRegs.drive_HeadReg.Drive = DriveNumber;
        HardDriveRegs.drive_HeadReg.r1 = 1;
        HardDriveRegs.drive_HeadReg.r2 = 1;
        HardDriveRegs.drive_HeadReg.LBA = 0;
        HardDriveRegs.drive_HeadReg.update();
        HardDriveRegs.sectorCountReg.updateCount(1);
        if (writeCommand(cmd) == Error) {
            Console::print("There was Error for Issue Command");
        }

    }
    u8 Retries = 0;

    while (Retries < 255) {
        HardDriveRegs.statusReg_Command.getStatus();
        u32 busy = 0;
        while (HardDriveRegs.statusReg_Command.Busy == Set) {
            HardDriveRegs.statusReg_Command.getStatus();
            if (busy > 500000) {
                Console::print("There was Error HD, too busy %i", busy);
                return Error;
            }
            busy++;
        }

        int index = 0;
        while (HardDriveRegs.statusReg_Command.DRQ == Set) {
            to->data[index] = HardDriveRegs.dataReg.inputData();

            HardDriveRegs.statusReg_Command.getStatus();
            if (HardDriveRegs.statusReg_Command.Error == Set) {
                Console::print("There was Error HD");
                return Error;
            }

            index++;

            if (index > 256) {
                Console::print("%crThere was Error, over lapped %i", index);
                return Error;
            }
        }

        if (index < 255) {
            Retries++;
            Console::print(7, 0, "%ct5Read retry %i", index);
            if (Retries >= 255)
                return Error;
        } else {
            return OK;
        }

    }
    return OK;
}

//returnCode HardDriveDriver::write(u512 sect, u32 to) {
//
//}

returnCode HardDriveDriver::writeCommand(u8 cmd) {
    HardDriveRegs.statusReg_Command.getStatus();
    u16 Retries = 0;
    while (HardDriveRegs.statusReg_Command.DRDY == Reset) {

        Retries++;
        HardDriveRegs.statusReg_Command.getStatus();
        if (Retries > 1000) {
            return Error;
        }
    }

    HardDriveRegs.statusReg_Command.issueCommand(cmd);
    return OK;
}