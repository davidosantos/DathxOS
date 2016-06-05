/* 
 * File:   processor.cpp
 * Author: david
 * 
 * Created on November 6, 2015, 11:29 PM
 */

#include "processor.h"

processor::processor() {
}

//processor::processor(const processor& orig) {
//}

//processor::~processor() {
//}


u8 processor::GDTInitDesc[6];
u32 processor::IDTInitDesc[48];

int processor::GDTCounter;
int processor::IDTCounter;
int processor::LDTCounter;

processor::TSSEntry *processor::TSS;
processor::TSSEntry *processor::TSSrng3;
processor::IDTEntry *processor::IDT;
processor::LDTEntry processor::LDT[8192];
processor::GDTEntry *processor::GDT;
processor::GDTPtr *processor::PointGDT;
processor::IDTPtr *processor::PointIDT;
processor::LDTPtr processor::PointLDT;

void processor::setupGDT() {
    cli();
    PointGDT = new GDTPtr();
    GDT = new GDTEntry [8192];

    GDTInitDesc[1] = prsnt_rng0_code_eo_naccssd;
    GDTInitDesc[2] = prsnt_rng0_data_rw_naccssd;
    GDTInitDesc[3] = prsnt_rng3_code_er_naccssd;
    GDTInitDesc[4] = prsnt_rng3_data_rw_naccssd;
    GDTInitDesc[5] = prsnt_rng0_code_eo_naccssd; //for interrupts


    for (u8 i = 1; i < 7; i++) {
        addGDTDesc(i, 0xFFFFFFFF, 0, GDTInitDesc[i], Flags_Granu_Big);
        GDTCounter++;
    }



    LGDT(PointGDT);

    asm("pushl %eax\n"
                "movl  	%cr0, %eax\n"
                "bts    $0, %eax\n"
                "movl  	%eax,%cr0\n"
                "ljmp   $0x08,$flush  \n"
                "flush:	\n"
                "movw	$0x10,%ax\n"
                "movw	%ax,%ds\n"
                "movw	%ax,%ss\n"
                "movw	%ax,%es\n"
                "movw	%ax,%gs\n"
                "movw	%ax,%fs\n"
                //"movl	$0X30000,%esp\n"
                //"movl	%%eax,%%esp\n"
                //"movw	$0x18,%ax\n"
                //"movw	%ax,%es\n"
                //"movw	$0x20,%ax\n"
                //"movw	%ax,%gs\n"
                //"movw	$0x28,%ax\n"
                //"movw	%ax,%fs\n"
                "popl   %eax\n");
}

void processor::setupIDT() {

    PointIDT = new IDTPtr();

    IDT = new IDTEntry [255];

    for (u32 i = 0; i < 256; i++) {
        //add for security reasons, some application may cause invalid interrupt
        //and crash the whole system.
        addIDTDesc((u32) & Syscall0x80, 0x8, intrrgt_rng0, i);


    }

    IDTInitDesc[0] = (u32) & InternalInterrupt00;
    IDTInitDesc[1] = (u32) & InternalInterrupt01;
    IDTInitDesc[2] = (u32) & InternalInterrupt02;
    IDTInitDesc[3] = (u32) & InternalInterrupt03;
    IDTInitDesc[4] = (u32) & InternalInterrupt04;
    IDTInitDesc[5] = (u32) & InternalInterrupt05;
    IDTInitDesc[6] = (u32) & InternalInterrupt06;
    IDTInitDesc[7] = (u32) & InternalInterrupt07;
    IDTInitDesc[8] = (u32) & InternalInterrupt08;
    IDTInitDesc[9] = (u32) & InternalInterrupt09;
    IDTInitDesc[10] = (u32) & InternalInterrupt10;
    IDTInitDesc[11] = (u32) & InternalInterrupt11;
    IDTInitDesc[12] = (u32) & InternalInterrupt12;
    IDTInitDesc[13] = (u32) & InternalInterrupt13;
    IDTInitDesc[14] = (u32) & InternalInterrupt14;
    IDTInitDesc[15] = (u32) & InternalInterrupt15;
    IDTInitDesc[16] = (u32) & InternalInterrupt16;
    IDTInitDesc[17] = (u32) & InternalInterrupt17;
    IDTInitDesc[18] = (u32) & InternalInterrupt18;
    IDTInitDesc[19] = (u32) & InternalInterrupt19;
    IDTInitDesc[20] = (u32) & InternalInterrupt20;
    IDTInitDesc[21] = (u32) & InternalInterrupt21;
    IDTInitDesc[22] = (u32) & InternalInterrupt22;
    IDTInitDesc[23] = (u32) & InternalInterrupt23;
    IDTInitDesc[24] = (u32) & InternalInterrupt24;
    IDTInitDesc[25] = (u32) & InternalInterrupt25;
    IDTInitDesc[26] = (u32) & InternalInterrupt26;
    IDTInitDesc[27] = (u32) & InternalInterrupt27;
    IDTInitDesc[28] = (u32) & InternalInterrupt28;
    IDTInitDesc[29] = (u32) & InternalInterrupt29;
    IDTInitDesc[30] = (u32) & InternalInterrupt30;
    IDTInitDesc[31] = (u32) & InternalInterrupt31;

    IDTInitDesc[32] = (u32) & ExternalInterrupt00;
    IDTInitDesc[33] = (u32) & ExternalInterrupt01;
    IDTInitDesc[34] = (u32) & ExternalInterrupt02;
    IDTInitDesc[35] = (u32) & ExternalInterrupt03;
    IDTInitDesc[36] = (u32) & ExternalInterrupt04;
    IDTInitDesc[37] = (u32) & ExternalInterrupt05;
    IDTInitDesc[38] = (u32) & ExternalInterrupt06;
    IDTInitDesc[39] = (u32) & ExternalInterrupt07;
    IDTInitDesc[40] = (u32) & ExternalInterrupt08;
    IDTInitDesc[41] = (u32) & ExternalInterrupt09;
    IDTInitDesc[42] = (u32) & ExternalInterrupt10;
    IDTInitDesc[43] = (u32) & ExternalInterrupt11;
    IDTInitDesc[44] = (u32) & ExternalInterrupt12;
    IDTInitDesc[45] = (u32) & ExternalInterrupt13;
    IDTInitDesc[46] = (u32) & ExternalInterrupt14;
    IDTInitDesc[47] = (u32) & ExternalInterrupt15;

    for (u32 i = 0; i < 47; i++) {

        addIDTDesc(IDTInitDesc[i], 0x28, intrrgt_rng0, i);


    }
    //adds system calls
    addIDTDesc((u32) & Syscall0x80, 0x8, intrrgt_rng3, 0x80);

    PointIDT->size = 255 * 8;
    LIDT(PointIDT);
}

void processor::setupLDT() {

}

void processor::setupTR() {
    TSS = new TSSEntry();
    TSSrng3 = new TSSEntry();

    u16 selr3 = addGDTDesc(sizeof (TSSEntry), (u32) TSSrng3, tss_p_rng3, Flags_Granu_Big);
    u16 sel = addGDTDesc(sizeof (TSSEntry), (u32) TSS, tss_p_rng0, Flags_Granu_Big);
    u32 callate = getGDTFreeEntry();
    addGDTDesc(callate, 0, makeSelector(selr3, false, 0), 0x85, 0); //call gate
    //link both
    TSS->prev_tss = makeSelector(selr3, false, 0) + 3;
    TSSrng3->prev_tss = makeSelector(sel, false, 0);
    LTR(makeSelector(sel, false, 0));
}

void processor::LGDT(GDTPtr *gdt) {
    gdt->size = GDTCounter * 8 - 1;
    gdt->addrs = GDT;

    asm("lgdt %0" ::"m" (*gdt));
}

void processor::LIDT(IDTPtr *idt) {
    idt->size = 255 * 8;
    idt->addrs = IDT;

    asm("lidt %0" ::"m" (*idt));
}

//void processor::LLDT(LDTPtr *ldt) {

//}

void processor::LTR(u16 Sel) {
    asm volatile("ltr %0" ::"r" (Sel));
}

u16 processor::STR() {
    u16 sel;
    asm("str %0" : "=m" (sel));
    return sel;
}

u16 processor::STRGDTIndex() {
    u16 sel;
    asm("str %0" : "=m" (sel));
    sel = (sel >> 3);
    return sel;
}

u16 processor::makeSelector(u32 selnumb, bool table, bool ring) {
    u16 Selector = (selnumb << 3);

    if (table) {
        Selector = (Selector + 4);
    }
    if (ring) {
        Selector = (Selector + 3);
    }

    return Selector;
}

/**
 * Adds a new data segment to the GDT and returns its selector
 * 
 * @param base Descriptor base 
 * @param limit Descriptor limit
 * @return Return a selector to the just added descriptor
 */
u16 processor::getNewDataSeg(u32 base, u32 limit) {
    return makeSelector(
            addGDTDesc(limit, base, prsnt_rng0_data_rw_naccssd, Flags_Granu_Big),
            false,
            false);
}

u16 processor::getNewCodeSeg(u32 base, u32 limit) {
    return makeSelector(
            addGDTDesc(limit, base, prsnt_rng0_code_eo_naccssd, Flags_Granu_Big),
            false,
            false);
}

/**
 *Get GDT free entry
 * 
 * 
 * @return Return index of free entry to be used with makeselector
 */
u16 processor::getGDTFreeEntry() {
    for (u32 i = 1; i < 8192; i++)
        if (GDT[i].type == 0) {
            GDTCounter++;
            return i;
        }
    return -1;
}

u16 processor::addGDTDesc(u32 limit, u32 base, u8 type, u8 flags) {
    u8 limitflag = 0;
    limitflag = ((limit >> 16 & 0x0F) | (flags & 0xF0)); //join
    u32 Entry = getGDTFreeEntry();
    GDT[Entry].base_31_24 = (base >> 24);
    GDT[Entry].base_23_16 = (base >> 16);
    GDT[Entry].base = base;
    GDT[Entry].type = type;
    GDT[Entry].limit = limit;
    GDT[Entry].flags = limitflag;
    GDTCounter++;
    LGDT(PointGDT);
    return Entry;
}

void processor::addGDTDesc(u16 entry, u32 limit, u32 base, u8 type, u8 flags) {
    u8 limitflag = 0;
    limitflag = ((limit >> 16 & 0x0F) | (flags & 0xF0)); //join
    u32 Entry = entry;
    GDT[Entry].base_31_24 = (base >> 24);
    GDT[Entry].base_23_16 = (base >> 16);
    GDT[Entry].base = base;
    GDT[Entry].type = type;
    GDT[Entry].limit = limit;
    GDT[Entry].flags = limitflag;

}

void processor::addIDTDesc(u32 base, u16 sel, u8 type, u32 Entry) {
    if (Entry <= 255) {
        IDT[Entry].offset_15_0 = (base >> 0);
        IDT[Entry].selector = sel;
        IDT[Entry].undef = 0;
        IDT[Entry].type = type;
        IDT[Entry].offset_31_16 = (base >> 16);
    }
}

void processor::loadPDBR(Paging::PagesDir *Ptr) {
    asm ("movl %0,%%cr3 " ::"r" (Ptr));

}

void processor::enablePaging() {

    asm("pushl %eax\n"
                "pushl %ebp\n"
                "movl  	%esp, %ebp\n"
                "movl  	%cr0, %eax\n"
                "bts    $31, %eax\n"
                "movl  	%eax,%cr0\n"
                "movl  	%ebp,%esp\n"
                "popl  	%ebp\n"
                "popl  	%eax\n"
                "ljmp   $0x08,$flushp  \n"
                "flushp:	\n"
                );

}

u32 processor::getPDBR() {
    u32 value;
    asm ("movl %%cr3,%0 " : "=r" (value));
    return value;
}

u32 processor::getCR2() {
    u32 value;
    asm ("movl %%cr2,%0 " : "=r" (value));
    return value;
}

u32 processor::getSIDT() {
    u32 value = 0;
    asm ("sidt %0 " : "=m" (value));
    return value;
}

u32 processor::getSGDT() {
    u32 value = 0;
    asm ("sgdt %0 " : "=m" (value));
    return value;
}

u32 processor::getSLDT() {
    u32 value = 0;
    asm ("sldt %0 " : "=m" (value));
    return value;
}

u16 processor::getRng0Code() {
    return makeSelector(1, false, 0);
}

u16 processor::getRng0Data() {
    return makeSelector(2, false, 0);
}

u16 processor::getRng3Code() {
    return makeSelector(3, false, 3);
}

u16 processor::getRng3Data() {
    return makeSelector(4, false, 3);
}

void processor::cli() {
    asm("cli");
}

void processor::sti() {
    asm("sti");
}

void processor::Set_NT() {

    asm ("pushf; orl  $0x00004000, (%esp); popf;");

}

void processor::Set_Trap() {

    asm ("pushf; orl  $0x00000100, (%esp); popf;");

}

void processor::Clear_NT() {

    asm ("pushf; andl $0xffffbfff, (%esp); popf;");

}

processor::CPUString processor::getCPUString() {
    CPUString cpustr;
    asm ("cpuid;"
                : "=a"(cpustr.EAX), "=b"(cpustr.EBX), "=c"(cpustr.ECX), "=d"(cpustr.EDX) /* output */
                : "a"(getString) /* input */
                );
    cpustr.String[4 * 3] = 0; //Null Terminated String
    return cpustr;
}

processor::CPUFeatures processor::getCPUFeatures() {
    CPUFeatures cpusig;
    asm ("cpuid;"
                : "=a"(cpusig.EAX), "=b"(cpusig.EBX), "=c"(cpusig.ECX), "=d"(cpusig.EDX) /* output */
                : "a"(ProcessorSignature) /* input */
                );
    return cpusig
            ;
}

processor::CPUBrandString processor::getCPUBrandString(CPUFeatures *features) {

    //To use the brand string method, execute CPUID with EAX input of 8000002H through 80000004H. For each input
    //value, CPUID returns 16 ASCII characters using EAX, EBX, ECX, and EDX. The returned string will be NULL-termi-nated.

    //Starting with processor signature family ID = 0FH, model = 03H, brand
    //index method is no longer supported. Use brand string method instead.

    CPUBrandString brandStr;
    for (int i = 0; i < (3 * 4 * 4); i++) {
        brandStr.String[i] = 0; //clear
    }

    if (features->BrandId == 0) {
        u8 regsIndex = 0;
        for (u32 command = getStringEx; command <= 0x80000004; command++) {
            asm ("cpuid;"
                        : /* output */
                        "=a"(brandStr.regs[regsIndex].EAX),
                        "=b"(brandStr.regs[regsIndex].EBX),
                        "=c"(brandStr.regs[regsIndex].ECX),
                        "=d"(brandStr.regs[regsIndex].EDX)
                        : "a"(command) /* input */
                        );
            regsIndex++;
        }

    } else {
        switch (features->BrandId) {

        }
    }
    return brandStr;
}

cs8 *processor::getTypeStr(s8 type) {
    switch (type) {
        case 0:
            return "Original OEM Processor";
        case 1:
            return "Intel OverDrive Processor";
        case 2:
            return "Dual processor";
        case 3:
            return "Intel reserved";
        default:
            return "";
    }
}

bool processor::getModelSpecificReg(CPUFeatures *features, MSR *to, u32 base) {
    if (features->MSR == 1) {
        asm volatile("rdmsr" : "=a"(to->low), "=d"(to->high) : "c"(base));
        return true;
        // asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
    } else {
        return false;
    }
    return false;
}

bool processor::setModelSpecificReg(CPUFeatures *features, MSR *to, u32 base) {
    if (features->MSR == 1) {
        asm volatile("wrmsr" : "=a"(to->low), "=d"(to->high) : "c"(base));
        return true;
    } else {
        return false;
    }
    return false;
}

/**
 * 
 * @param oldeFlags
 * @param oldCS
 * @param oldEIP
 */
extern "C" void Divideerror() {
Begin:
    ;
    const u8 msg[] = {"Devide error"};

    u8* videoPtr = (u8*) 0xB8200;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    goto Begin;
}

extern "C" void Debugexceptions() {
Begin:
    ;
    const u8 msg[] = {"Debugexceptions"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

extern "C" void Nonmaskableinterrupt() {
Begin:
    ;
    const u8 msg[] = {"Nonmaskableinterrupt"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

extern "C" void Breakpoint() {

Begin:
    ;
    const u8 msg[] = {"Breakpoint"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    goto Begin;
}

extern "C" void Overflow() {
Begin:
    ;
    const u8 msg[] = {"Overflow"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

extern "C" void Boundscheck() {
Begin:
    ;
    const u8 msg[] = {"Boundscheck"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

extern "C" void Invalidopcode() {
Begin:
    ;

    const u8 msg[] = {"Invalidopcode"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    goto Begin;
}

extern "C" void Coprocessornotavailable() {
Begin:
    ;

    const u8 msg[] = {"Coprocessornotavailable"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }
    asm("iret");
    goto Begin;
}

extern "C" void Doublefault() {
    //    autoCheck::runCheck();
Begin:
    ;

    const u8 msg[] = {"Doublefault"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    goto Begin;
}

extern "C" void reserved0() {

Begin:
    ;
    const u8 msg[] = {"reserved0"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    goto Begin;
}

extern "C" void InvalidTSS(processor::ErroCode errorCode, u32 oldEIP, u32 oldCS, u32 oldEFLAGS, u32 oldEIP2, u32 oldCS2, u32 oldEFLAGS2) {
Begin:
    ;

    Console::print("InvalidTSS, Event was: %s", errorCode.External == 1 ? "External" : "Internal");
    if (errorCode.InterruptTable == 1) {
        Console::print("Gate of IDT: %i", errorCode.Index);
    } else {
        if (errorCode.GDTorLDT == 0) {
            Console::print("Gate of GDT: %i", errorCode.Index);
            Console::print("Gate of GDT: %h", errorCode.Index * 8);
        } else {
            Console::print("Gate of LDT: %i", errorCode.Index);
        }
    }

    Console::print("InvalidTSS oldEIP %h", oldEIP);
    Console::print("InvalidTSS oldCS %h", oldCS);
    Console::print("InvalidTSS oldEFLAGS %h", oldEFLAGS);
    Console::print("InvalidTSS oldEIP2 %h", oldEIP2);
    Console::print("InvalidTSS oldCS2 %h", oldCS2);
    Console::print("InvalidTSS oldEFLAGS2 %h", oldEFLAGS2);




    //    GDT[40].type = tss_p_rng0;
    asm("hlt");
    goto Begin;
}

extern "C" void Segmentnotpresent() {
Begin:
    ;
    const u8 msg[] = {"Segmentnotpresent"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

extern "C" void Stackexception() {
Begin:
    ;
    const u8 msg[] = {"Stackexception"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

extern "C" void Generalprotection(processor::ErroCode errorCode, u32 oldEIP, u32 oldCS, u32 oldEFLAGS, u32 oldESP, u32 oldSS ) {
    //    autoCheck::runCheck();
//Begin:
    ;



    Console::print("General Protection, Event was: %s", errorCode.External == 1 ? "External" : "Internal");
    if (errorCode.InterruptTable == 1) {
        Console::print("Gate of IDT: %i", errorCode.Index);
    } else {
        if (errorCode.GDTorLDT == 0) {
            Console::print("Gate of GDT: %i", errorCode.Index);
            Console::print("Gate of GDT: %h", errorCode.Index * 8);
        } else {
            Console::print("Gate of LDT: %i", errorCode.Index);
        }
    }

    Console::print("General Protection errorCode %h", errorCode.cause);
    Console::print("General Protection oldEIP %h", oldEIP);
    Console::print("General Protection oldCS %h", oldCS);
    Console::print("General Protection oldEFLAGS %h", oldEFLAGS);
    Console::print("General Protection oldESP %h", oldESP);
    Console::print("General Protection oldSS %h", oldSS);

    asm("cli");
    
    while(true){}
    
    //asm("hlt");
    //asm("hlt");
    //GDT[7].type = tss_p_rng0;
    //asm("lcall $56,$0");
    //goto Begin;
}

#include "memory/Paging.h"

static u32 pageFaults = 0;

extern "C" void Pagefault(processor::PageFaultErroCode *pageFault, Paging::PagesDir *ppageDir) {

    pageFaults++;

    //Console::clear();
    Console::print(1, 0, "Page fault due to:");
    Console::print(3, 0, "cause %h", pageFault->cause);
    if (pageFault->Present == 1) Console::print(5, 0, "Present");
    if (pageFault->Write == 1) Console::print(7, 0, "Write");
    else Console::print(7, 0, "read");
    if (pageFault->User == 1) Console::print(9, 0, "User");
    if (pageFault->InstructionFecth == 1) Console::print(11, 0, "InstructionFecth");
    if (pageFault->SGX == 1) Console::print(13, 0, "SGX");
    if (pageFault->ReservedWrite == 1) Console::print(15, 0, "ReservedWrite");
    if (pageFault->Reserved) Console::print(17, 0, "pageFault.Reserved %i", pageFault->Reserved);

    u32 faultAdress = processor::getCR2();
    u32 *physAddress = Paging::getNewPage();
    Console::print(19, 0, "Linear Address: %h", (u32) faultAdress);
    Console::print(21, 0, "physAddress: %h", (u32) physAddress);
    Console::print(23, 0, "ppageDir: %h", (u32) ppageDir);
    Console::print(27, 0, "pageFaults: %i", pageFaults);


    Paging::mapRange(faultAdress, faultAdress,
            ppageDir, physAddress, false);


    //
    //    switch (pageFault.cause) {
    //        case 0:
    //            Console::print("Supervisory process tried to read a non-present page entry");
    //            break;
    //        case 1:
    //            Console::print("Supervisory process tried to read a page and caused a protection");
    //            break;
    //        case 2:
    //            Console::print("Supervisory process tried to write to a non-present page entry");
    //            break;
    //        case 3:
    //            Console::print("Supervisory process tried to write a page and caused a protection");
    //            break;
    //        case 4:
    //            Console::print("User process tried to read a non-present page entry");
    //            break;
    //        case 5:
    //            Console::print("User process tried to read a page and caused a protection fault");
    //            break;
    //        case 6:
    //            Console::print("User process tried to write to a non-present page entry");
    //            break;
    //        case 7:
    //            Console::print("User process tried to write a page and caused a protection fault");
    //            break;
    //
    //        default:
    //            Console::print("Unknown");
    //    }
    //    u32 value;
    //
    //    asm ("movl %%cr3,%0 " : "=r" (value));
    //    Console::print("cr3: %h", value);
    //
    //    // Paging::PagesDir *ppageDir = (Paging::PagesDir*)value;
    //
    //    for (u32 i = 0; i < 1024; i++) {
    //        // Paging::PagesTable *ppageTable = (Paging::PagesTable*) (ppageDir->dir.pageDir[i].phys * 4096);
    //
    //        for (u32 j = 0; j < 1024; j++) {
    //            // if(ppageTable->page[j].Present == 0){
    //            Console::print("Page Table %i is off", j);
    //            Console::print("of Page Dir %i ", i);
    //            //     Console::print("Page Table is at %h ",(u32)ppageTable);
    //
    //            // }
    //        }
    //    }
    //
    //
    //

    //autoCheck::runCheck();
    // while (true) {
    //}


}

extern "C" void reserved1() {
Begin:
    ;
    const u8 msg[] = {"reserved1"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

extern "C" void Coprecessorerror() {
Begin:
    ;

    const u8 msg[] = {"Coprecessorerror"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    goto Begin;
}

extern "C" void SystemError() {
Begin:
    const u8 msg[] = {"System error"};

    u8* videoPtr = (u8*) 0xB8200;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    //asm volatile("iret");
    goto Begin;
}

extern "C" void CoprecessorSegOverrun() {
    const u8 msg[] = {"Copro overrun"};
Begin:
    u8* videoPtr = (u8*) 0xB8200;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }

    //asm volatile("iret");
    goto Begin;
}

extern "C" void reserved2() {

Begin:
    ;
    const u8 msg[] = {"reserved2"};

    u8* videoPtr = (u8*) 0xB8000;

    for (u32 i = 0; i < sizeof msg; i++) {

        *videoPtr++ = msg[i];
        *videoPtr++ = 15;
    }


    goto Begin;
}

