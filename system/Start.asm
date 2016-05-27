; Define some constants, just to make life easier for us
STACKSIZE           equ 40

MBOOT_PAGE_ALIGN    equ 1 << 0   ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1 << 1   ; Provide the kernel with memory info
;Not need for elf file, bacause elf contais headers with the same info
;MBOOT_MEM_MAP       equ 1 << 1   ; Provide the kernel with memory map info
;LOAD_ADDRESS        equ 1 << 16  ; Specify load address

MBOOT_HEADER_MAGIC  equ 0x1BADB002    ; Multiboot Magic value
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO  ;| MBOOT_MEM_MAP  |LOAD_ADDRESS 
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                     ; Tell NASM to output 32-bit code
[GLOBAL Multiboot]            ; This lets LD reorder the file to put
                              ; the Multiboot header at the start of our file
[GLOBAL Start]                ; The assembly entry point

[EXTERN Kernel_Code_Start]
[EXTERN Kernel_BSS_Start]
[EXTERN Kernel_BSS_End]                  ; This marks the end of the kernel
[EXTERN main]                 ; This is the C++ entry point. We have to call this manually
;[EXTERN LoadConstructors]     ; Called before Main(), this calls the global constructors


Multiboot:
  dd  MBOOT_HEADER_MAGIC     ; GRUB will search for this value
                             ; on each 4-byte boundary in the ELF file
  dd  MBOOT_HEADER_FLAGS
  dd  MBOOT_CHECKSUM         ; Ensures that the above values are correct
  
;Not need for elf file, bacause elf contais headers with the same info
  ;dd  Multiboot              ; Location of this section
  ;dd  Kernel_Code_Start                   ; Start of kernel '.text' (code) section
  ;dd  Kernel_BSS_Start                   ; End of kernel '.data' section
  ;dd  Kernel_BSS_End                    ; End of kernel
  ;dd  Start                    ; Kernel entry point (initial EIP)

Start:
    cli                       ; Disable interrupts.
    mov ebp,stackStart        ; setup a stack to this assemble code
    mov esp,stackEnd

    ;mov dword [saveEax],eax         ;save Magic code
    ;mov dword [saveEbx],ebx         ;Save multiboot header location 
 
    ;call LoadConstructors  ; Load global constructors
                           ; Parameters for the C++ entry point need to be pushed backwards
    ;mov dword ebx,[saveEbx]   ; Load multiboot header location
    ;mov dword eax,[saveEax]   ; Magic code
    call main              ; Invoke the Main() function
    jmp $                  ; Enter an infinite loop, to stop the processor
                           ; executing whatever rubbish is in the memory after the kernel
    
section .data
    saveEax dd 0
    saveEbx dd 0
section .bss
   
stackStart:
   resb STACKSIZE

stackEnd:
