/* 
 * File:   APIC.h
 * Author: david
 *
 * Created on May 7, 2016, 4:46 PM
 */

#ifndef APIC_H
#define APIC_H

#include "../../util/util.h"
#include "../monitor/Console.h"
#include "../memory/Memory.h"
#include "msr.h"
#include "../../system/processor.h"

#define ReservedReg  struct { \
                }__attribute__((aligned(16), packed));

#define ApicDefautAddrs  0xFEE00000
#define ON 1
#define OFF 0

class APIC {
public:

    static void setup(processor::CPUFeatures *features, Paging::PageDirectory *kernelPageDir);

    static void enableAPIC();
    static void disableAPIC();
    /**
     * 
     * 10.5.4
APIC Timer
The local APIC unit contains a 32-bit programmable timer that is available to software to time events or operations.
This timer is set up by programming four registers: the divide configuration register (see Figure 10-10), the initial-
count and current-count registers (see Figure 10-11), and the LVT timer register (see Figure 10-8).
If CPUID.06H:EAX.ARAT[bit 2] = 1, the processor’s APIC timer runs at a constant rate regardless of P-state transi-
tions and it continues to run at the same rate in deep C-states.
If CPUID.06H:EAX.ARAT[bit 2] = 0 or if CPUID 06H is not supported, the APIC timer may temporarily stop while the
processor is in deep C-states or during transitions caused by Enhanced Intel SpeedStep® Technology.
4 3 2 1 0
31
0
Reserved
Address: FEE0 03E0H
Value after reset: 0H
Divide Value (bits 0, 1 and 3)
000: Divide by 2
001: Divide by 4
010: Divide by 8
011: Divide by 16
100: Divide by 32
101: Divide by 64
110: Divide by 128
111: Divide by 1
Figure 10-10. Divide Configuration Register
31
0
Initial Count
Current Count
Address: Initial Count FEE0 0380H
Current Count FEE0 0390H
Value after reset: 0H
Figure 10-11. Initial Count and Current Count Registers
The APIC timer frequency will be the processor’s bus clock or core crystal clock frequency (when TSC/core crystal
clock ratio is enumerated in CPUID leaf 0x15) divided by the value specified in the divide configuration register.
The timer can be configured through the timer LVT entry for one-shot or periodic operation. In one-shot mode, the
timer is started by programming its initial-count register. The initial count value is then copied into the current-
count register and count-down begins. After the timer reaches zero, an timer interrupt is generated and the timer
remains at its 0 value until reprogrammed.
In periodic mode, the current-count register is automatically reloaded from the initial-count register when the
count reaches 0 and a timer interrupt is generated, and the count-down is repeated. If during the count-down
10-16 Vol. 3AADVANCED PROGRAMMABLE INTERRUPT CONTROLLER (APIC)
process the initial-count register is set, counting will restart, using the new initial-count value. The initial-count
register is a read-write register; the current-count register is read only.
A write of 0 to the initial-count register effectively stops the local APIC timer, in both one-shot and periodic mode.
The LVT timer register determines the vector number that is delivered to the processor with the timer interrupt that
is generated when the timer count reaches zero. The mask flag in the LVT timer register can be used to mask the
timer interrupt.
     * 
     */
    static void startTimer(u32 count);
    static u32 getCurrentCount();
    static void issueEOI();

    APIC();
    //    APIC(const APIC& orig);
    //    virtual ~APIC();

    union LocalAPICIDReg {

        struct {
u32:
            25,
            APICID : 4,
            : 4;
        };

        struct {
u32:
            25,
            APICIDXeon : 8;
        };
        u32 x2APICID;
    } __attribute__((packed));

    struct LocalAPICVersionReg {
        u32 version : 8,
        : 8, //reserved
        MaxLVTEntry : 8,
        EOIBroadCast : 1,
        : 7; //reserved
    } __attribute__((packed));

    struct TaskPriorityReg {
        u32 TaskPrioritySubClass : 4,
        TaskPriorityClass : 4,
        : 24;
    } __attribute__((packed));

    struct ArbitrationPriorityReg {
        u32 ArbitrationPrioritySubClass : 4,
        ArbitrationPriorityClass : 4,
        : 24;
    } __attribute__((packed));

    struct ProcessorPriorityReg {
        u32 AProcessorPrioritySubClass : 4,
        ProcessorPriorityClass : 4,
        : 24;
    } __attribute__((packed));

    struct LogicalDestinationReg {
u32:
        24,
        DestinationLogicalAPICID : 8;
    } __attribute__((packed));

    struct DestinationFormatReg {
u32:
        24,
        DestinationFormat : 8;
        //Flat model: 1111B
        //Cluster model: 0000B
    } __attribute__((packed));

    struct SpuriousInterruptVectorReg {

        struct {
            u32 SpuriousVector : 8,
            ApicSoftwareEnabled : 1,
            FocusProcessorChecking : 1,
            : 2,
            EOIBroadcastSuppression : 1,
            : 19;
        };

        /**
         1. Not supported on all processors.
        2. Not supported in Pentium 4 and Intel Xeon processors.
        3. For the P6 family and Pentium processors, bits 0 through 3
        are always 0.
         */
    } __attribute__((packed));

    struct ErrorStatusReg {
        u32 SendChecksumError : 1,
        ReceiveChecksumError : 1,
        SendAcceptError : 1,
        ReceiveAcceptError : 1,
        RedirectableIPI : 1,
        SendIllegalVector : 1,
        ReceivedIllegalVector : 1,
        IllegalRegisterAddress : 1,
        : 24;
    } __attribute__((packed));

    struct CMCIReg {
        u32 vector : 8,
        deliveryMode : 3,
        : 1,
        DeliveryStatus : 1, //bit 12
        : 3,
        Mask : 1,
        : 15;

    } __attribute__((packed));

    struct InterruptCommandReg {
        u32 vector : 8,
        deliveryMode : 3,
        DestinationMode : 1,
        DeliveryStatus : 1,
        : 1,
        level : 1,
        truggerMode : 1,
        : 2,
        destinationShorthand : 2,
        : 12;

    } __attribute__((packed));

    struct InterruptCommandReg0 {
u32:
        24,
        DestinationField : 8;

    } __attribute__((packed));

    struct TimerReg {
        u32 vector : 8,
        : 4,
        DeliveryStatus : 1,
        : 3,
        Mask : 1,
        timerMode : 2,
        : 13;
    } __attribute__((packed));

    struct ThermalSensorReg {
        u32 vector : 8,
        deliveryMode : 3,
        : 1,
        DeliveryStatus : 1, //bit 12
        : 3,
        Mask : 1,
        : 15;

    } __attribute__((packed));

    struct PerformanceMonitoringCountersReg {
        u32 vector : 8,
        deliveryMode : 3,
        : 1,
        DeliveryStatus : 1, //bit 12
        : 3,
        Mask : 1,
        : 15;

    } __attribute__((packed));

    struct LINT0Reg {
        u32 vector : 8,
        deliveryMode : 3,
        : 1,
        DeliveryStatus : 1, //bit 12
        InterruptInputPinPolarity : 1,
        RemoteIRR : 1,
        TriggerMode : 1,
        Mask : 1,
        : 15;

    } __attribute__((packed));

    struct LINT1Reg {
        u32 vector : 8,
        deliveryMode : 3,
        : 1,
        DeliveryStatus : 1, //bit 12
        InterruptInputPinPolarity : 1,
        RemoteIRR : 1,
        TriggerMode : 1,
        Mask : 1,
        : 15;

    } __attribute__((packed));

    struct ErrorReg {
        u32 vector : 8,
        : 4,
        DeliveryStatus : 1, //bit 12
        : 4,
        Mask : 1,
        : 15;

    } __attribute__((packed));
    
     struct DivideConfigurationReg {

            /**
             * 0X00: Divide by 2
             * 0X01: Divide by 4
             * 0X10: Divide by 8
             * 0X11: Divide by 16
             * 1X00: Divide by 32
             * 1X01: Divide by 64
             * 1X10: Divide by 128
             * 1X11: Divide by 1
             * X = not used
             */
            union {
                u32 value;

                struct {
                    u32 lowOrderBits : 2,
                    : 1,
                    highOrderBits : 1;
                };
            };

        }  __attribute__((packed));


private:

    struct Registers {
        ReservedReg;
        ReservedReg;

        struct {
            LocalAPICIDReg LocalAPICIDRegister;
        } __attribute__((aligned(16), packed));

        struct {
            LocalAPICVersionReg LocalAPICVersionRegister;
        } __attribute__((aligned(16), packed));

        ReservedReg
        ReservedReg
        ReservedReg
        ReservedReg
        struct {
            TaskPriorityReg TaskPriorityRegister;
        } __attribute__((aligned(16), packed));

        struct {
            ArbitrationPriorityReg ArbitrationPriorityRegister;
        } __attribute__((aligned(16), packed));

        struct {
            ProcessorPriorityReg ProcessorPriorityRegister;
        } __attribute__((aligned(16), packed));

        struct {
            /**
             * 10.8.5
Signaling Interrupt Servicing Completion
For all interrupts except those delivered with the NMI, SMI, INIT, ExtINT, the start-up, or INIT-Deassert delivery
mode, the interrupt handler must include a write to the end-of-interrupt (EOI) register (see Figure 10-21). This
write must occur at the end of the handler routine, sometime before the IRET instruction. This action indicates that
the servicing of the current interrupt is complete and the local APIC can issue the next interrupt from the ISR.
             */
            u32 EOIRegister;
            /**
             Upon receiving an EOI, the APIC clears the highest priority bit in the ISR and dispatches the next highest priority
interrupt to the processor. If the terminated interrupt was a level-triggered interrupt, the local APIC also sends an
end-of-interrupt message to all I/O APICs.
System software may prefer to direct EOIs to specific I/O APICs rather than having the local APIC send end-of-
interrupt messages to all I/O APICs.
Software can inhibit the broadcast of EOI message by setting bit 12 of the Spurious Interrupt Vector Register (see
Section 10.9). If this bit is set, a broadcast EOI is not generated on an EOI cycle even if the associated TMR bit indi-
cates that the current interrupt was level-triggered. The default value for the bit is 0, indicating that EOI broadcasts
are performed.
             * Bit 12 of the Spurious Interrupt Vector Register is reserved to 0 if the processor does not support suppression of
EOI broadcasts. Support for EOI-broadcast suppression is reported in bit 24 in the Local APIC Version Register (see
Section 10.4.8); the feature is supported if that bit is set to 1. When supported, the feature is available in both
xAPIC mode and x2APIC mode.
System software desiring to perform directed EOIs for level-triggered interrupts should set bit 12 of the Spurious
Interrupt Vector Register and follow each the EOI to the local xAPIC for a level triggered interrupt with a directed
EOI to the I/O APIC generating the interrupt (this is done by writing to the I/O APIC’s EOI register). System soft-
ware performing directed EOIs must retain a mapping associating level-triggered interrupts with the I/O APICs in
the system.
             */

        } __attribute__((aligned(16), packed));

        struct {
            u32 RemoteReadReg; //Remote Read Register
        } __attribute__((aligned(16), packed));

        struct {
            LogicalDestinationReg LogicalDestinationRegister;
        } __attribute__((aligned(16), packed));

        struct {
            DestinationFormatReg DestinationFormatRegister;
            //Flat model: 1111B
            //Cluster model: 0000B
        } __attribute__((aligned(16), packed));

        struct {
            SpuriousInterruptVectorReg SpuriousInterruptVectorRegister;
        } __attribute__((aligned(16), packed));

        struct {
u16:
            16;
            u16 ISR_Bits15to31;
        } __attribute__((aligned(16), packed));

        struct {
            u32 ISR_Bits32to63;
        } __attribute__((aligned(16), packed));

        struct {
            u32 ISR_Bits64to95;
        } __attribute__((aligned(16), packed));

        struct {
            u32 ISR_Bits96to127;
        } __attribute__((aligned(16), packed));

        struct {
            u32 ISR_Bits128to159;
        } __attribute__((aligned(16), packed));

        struct {
            u32 ISR_Bits160to191;
        } __attribute__((aligned(16), packed));

        struct {
            u32 ISR_Bits192to233;
        } __attribute__((aligned(16), packed));

        struct {
            u32 ISR_Bits224to255;
        } __attribute__((aligned(16), packed));

        struct {
u16:
            16;
            u16 TMR_Bits15to31;
        } __attribute__((aligned(16), packed));

        struct {
            u32 TMR_Bits32to63;
        } __attribute__((aligned(16), packed));

        struct {
            u32 TMR_Bits64to95;
        } __attribute__((aligned(16), packed));

        struct {
            u32 TMR_Bits96to127;
        } __attribute__((aligned(16), packed));

        struct {
            u32 TMR_Bits128to159;
        } __attribute__((aligned(16), packed));

        struct {
            u32 TMR_Bits160to191;
        } __attribute__((aligned(16), packed));

        struct {
            u32 TMR_Bits192to233;
        } __attribute__((aligned(16), packed));

        struct {
            u32 TMR_Bits224to255;
        } __attribute__((aligned(16), packed));

        struct {
u16:
            16;
            u16 IRR_Bits15to31;
        } __attribute__((aligned(16), packed));

        struct {
            u32 IRR_Bits32to63;
        } __attribute__((aligned(16), packed));

        struct {
            u32 IRR_Bits64to95;
        } __attribute__((aligned(16), packed));

        struct {
            u32 IRR_Bits96to127;
        } __attribute__((aligned(16), packed));

        struct {
            u32 IRR_Bits128to159;
        } __attribute__((aligned(16), packed));

        struct {
            u32 IRR_Bits160to191;
        } __attribute__((aligned(16), packed));

        struct {
            u32 IRR_Bits192to233;
        } __attribute__((aligned(16), packed));

        struct {
            u32 IRR_Bits224to255;
        } __attribute__((aligned(16), packed));

        struct {
            ErrorStatusReg ErrorStatusRegister;
        } __attribute__((aligned(16), packed));

        ReservedReg
        ReservedReg
        ReservedReg
        ReservedReg
        ReservedReg
        ReservedReg

        struct {
            CMCIReg CMCIRegister;
        } __attribute__((aligned(16), packed));

        struct {
            InterruptCommandReg InterruptCommandRegister;
        } __attribute__((aligned(16), packed));

        struct {
            InterruptCommandReg0 InterruptCommandRegister0;
        } __attribute__((aligned(16), packed));

        struct {
            TimerReg TimerRegister;
        } __attribute__((aligned(16), packed));

        struct {
            ThermalSensorReg ThermalSensorRegister;
        } __attribute__((aligned(16), packed));

        struct {
            PerformanceMonitoringCountersReg PerformanceMonitoringCountersRegister;
        } __attribute__((aligned(16), packed));

        struct {
            LINT0Reg LINT0Register;
        } __attribute__((aligned(16), packed));

        struct {
            LINT1Reg LINT1Register;
        } __attribute__((aligned(16), packed));

        struct {
            ErrorReg ErrorRegister;

        } __attribute__((aligned(16), packed));

        struct {
            u32 InitialCountRegister;
        } __attribute__((aligned(16), packed));

        struct {
            u32 CurrentCountRegister;
        } __attribute__((aligned(16), packed));

        ReservedReg
        ReservedReg
        ReservedReg
        ReservedReg

        struct {
          DivideConfigurationReg DivideConfigurationRegister;
        } __attribute__((aligned(16), packed));

        ReservedReg
    } __attribute__((packed));

    static Registers *apicRegisters;
    static processor::MSR modelSpecificReg;




};

#endif /* APIC_H */

