/* 
 * File:   APIC.cpp
 * Author: david
 * 
 * Created on May 7, 2016, 4:46 PM
 */

#include "APIC.h"

APIC::APIC() {
}
//
//APIC::APIC(const APIC& orig) {
//}
//
//APIC::~APIC() {
//}
APIC::Registers *APIC::apicRegisters;
processor::MSR APIC::modelSpecificReg;

void APIC::setup(processor::CPUFeatures *features, Paging::PagesDir *kernelPageDir) {
    //pageManagment::setRangeBusy(0, baseMemoryPointer);
    if (processor::getModelSpecificReg(features, &modelSpecificReg, IA32_APIC_BASE)) {
        u32 apicBaseAddress = (modelSpecificReg.ApicBase << 12);

        apicRegisters = (Registers*) apicBaseAddress;

        Paging::mapRange(apicBaseAddress, apicBaseAddress,
                kernelPageDir, (u32*) apicBaseAddress,false);

        if (modelSpecificReg.ApicEnabled == 1) {
            Console::print("ApicEnabled is ON, Base Address: %h",apicBaseAddress);
            
        } else {
            Console::print("ApicEnabled is OFF");
        }

        LogicalDestinationReg logicalDestReg = apicRegisters->LogicalDestinationRegister;
        DestinationFormatReg destFomatReg = apicRegisters->DestinationFormatRegister;
        TimerReg timerReg = apicRegisters->TimerRegister;
        PerformanceMonitoringCountersReg perfReg = apicRegisters->PerformanceMonitoringCountersRegister;
        ThermalSensorReg thermReg = apicRegisters->ThermalSensorRegister;
        ErrorReg errReg = apicRegisters->ErrorRegister;
        //CMCIReg cmci = apicRegisters->CMCIRegister;
        LINT0Reg lInt0 = apicRegisters->LINT0Register;
        LINT1Reg lInt1 = apicRegisters->LINT1Register;
        TaskPriorityReg taskPrior = apicRegisters->TaskPriorityRegister;
        LocalAPICVersionReg version = apicRegisters->LocalAPICVersionRegister;

        logicalDestReg.DestinationLogicalAPICID = 0x1; //logical id = 1
        destFomatReg.DestinationFormat = 0xFF; //flat
        timerReg.Mask = ON;
        perfReg.Mask = ON;
        thermReg.Mask = ON;
        errReg.Mask = ON;
        // cmci.Mask = ON;
        lInt0.Mask = ON;
        lInt1.Mask = ON;
        taskPrior.TaskPriorityClass = 0;
        taskPrior.TaskPrioritySubClass = 0;

        apicRegisters->LogicalDestinationRegister = logicalDestReg;
        apicRegisters->DestinationFormatRegister = destFomatReg;
        apicRegisters->TimerRegister = timerReg;
        apicRegisters->PerformanceMonitoringCountersRegister = perfReg;
        apicRegisters->ThermalSensorRegister = thermReg;
        apicRegisters->ErrorRegister = errReg;
        //apicRegisters->CMCIRegister = cmci;
        apicRegisters->LINT0Register = lInt0;
        apicRegisters->LINT1Register = lInt1;
        apicRegisters->TaskPriorityRegister = taskPrior;
        Console::print("Local APIC Version: %i",version.version);
    } else {
        Console::print("CPU Does not support MSR");
    }
}

void APIC::enableAPIC() {
    if (modelSpecificReg.ApicEnabled == 1) {
        SpuriousInterruptVectorReg spuriousReg = apicRegisters->SpuriousInterruptVectorRegister;

        spuriousReg.ApicSoftwareEnabled = ON;


        apicRegisters->SpuriousInterruptVectorRegister = spuriousReg;

    } else {
        Console::print("Cannot enable APIC, it might have been disabled by BIOS");
    }
}

void APIC::disableAPIC() {
    if (modelSpecificReg.ApicEnabled == 1) {
        SpuriousInterruptVectorReg spuriousReg = apicRegisters->SpuriousInterruptVectorRegister;
        spuriousReg.ApicSoftwareEnabled = OFF;
        apicRegisters->SpuriousInterruptVectorRegister = spuriousReg;
    } else {
        Console::print("Cannot disable APIC, it might have been disabled by BIOS");
    }
}

void APIC::startTimer(u32 count) {

    DivideConfigurationReg divideConReg = apicRegisters->DivideConfigurationRegister;
    SpuriousInterruptVectorReg spuriousReg = apicRegisters->SpuriousInterruptVectorRegister;
    TimerReg timerReg = apicRegisters->TimerRegister;

    timerReg.Mask = OFF;
    timerReg.vector = 32;
    timerReg.timerMode = 1;
    divideConReg.lowOrderBits = 3;
    divideConReg.highOrderBits = 1;
    spuriousReg.ApicSoftwareEnabled = 1;


    apicRegisters->DivideConfigurationRegister = divideConReg;
    apicRegisters->InitialCountRegister = count;
    apicRegisters->SpuriousInterruptVectorRegister = spuriousReg;
    apicRegisters->TimerRegister = timerReg;


    //    Console::print(0, 48, "InitialCountReg: %h", apicRegisters->InitialCountRegister);
    //    Console::print(2, 48, "DivideConfigurationReg.highOrderBits: %i", apicRegisters->DivideConfigurationRegister.highOrderBits);
    //    Console::print(4, 48, "DivideConfigurationReg.lowOrderBits: %i", apicRegisters->DivideConfigurationRegister.lowOrderBits);
    //    Console::print(6, 48, "spuriousInterruptVectorReg.ApicSoftwareEnabled: %i", apicRegisters->SpuriousInterruptVectorRegister.ApicSoftwareEnabled);
    //    Console::print(8, 48, "spuriousInterruptVectorReg.SpuriousVector: %i", apicRegisters->SpuriousInterruptVectorRegister.SpuriousVector);
    //    Console::print(10, 48, "spuriousInterruptVectorReg.EOIBroadcastSuppression: %i", apicRegisters->SpuriousInterruptVectorRegister.EOIBroadcastSuppression);
    //    Console::print(12, 48, "TimerRegister.vector : %i", apicRegisters->TimerRegister.vector);
    //    Console::print(14, 48, "TimerRegister.DeliveryStatus : %i", apicRegisters->TimerRegister.DeliveryStatus);
    //    Console::print(16, 48, "TimerRegister.timerMode : %i", apicRegisters->TimerRegister.timerMode);
    //    Console::print(18, 48, "TimerRegister.Masked : %i", apicRegisters->TimerRegister.Mask);
    //
    //    Console::print(22, 48, "ErrorStatusReg.IllegalRegisterAddress : %i", apicRegisters->ErrorStatusRegister.IllegalRegisterAddress);
    //    Console::print(24, 48, "ErrorStatusReg.ReceiveAcceptError : %i", apicRegisters->ErrorStatusRegister.ReceiveAcceptError);
    //    Console::print(26, 48, "ErrorStatusReg.ReceiveChecksumError : %i", apicRegisters->ErrorStatusRegister.ReceiveChecksumError);
    //    Console::print(28, 48, "ErrorStatusReg.ReceivedIllegalVector : %i", apicRegisters->ErrorStatusRegister.ReceivedIllegalVector);
    //    Console::print(30, 48, "ErrorStatusReg.RedirectableIPI : %i", apicRegisters->ErrorStatusRegister.RedirectableIPI);
    //    Console::print(32, 48, "ErrorStatusReg.SendAcceptError : %i", apicRegisters->ErrorStatusRegister.SendAcceptError);
    //    Console::print(34, 48, "ErrorStatusReg.SendChecksumError : %i", apicRegisters->ErrorStatusRegister.SendChecksumError);
    //    Console::print(36, 48, "ErrorStatusReg.SendIllegalVector : %i", apicRegisters->ErrorStatusRegister.SendIllegalVector);


}

u32 APIC::getCurrentCount() {
    return apicRegisters->CurrentCountRegister;
}

void APIC::issueEOI() {
    apicRegisters->EOIRegister = 0;
}