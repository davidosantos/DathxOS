/* 
 * File:   processor.h
 * Author: david
 *
 * Created on November 6, 2015, 11:29 PM
 */

#ifndef PROCESSOR_H
#define	PROCESSOR_H
#include "../util/util.h"
#include "monitor/Console.h"
#include "memory/Paging.h"
#include "memory/Memory.h"
#include "autoCheck.h"

#define prsnt_rng0_data_r0_naccssd 0x90	//present, ring 0, data, read only, not accessed. generate this binary 	10010000
#define prsnt_rng0_data_rw_naccssd 0x92	//;present, ring 0, data, read/wright, not accessed. generate this binary 	10010010
#define prsnt_rng0_stck_r0_naccssd 0x94	//;present, ring 0, stack, read only, not accessed. generate this binary 	10010100
#define prsnt_rng0_stck_rw_naccssd 0x96	//;present, ring 0, stack, read/wright, not accessed. generate this binary 10010110
#define prsnt_rng0_code_e0_naccssd 0x98	//;present, ring 0, code, exec only, not accessed. generate this binary 	10011000
#define prsnt_rng0_code_er_naccssd 0x9a	//;present, ring 0, code, exec read, not accessed. generate this binary 	10011010
#define prsnt_rng0_code_e0_naccssd_c 0x9c	//;present, ring 0, code, exec only, not accessed, conforming.  			10011100
#define prsnt_rng0_code_er_naccssd_c 0x9e	//;present, ring 0, code, exec read, not accessed, conforming.  			10011110
#define intrrgt_rng0 0x8e
#define tss_p_rng0 0x89			  //;tss ring 0//////////
#define tskgt_rng0 0x85				//;task gate ring 0
#define tskgt_rng0 0x85				//;task gate ring 0
#define Flags_Granu_Big 0xc0

extern "C" void InternalInterrupt00();
extern "C" void InternalInterrupt01();
extern "C" void InternalInterrupt02();
extern "C" void InternalInterrupt03();
extern "C" void InternalInterrupt04();
extern "C" void InternalInterrupt05();
extern "C" void InternalInterrupt06();
extern "C" void InternalInterrupt07();
extern "C" void InternalInterrupt08();
extern "C" void InternalInterrupt09();
extern "C" void InternalInterrupt10();
extern "C" void InternalInterrupt11();
extern "C" void InternalInterrupt12();
extern "C" void InternalInterrupt13();
extern "C" void InternalInterrupt14();
extern "C" void InternalInterrupt15();
extern "C" void InternalInterrupt16();
extern "C" void InternalInterrupt17();
extern "C" void InternalInterrupt18();
extern "C" void InternalInterrupt19();
extern "C" void InternalInterrupt20();
extern "C" void InternalInterrupt21();
extern "C" void InternalInterrupt22();
extern "C" void InternalInterrupt23();
extern "C" void InternalInterrupt24();
extern "C" void InternalInterrupt25();
extern "C" void InternalInterrupt26();
extern "C" void InternalInterrupt27();
extern "C" void InternalInterrupt28();
extern "C" void InternalInterrupt29();
extern "C" void InternalInterrupt30();
extern "C" void InternalInterrupt31();

extern "C" void ExternalInterrupt00();
extern "C" void ExternalInterrupt01();
extern "C" void ExternalInterrupt02();
extern "C" void ExternalInterrupt03();
extern "C" void ExternalInterrupt04();
extern "C" void ExternalInterrupt05();
extern "C" void ExternalInterrupt06();
extern "C" void ExternalInterrupt07();
extern "C" void ExternalInterrupt08();
extern "C" void ExternalInterrupt09();
extern "C" void ExternalInterrupt10();
extern "C" void ExternalInterrupt11();
extern "C" void ExternalInterrupt12();
extern "C" void ExternalInterrupt13();
extern "C" void ExternalInterrupt14();
extern "C" void ExternalInterrupt15();
extern "C" void Syscall0x80();

class processor {
public:
    processor();
    // processor(const processor& orig);
    // virtual ~processor();

public:
    static void enablePaging();

    static void loadPDBR(Paging::PagesDir *Ptr);

    static u32 getPDBR();

    static u32 getSIDT();
    static u32 getSGDT();
    static u32 getSLDT();

    static void Set_NT();

    static void Set_Trap();

    static void Clear_NT();

    static u16 getNewDataSeg(u32 base, u32 limit);

    static u16 getNewCodeSeg(u32 base, u32 limit);

    static void setupGDT();
    static void setupIDT();
    static void setupLDT();

    static void inline cli();

    static void inline sti();

    struct GDTEntry {
        u16 limit;
        u16 base;
        u8 base_23_16;
        u8 type;
        u8 flags;
        u8 base_31_24;
    } __attribute__((packed));




public:

    struct IDTEntry {
        u16 offset_15_0;
        u16 selector;
        u8 undef;
        u8 type;
        u16 offset_31_16;
    } __attribute__((packed));

    struct LDTEntry {
        u16 limit;
        u16 base;
        u8 base_23_16;
        u8 type;
        u8 flags;
        u8 base_31_24;
    } __attribute__((packed));

    struct GDTPtr {
        u16 size;
        GDTEntry *addrs;
    } __attribute__((packed));

    struct IDTPtr {
        u16 size;
        IDTEntry *addrs;
    } __attribute__((packed));

    struct LDTPtr {
        u16 size;
        LDTEntry addrs;
    } __attribute__((packed));

    static GDTPtr *PointGDT;
    static IDTPtr *PointIDT;
    static LDTPtr PointLDT;

    static void LGDT(GDTPtr *gdt);

    static void LIDT(IDTPtr *idt);

    static void LLDT(LDTPtr *ldt);

    static void LTR(u16 Sel);

    u16 STR();

    u16 STRGDTIndex();


    static IDTEntry *IDT;
    static LDTEntry LDT[8192];
    static GDTEntry *GDT;

    static const GDTEntry *getGDTEntry();

    IDTEntry getIDT();

    static int GDTCounter;
    static int IDTCounter;
    static int LDTCounter;

    static u16 makeSelector(u32 selnumb, bool table, bool ring);

    static u16 getGDTFreeEntry();

    static u16 addGDTDesc(u32 limit, u32 base, u8 type, u8 flags);

    static void addGDTDesc(u16 entry, u32 limit, u32 base, u8 type, u8 flags);

    static void addIDTDesc(u32 base, u16 sel, u8 type, u32 Entry);

    static u8 GDTInitDesc[6];

    static u32 IDTInitDesc[48];

    typedef struct PageFaultErroCode {

        union {
            u32 cause : 3;

            struct {
                u32 Present : 1,
                Write : 1,
                User : 1,
                ReservedWrite : 1,
                InstructionFecth : 1,
                Reserved : 28;
            };
        };
    } _PageFaultErroCode;






#define getString 0x00
#define getStringEx 0x80000002
#define ProcessorSignature 0x01
#define CacheandTLBDescriptors 0x02
#define ProcessorSerialNumber 0x03
#define ProcessorSignatureEx 0x80000001
#define CacheandTLBDescriptorsEx 0x80000002
#define ProcessorSerialNumberEx 0x80000003

    struct CPUString {

        union {
            s8 String[4 * 3];

            struct {
                u32 EBX;
                u32 EDX;
                u32 ECX;
                u32 EAX;
            };
        };
    } __attribute__((packed));

    struct CPUBrandString {

        union {
            s8 String[3 * 4 * 4];

            struct {
                u32 EAX;
                u32 EBX;
                u32 ECX;
                u32 EDX;
            } regs[3];
        };
    } __attribute__((packed));

    struct CPUFeatures {

        union {

            struct {
                u32 EAX;
                u32 EBX;
                u32 ECX;
                u32 EDX;
            };

            struct {

                struct {
                    u32 SteppingId : 4,
                    ModelNumber : 4,
                    FamilyId : 4,
                    ProcessorType : 2,
                    : 2,
                    ExtendedModel : 4,
                    ExtendedFamily : 8,
                    : 4;
                };

                struct {
                    u32 BrandId : 8,
                    CLFLUSH : 8,
                    Count : 8,
                    ApicID : 8;
                };

                struct {
                    u32 SSE3 : 1,
                    PCLMUQDQ : 1,
                    DTES64 : 1,
                    MONITOR : 1,
                    DSCPL : 1,
                    VMX : 1,
                    SMX : 1,
                    EIST : 1,
                    TM2 : 1,
                    SSSE3 : 1,
                    CNXTID : 1,
                    SDBG : 1,
                    FMA : 1,
                    CMPX : 1,
                    xTPRUPDATE : 1,
                    PDCM : 1,
                    : 1,
                    PCID : 1,
                    DCA : 1,
                    SSE41 : 1,
                    SSE42 : 1,
                    x2APIC : 1,
                    MOVBE : 1,
                    POPCNT : 1,
                    TSCDeadline : 1,
                    AESNI : 1,
                    XSAVE : 1,
                    OSXSAVE : 1,
                    AVX : 1,
                    F16C : 1,
                    RDRAND : 1,
                    : 1;
                };

                struct {
                    u32
                    FPU : 1,
                    VME : 1,
                    DE : 1,
                    PSE : 1,
                    TSC : 1,
                    MSR : 1,
                    PAE : 1,
                    MCE : 1,
                    CX8 : 1,
                    APIC : 1,
                    : 1,
                    SEP : 1,
                    MTRR : 1,
                    PGE : 1,
                    MCA : 1,
                    CMOV : 1,
                    PAT : 1,
                    PSE36 : 1,
                    PSN : 1,
                    CLFSH : 1,
                    : 1,
                    DS : 1,
                    ACPI : 1,
                    MMX : 1,
                    FXSR : 1,
                    SSE : 1,
                    SSE2 : 1,
                    SS : 1,
                    HTT : 1,
                    TM : 1,
                    : 1,
                    PBE : 1;
                };
            };
        };
    } __attribute__((packed));



    static CPUString getCPUString();
    static CPUFeatures getCPUFeatures();
    static CPUBrandString getCPUBrandString(CPUFeatures *features);
    scs8 *getTypeStr(s8 type);

};

#endif	/* PROCESSOR_H */

