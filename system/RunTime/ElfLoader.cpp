/* 
 * File:   ElfLoader.cpp
 * Author: david
 * 
 * Created on 7 de Setembro de 2015, 14:44
 */

#include "ElfLoader.h"

ElfLoader::ElfLoader() {

}

returnCode ElfLoader::openFile(const s8 *fileName) {
    if (file.open(fileName) == OK) {
        u8 *elfHeader = new u8 [sizeof (Elf32_Ehdr)];
        if (file.read(0, sizeof (Elf32_Ehdr), elfHeader) == OK) {
            Header = (Elf32_Ehdr*) elfHeader;
            //            Console::print("elf %s", (s8*) Header->e_ident);
            //            Console::print("Version: %h", Header->e_version);
            //            Console::print("Type: %h", Header->e_type);
            //            Console::print("Machine: %h",Header->e_machine);
            //            Console::print("Entry point address: %h",Header->e_entry);
            //            Console::print("Start of program headers: %h",Header->e_phoff);
            //            Console::print("Start of section headers: %h",Header->e_shoff);
            //            Console::print("Size of this header: %h",Header->e_ehsize);
            //            Console::print("Number of program headers: %i",Header->e_phnum);
            //            Console::print("Size of section headers: %i",Header->e_shentsize);
            //            Console::print("Number of section headers: %i",Header->e_shnum);
            //            Console::print("Section header string table index: %i",Header->e_shstrndx);
            u8 *prHeader = new u8 [sizeof (Elf32_Phdr) * Header->e_phnum];
            if (file.read(Header->e_phoff, sizeof (Elf32_Phdr) * Header->e_phnum, prHeader) == OK) {
                pHeader = (Elf32_Phdr*) prHeader;

                //                Console::print("Type: %h",pHeader->p_type);
                //                Console::print("p_align: %h",pHeader->p_align);
                //                Console::print("p_filesz: %h",pHeader->p_filesz);
                //                Console::print("p_flags: %h",pHeader->p_flags);
                //                Console::print("p_memsz: %h",pHeader->p_memsz);
                //                Console::print("p_offset: %h",pHeader->p_offset);
                //                Console::print("p_paddr: %h",pHeader->p_paddr);
                //                Console::print("p_vaddr: %h",pHeader->p_vaddr);
            } else {
                return Error;
            }

            u8 *psHeader = new u8 [sizeof (Elf32_Shdr) * Header->e_shnum];
            if (file.read(Header->e_shoff, sizeof (Elf32_Shdr) * Header->e_shnum, psHeader) == OK) {
                sHeader = (Elf32_Shdr*) psHeader;

                //A section header’s sh_name member holds an index into the section header string table section, as desig-
                //nated by the e_shstrndx member of the ELF header.
                stringTable = new u8 [sHeader[Header->e_shstrndx].sh_size];
                if (file.read(sHeader[Header->e_shstrndx].sh_offset, sHeader[Header->e_shstrndx].sh_size, stringTable) == Error)
                    return Error;

                //                Console::print("sh_addr: %h", sHeader[15].sh_addr);
                //                Console::print("sh_addralign: %h", sHeader[15].sh_addralign);
                //                Console::print("sh_entsize: %h", sHeader[15].sh_entsize);
                //                Console::print("sh_flags: %h", sHeader[15].sh_flags);
                //                Console::print("sh_info: %h", sHeader[15].sh_info);
                //                Console::print("sh_link: %h", sHeader[15].sh_link);
                //                Console::print("sh_offset: %h", sHeader[15].sh_offset);
                //                Console::print("sh_size: %h", sHeader[15].sh_size);
                //                Console::print("sh_type: %h", sHeader[15].sh_type);
                //                Console::print("sh_name index: %h", sHeader[15].sh_name);
                //                Console::print("sh_name: %s", (s8*)stringTable+sHeader[15].sh_name);
                //               

            } else {
                return Error;
            }

        } else {
            return Error;
        }
        return OK;
    } else {
        return Error;
    }
}

/*
david@davidpc:~$ readelf -e '/home/david/.wine/CrossFireKernel.bin' 
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x100c04
  Start of program headers:          52 (bytes into file)
  Start of section headers:          172716 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         2
  Size of section headers:           40 (bytes)
  Number of section headers:         18
  Section header string table index: 15

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        00100000 001000 004b4c 00  AX  0   0 16
  [ 2] .eh_frame         PROGBITS        00104b4c 005b4c 002280 00   A  0   0  4
  [ 3] .rodata.str1.4    PROGBITS        00106dcc 007dcc 0000b8 01 AMS  0   0  4
  [ 4] .rodata.str1.1    PROGBITS        00106e84 007e84 0004b1 01 AMS  0   0  1
  [ 5] .data             PROGBITS        00107338 008338 000cc8 00  WA  0   0  4
  [ 6] .bss              NOBITS          00108000 009000 001000 00  WA  0   0 64
  [ 7] .debug_info       PROGBITS        00000000 009000 0131c6 00      0   0  1
  [ 8] .debug_abbrev     PROGBITS        00000000 01c1c6 00348e 00      0   0  1
  [ 9] .debug_loc        PROGBITS        00000000 01f654 002583 00      0   0  1
  [10] .debug_aranges    PROGBITS        00000000 021bd7 000220 00      0   0  1
  [11] .debug_line       PROGBITS        00000000 021df7 001c56 00      0   0  1
  [12] .debug_str        PROGBITS        00000000 023a4d 00380f 01  MS  0   0  1
  [13] .comment          PROGBITS        00000000 02725c 000025 01  MS  0   0  1
  [14] .debug_ranges     PROGBITS        00000000 027281 000160 00      0   0  1
  [15] .shstrtab         STRTAB          00000000 0273e1 0000b6 00      0   0  1
  [16] .symtab           SYMTAB          00000000 027498 001590 10     17  60  4
  [17] .strtab           STRTAB          00000000 028a28 001882 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x001000 0x00100000 0x00100000 0x08000 0x09000 RWE 0x1000
  GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RWE 0x10

 Section to Segment mapping:
  Segment Sections...
   00     .text .eh_frame .rodata.str1.4 .rodata.str1.1 .data .bss 
   01     

 */

returnCode ElfLoader::loadProgram() {
    Paging::PagesDir *pageDir = Paging::getNewDir();
    u8 *loadAddrs; // = (u32*) Paging::getNewPage();
    //Paging::mapRange(sHeader[i].sh_addr, sHeader[i].sh_size,pageDir,loadAddrs);

    loadAddrs = new u8 [pHeader[0].p_memsz];

    Console::print("pageDir %h", (u32) pageDir);
    Console::print("loadAddrs %h", (u32) loadAddrs);


    Paging::mapRange(0, 0x600000, pageDir, 0);

    Paging::mapRange(pHeader[0].p_vaddr, (pHeader[0].p_vaddr +
            pHeader[0].p_memsz), pageDir, (u32*) loadAddrs);
    //10000), pageDir, (u32*) loadAddrs);


    for (u8 i = 0; i < Header->e_shnum; i++) {

        if (sHeader[i].sh_type != 0 && (sHeader[i].sh_size != 0 && sHeader[i].sh_addr != 0)) {

            if (strcmp((const char*) (stringTable + sHeader[i].sh_name), ".bss")) {
                Console::print("section bss %i", i);
            } else {

                if (file.read(sHeader[i].sh_offset, sHeader[i].sh_size,
                        (u8*) Paging::getPhysAddrs((u32*) sHeader[i].sh_addr, pageDir)) == OK) {

                    //Console::print("section num %i", i);
                    //Console::print("Add at prog %h", sHeader[i].sh_addr);
                    //Console::print("Add at phys %h", (u32) Paging::getPhysAddrs((u32*)sHeader[i].sh_addr, pageDir));
                    //falta carregar
                } else {
                    return Error;
                }
            }
        }
    }

    u32 *stack = new u32 [100];

    Tasks::NewTask("File", Header->e_entry, pageDir, stack, 100);
    return OK;
}

//ElfLoader::ElfLoader(const ElfLoader& orig) {
//}
//
//ElfLoader::~ElfLoader() {
//}

