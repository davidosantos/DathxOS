
section .text
global StartProgram:function
Start:
    mov dword [eaxReg],eax
    mov dword [ebxReg],ebx
    mov dword [ecxReg],ecx
    mov dword [edxReg],edx
    mov dword [ebpReg],ebp
    mov dword [espReg],esp
    mov dword [esiReg],esi
    mov dword [ediReg],edi
    continue:
    cmp eax,[eaxReg]
    jne callToint
    cmp ebx,[ebxReg]
    jne callToint
    cmp ecx,[ecxReg]
    jne callToint
    cmp edx,[edxReg]
    jne callToint
    cmp ebp,[ebpReg]
    jne callToint
    cmp esp,[espReg]
    jne callToint
    cmp esi,[esiReg]
    jne callToint
    cmp edi,[ediReg]
    jne callToint
    jmp continue


    callToint:
    mov dword eax,0x03    ;funcion number
    int 0x80
    
    jmp Start

section .data

eaxReg dd 0
ebxReg dd 0
ecxReg dd 0
edxReg dd 0
espReg dd 0
ebpReg dd 0
esiReg dd 0
ediReg dd 0
;u32 eaxReg, ecxReg, edxReg, ebxReg, espReg, ebpReg, esiReg, ediReg, eflags, eipReg, csReg, cr3Reg;
;u16 ssReg, dsReg, esReg, fsReg, gsReg;
section .bss




