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
processor::MSR APIC::msr;

void APIC::setup(processor::CPUFeatures *features, Paging::PagesDir *kernelPageDir) {
    //pageManagment::setRangeBusy(0, baseMemoryPointer);
    if (processor::getModelSpecificReg(features, &msr, IA32_APIC_BASE)) {
        u32 apicBaseAddress = (msr.ApicBase << 12);
        apicRegisters = (Registers*) apicBaseAddress;
        Paging::mapRange(apicBaseAddress, apicBaseAddress,
                kernelPageDir, (u32*) apicBaseAddress);
      

    } else {
        Console::print("CPU Does not support MSR");
    }
}

void APIC::enableAPIC() {
    if(msr.ApicEnabled == 1){
        u32 value = apicRegisters->SpuriousInterruptVectorReg.value;
        Console::print("BroadCastbup: %i",apicRegisters->LocalAPICVersionReg.EOIBroadCast);
        value = (value | 256);
        
        Console::print(40,48,"SpuriousInterruptVectorReg.value: %i",apicRegisters->SpuriousInterruptVectorReg.value);
    apicRegisters->SpuriousInterruptVectorReg.value = value;
    Console::print(42,48,"SpuriousInterruptVectorReg.value::: %i",apicRegisters->SpuriousInterruptVectorReg.value);
    } else {
        Console::print("Cannot enable APIC, it might have been disabled by BIOS");
    }
}
void APIC::disableAPIC() {
    if(msr.ApicEnabled == 1){
    apicRegisters->SpuriousInterruptVectorReg.ApicSoftwareEnabled = 0;
    } else {
        Console::print("Cannot disable APIC, it might have been disabled by BIOS");
    }
}

void APIC::startTimer(u32 count){
    apicRegisters->InitialCountReg.value = count;
    apicRegisters->DivideConfigurationReg.value = 11;
    
    apicRegisters->TimerReg.value = 131104;
    
    
       apicRegisters->SpuriousInterruptVectorReg.ApicSoftwareEnabled = 1;
    
    Console::print(0,48,"InitialCountReg: %i", apicRegisters->InitialCountReg.value);
    Console::print(2,48,"DivideConfigurationReg.highOrderBits: %i", apicRegisters->DivideConfigurationReg.highOrderBits);
    Console::print(4,48,"DivideConfigurationReg.lowOrderBits: %i", apicRegisters->DivideConfigurationReg.lowOrderBits);
    Console::print(6,48,"spuriousInterruptVectorReg.ApicSoftwareEnabled: %i", apicRegisters->SpuriousInterruptVectorReg.ApicSoftwareEnabled);
    Console::print(8,48,"spuriousInterruptVectorReg.SpuriousVector: %i", apicRegisters->SpuriousInterruptVectorReg.SpuriousVector);
    Console::print(10,48,"spuriousInterruptVectorReg.EOIBroadcastSuppression: %i", apicRegisters->SpuriousInterruptVectorReg.EOIBroadcastSuppression);
    Console::print(12,48,"TimerRegister.vector : %i", apicRegisters->TimerReg.vector );
    Console::print(14,48,"TimerRegister.DeliveryStatus : %i", apicRegisters->TimerReg.DeliveryStatus );
    Console::print(16,48,"TimerRegister.timerMode : %i", apicRegisters->TimerReg.timerMode );
    Console::print(18,48,"TimerRegister.Masked : %i", apicRegisters->TimerReg.Masked );
   
    Console::print(22,48,"ErrorStatusReg.IllegalRegisterAddress : %i", apicRegisters->ErrorStatusReg.IllegalRegisterAddress );
    Console::print(24,48,"ErrorStatusReg.ReceiveAcceptError : %i", apicRegisters->ErrorStatusReg.ReceiveAcceptError );
    Console::print(26,48,"ErrorStatusReg.ReceiveChecksumError : %i", apicRegisters->ErrorStatusReg.ReceiveChecksumError );
    Console::print(28,48,"ErrorStatusReg.ReceivedIllegalVector : %i", apicRegisters->ErrorStatusReg.ReceivedIllegalVector );
    Console::print(30,48,"ErrorStatusReg.RedirectableIPI : %i", apicRegisters->ErrorStatusReg.RedirectableIPI );
    Console::print(32,48,"ErrorStatusReg.SendAcceptError : %i", apicRegisters->ErrorStatusReg.SendAcceptError );
    Console::print(34,48,"ErrorStatusReg.SendChecksumError : %i", apicRegisters->ErrorStatusReg.SendChecksumError );
    Console::print(36,48,"ErrorStatusReg.SendIllegalVector : %i", apicRegisters->ErrorStatusReg.SendIllegalVector );
    Console::print(38,48,"TimerReg.regt : %h", (u32) &apicRegisters->TimerReg.value);
    
    
}

u32 APIC::getCurrentCount(){
    return apicRegisters->CurrentCountReg.value;
}