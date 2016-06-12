;This application will check whether register has been wrongly changed during
;task switches 
section .text
global StartProgram:function
Start:
    mov dword eax,255
    mov dword ebx,255
    mov dword ecx,255
    mov dword edx,255
    mov dword ebp,255
    mov dword esp,255
    mov dword esi,255
    mov dword edi,255
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
    jne callTointeax
    cmp ebx,[ebxReg]
    jne callTointebx
    cmp ecx,[ecxReg]
    jne callTointecx
    cmp edx,[edxReg]
    jne callTointedx
    cmp ebp,[ebpReg]
    jne callTointebp
    cmp esp,[espReg]
    jne callTointesp
    cmp esi,[esiReg]
    jne callTointesi
    cmp edi,[ediReg]
    jne callTointedi
    jmp continue


    callTointeax:
    mov dword eax,0x01    ;funcion number
    int 0x80
    callTointebx:
    mov dword eax,0x02    ;funcion number
    int 0x80
    callTointecx:
    mov dword eax,0x03    ;funcion number
    int 0x80
    callTointedx:
    mov dword eax,0x04    ;funcion number
    int 0x80
    callTointebp:
    mov dword eax,0x05    ;funcion number
    int 0x80
    callTointesp:
    mov dword eax,0x06    ;funcion number
    int 0x80
    callTointesi:
    mov dword eax,0x07    ;funcion number
    int 0x80
    callTointedi:
    mov dword eax,0x08    ;funcion number
    
    
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




