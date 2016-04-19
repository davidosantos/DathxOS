/* 
 * File:   ElfLoader.h
 * Author: david
 *
 * Created on 7 de Setembro de 2015, 14:44
 */

#ifndef ELFLOADER_H
#define	ELFLOADER_H

#include "../../util/util.h"
#include "../fs/File.h"
#include "../Tasks/Tasks.h"

#define Elf32_Addr u32  //4 Unsigned program address
#define Elf32_Half u16 //2 Unsigned medium integer
#define Elf32_Off u32  //4Unsigned file offset
#define Elf32_Sword s32 //4 Signed large integer
#define Elf32_Word u32 //Unsigned large integer
#define EI_NIDENT 16

#define ET_NONE 0 //No file type
#define ET_REL 1 //Relocatable file
#define ET_EXEC 2 // Executable file
#define ET_DYN 3 // Shared object file
#define ET_CORE 4 //  Core file
#define ET_LOPROC 0xff00 // Processor-specific
#define ET_HIPROC 0xffff // Processor-specific

#define EM_NONE 0 //No machine
#define EM_M32 1 //AT&T WE 32100
#define EM_SPARC 2 // SPARC
#define EM_386 3 // Intel 80386
#define EM_68K 4 // Motorola 68000
#define EM_88K 5 // Motorola 88000
#define EM_860 7 // Intel 80860
#define EM_MIPS 8 //MIPS RS3000


#define EI_MAG0 0 //File identification
#define EI_MAG1 1 //File identification
#define EI_MAG2 2 //File identification
#define EI_MAG3 3 //File identification
#define EI_CLASS 4 //File class
#define EI_DATA 5 //Data encoding
#define EI_VERSION 6 //File version
#define EI_PAD 7 //Start of padding bytes
#define EI_NIDENT 16 //Size of e_ident[]

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define ELFCLASSNONE 0 //Invalid class
#define ELFCLASS32 1 //32-bit objects
#define ELFCLASS64 2 //64-bit objects


#define ELFDATANONE 0 
#define ELFDATA2LSB 1 
#define ELFDATA2MSB 2 //I'll use this first

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7fffffff

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_LOPROC 0x70000000 
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xffffffff

extern u32 totalMemoryAdress;

class ElfLoader {
public:

    typedef struct {
        unsigned char e_ident[EI_NIDENT];
        Elf32_Half e_type;
        Elf32_Half e_machine;
        Elf32_Word e_version;
        Elf32_Addr e_entry ; //This member gives the virtual address to which the system first transfers control, thus starting the process. If the file has no associated entry point, this member holds zero.
        Elf32_Off e_phoff;
        Elf32_Off e_shoff;
        Elf32_Word e_flags;
        Elf32_Half e_ehsize;
        Elf32_Half e_phentsize;
        Elf32_Half e_phnum;
        Elf32_Half e_shentsize;
        Elf32_Half e_shnum;
        Elf32_Half e_shstrndx;
    } Elf32_Ehdr;

    typedef struct {
        Elf32_Word p_type;
        Elf32_Off p_offset;
        Elf32_Addr p_vaddr;
        Elf32_Addr p_paddr;
        Elf32_Word p_filesz;
        Elf32_Word p_memsz;
        Elf32_Word p_flags;
        Elf32_Word p_align;
    } Elf32_Phdr;

    typedef struct {
        Elf32_Word sh_name;
        Elf32_Word sh_type;
        Elf32_Word sh_flags;
        Elf32_Addr sh_addr;
        Elf32_Off sh_offset;
        Elf32_Word sh_size;
        Elf32_Word sh_link;
        Elf32_Word sh_info;
        Elf32_Word sh_addralign;
        Elf32_Word sh_entsize;
    } Elf32_Shdr;


    File file;

    Elf32_Ehdr *Header __attribute__((packed));
    

    Elf32_Phdr *pHeader __attribute__((packed));
    
    Elf32_Shdr *sHeader __attribute__((packed));
    
    u8* stringTable;

    returnCode openFile(const s8 *fileName);

    returnCode loadProgram();


    ElfLoader();
    //    ElfLoader(const ElfLoader& orig);
    //    virtual ~ElfLoader();
private:

};

#endif	/* ELFLOADER_H */

