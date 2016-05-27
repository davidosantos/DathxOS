ENTRY(Start)
OUTPUT_FORMAT(elf32-i386)
phys = 0x00100000;
SECTIONS {
  .text phys : AT(phys) {
    Kernel_Code_Start = .;
    build/Debug/GNU-Linux/system/Start.o(.text)
    build/Debug/GNU-Linux/system/DathxMain.o(.text)
    intsStart = .;
    build/Debug/GNU-Linux/system/Interrupts.o(.text)
    intsEnd = .;
    *(.text)
    *(.rodata)
    *(.rodata.str1.1)
    *(.rodata.str1.4)
    *(.eh_frame)
    . = ALIGN(4k);
    Kernel_Code_End = .;
  }
   Kernel_Data_Start =  ( Kernel_Code_End +1);
  .data : AT(phys + Kernel_Data_Start)
  {
   
    *(.data)
    . = ALIGN(4K);  
    Kernel_Data_End = .;
  }
  Kernel_BSS_Start = (Kernel_Data_End +1);
  .bss : AT(phys + (Kernel_BSS_Start - Kernel_Code_Start))
  {
    *(.bss)
    . = ALIGN(4K);
    Kernel_BSS_End = .;
  }
  
}
