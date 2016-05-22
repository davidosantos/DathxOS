;[BITS 32]
;This File Contains interrups addresses
section .text
align 4

[EXTERN IntsReturnTaskSwitch]
;u32 eax, ecx, edx, ebx, esp, ebp, esi, edi;
[EXTERN eipReg]
[EXTERN eaxReg]
[EXTERN ecxReg]
[EXTERN edxReg]
[EXTERN ebxReg]
[EXTERN espReg]
[EXTERN ebpReg]
[EXTERN esiReg]
[EXTERN ediReg]
[EXTERN eflags]
[EXTERN ssReg]
[EXTERN csReg]
[EXTERN dsReg]
[EXTERN esReg]
[EXTERN fsReg]
[EXTERN gsReg]
[EXTERN cr3Reg]
[EXTERN kerPageDir]

[EXTERN SyscallsDelivery]

[EXTERN Divideerror]

[EXTERN Debugexceptions]

[EXTERN Nonmaskableinterrupt]

[EXTERN Breakpoint]

[EXTERN Overflow]

[EXTERN Boundscheck]

[EXTERN Invalidopcode]

[EXTERN Coprocessornotavailable]

[EXTERN Doublefault]

[EXTERN reserved0]

[EXTERN InvalidTSS]
    
[EXTERN SystemError]
    
[EXTERN CoprecessorSegOverrun]

[EXTERN Segmentnotpresent]

[EXTERN Stackexception]

[EXTERN Generalprotection];

[EXTERN Pagefault]

[EXTERN reserved1]

[EXTERN Coprecessorerror]

[EXTERN reserved2]
    
[EXTERN HandlerIRQ00];

[EXTERN HandlerIRQ01]

[EXTERN HandlerIRQ02]

[EXTERN HandlerIRQ03]

[EXTERN HandlerIRQ04]

[EXTERN HandlerIRQ05]

[EXTERN HandlerIRQ06]

[EXTERN HandlerIRQ07]

[EXTERN HandlerIRQ08]

[EXTERN HandlerIRQ09]

[EXTERN HandlerIRQ10]

[EXTERN HandlerIRQ11]

[EXTERN HandlerIRQ12]

[EXTERN HandlerIRQ13]

[EXTERN HandlerIRQ14]

[EXTERN HandlerIRQ15]

%macro saveALL 0
;cli
pushad

%endmacro

%macro restoreALL 0
popad
;sti
%endmacro


%macro restoreTaskState 0
cld
mov dword ecx,[ecxReg]
mov dword edx,[edxReg]
mov dword ebx,[ebxReg]
mov dword esp,[espReg]
mov dword ebp,[ebpReg]
mov dword esi,[esiReg]
mov dword edi,[ediReg]

mov dword eax,[eflags]
push eax ; out eflags
mov eax,[csReg]
push eax ; code segment
mov dword eax,[eipReg]
push eax ; retun adress
mov word ax,[ssReg]
mov word ss,ax
mov word ax,[ssReg]
mov word ss,ax
mov word ax,[dsReg]
mov word ds,ax
mov word ax,[esReg]
mov word es,ax
mov word ax,[fsReg]
mov word fs,ax
mov word ax,[gsReg]
mov word gs,ax
mov dword eax,[cr3Reg]
mov dword cr3,eax
mov dword eax,[eaxReg]
%endmacro

%macro saveTaskState 0
cld
mov dword [eaxReg],eax
mov word ax,ss
mov word [ssReg],ax
mov word ax,ds
mov word [dsReg],ax
mov word ax,es
mov word [esReg],ax
mov word ax,fs
mov word [fsReg],ax
mov word ax,gs
mov word [gsReg],ax
pop eax, ;save return address
mov dword [eipReg],eax
pop eax ; code segment
mov dword [csReg],eax
pop eax ;eflags
mov dword [eflags],eax
mov dword [ecxReg],ecx
mov dword [edxReg],edx
mov dword [ebxReg],ebx
mov dword [espReg],esp
mov dword [ebpReg],ebp
mov dword [esiReg],esi
mov dword [ediReg],edi
mov dword eax,cr3
mov dword [cr3Reg],eax
%endmacro

[GLOBAL InternalInterrupt00]
[GLOBAL InternalInterrupt01]
[GLOBAL InternalInterrupt02]
[GLOBAL InternalInterrupt03]
[GLOBAL InternalInterrupt04]
[GLOBAL InternalInterrupt05]
[GLOBAL InternalInterrupt06]
[GLOBAL InternalInterrupt07]
[GLOBAL InternalInterrupt08]
[GLOBAL InternalInterrupt09]
[GLOBAL InternalInterrupt10]
[GLOBAL InternalInterrupt11]
[GLOBAL InternalInterrupt12]
[GLOBAL InternalInterrupt13]
[GLOBAL InternalInterrupt14]
[GLOBAL InternalInterrupt15]
[GLOBAL InternalInterrupt16]
[GLOBAL InternalInterrupt17]
[GLOBAL InternalInterrupt18]
[GLOBAL InternalInterrupt19]
[GLOBAL InternalInterrupt20]
[GLOBAL InternalInterrupt21]
[GLOBAL InternalInterrupt22]
[GLOBAL InternalInterrupt23]
[GLOBAL InternalInterrupt24]
[GLOBAL InternalInterrupt25]
[GLOBAL InternalInterrupt26]
[GLOBAL InternalInterrupt27]
[GLOBAL InternalInterrupt28]
[GLOBAL InternalInterrupt29]
[GLOBAL InternalInterrupt30]
[GLOBAL InternalInterrupt31]


[GLOBAL ExternalInterrupt00]
[GLOBAL ExternalInterrupt01]
[GLOBAL ExternalInterrupt02]
[GLOBAL ExternalInterrupt03]
[GLOBAL ExternalInterrupt04]
[GLOBAL ExternalInterrupt05]
[GLOBAL ExternalInterrupt06]
[GLOBAL ExternalInterrupt07]
[GLOBAL ExternalInterrupt08]
[GLOBAL ExternalInterrupt09]
[GLOBAL ExternalInterrupt10]
[GLOBAL ExternalInterrupt11]
[GLOBAL ExternalInterrupt12]
[GLOBAL ExternalInterrupt13]
[GLOBAL ExternalInterrupt14]
[GLOBAL ExternalInterrupt15]

InternalInterrupt00:
saveALL
call Divideerror
restoreALL
iretd
InternalInterrupt01:
saveALL
call Debugexceptions
restoreALL
iretd
InternalInterrupt02:
saveALL
call Nonmaskableinterrupt
restoreALL
iretd
InternalInterrupt03:
saveALL
call Breakpoint
restoreALL
iretd
InternalInterrupt04:
saveALL
call Overflow
restoreALL
iretd
InternalInterrupt05:
saveALL
call Boundscheck
restoreALL
iretd
InternalInterrupt06:
saveALL
call Invalidopcode
restoreALL
iretd
InternalInterrupt07:
saveALL
call Coprocessornotavailable
restoreALL
iretd
InternalInterrupt08:
saveALL
call Doublefault
restoreALL
iretd
InternalInterrupt09:
saveALL
call reserved0
restoreALL
iretd
InternalInterrupt10:
saveALL
call InvalidTSS
restoreALL
iretd
InternalInterrupt11:
saveALL
call Segmentnotpresent
restoreALL
iretd
InternalInterrupt12:
saveALL
call Stackexception
restoreALL
iretd
InternalInterrupt13:
cli
;mov     dword   [SavedErrorCode],esp  ;get error code address
;saveALL
;push    dword   [SavedErrorCode]
call Generalprotection
;restoreALL
iretd
InternalInterrupt14:
cli
mov     dword   [SavedErrorCode],esp  ;get error code address
saveALL
cld
mov     dword   eax,cr3
mov     dword   [SavedPageDir],eax
push    dword   [SavedPageDir]
push    dword   [SavedErrorCode]
call            Pagefault
pop     dword   eax ;remove arg1
pop     dword   eax ;remove arg2
pop     dword   eax ;remove erro code
restoreALL
iretd

InternalInterrupt15:
saveALL
call reserved1
restoreALL
iretd
InternalInterrupt16:
saveALL
call Coprecessorerror
restoreALL
iretd
InternalInterrupt17:
saveALL
call SystemError
restoreALL
iretd
InternalInterrupt18:
saveALL
call CoprecessorSegOverrun
restoreALL
iretd
InternalInterrupt19:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt20:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt21:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt22:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt23:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt24:

saveALL
call reserved2
restoreALL
iretd
InternalInterrupt25:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt26:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt27:
saveALL
call reserved2
restoreALL
iretd

InternalInterrupt28:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt29:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt30:
saveALL
call reserved2
restoreALL
iretd
InternalInterrupt31:
saveALL
call reserved2
restoreALL
iretd


ExternalInterrupt00:
cli  ;CPU Eflags will be restorned when iret executes
saveTaskState
call HandlerIRQ00
mov     dword   eax,[kerPageDir]
mov     dword   cr3,eax                     ;hangle task switch in kernel page dir
call IntsReturnTaskSwitch
restoreTaskState
iretd



ExternalInterrupt01:
saveALL
call HandlerIRQ01
restoreALL
iretd
ExternalInterrupt02:
saveALL
call HandlerIRQ02
restoreALL
iretd
ExternalInterrupt03:
saveALL
call HandlerIRQ03
restoreALL
iretd
ExternalInterrupt04:
saveALL
call HandlerIRQ04
restoreALL
iretd
ExternalInterrupt05:
saveALL
call HandlerIRQ05
restoreALL
iretd
ExternalInterrupt06:
saveALL
call HandlerIRQ06
restoreALL
iretd
ExternalInterrupt07:
saveALL
call HandlerIRQ07
restoreALL
iretd
ExternalInterrupt08:
saveALL
call HandlerIRQ08
restoreALL
iretd
ExternalInterrupt09:
saveALL
call HandlerIRQ09
restoreALL
iretd
ExternalInterrupt10:
saveALL
call HandlerIRQ10
restoreALL
iretd
ExternalInterrupt11:
saveALL
call HandlerIRQ11
restoreALL
iretd
ExternalInterrupt12:
saveALL
call HandlerIRQ12
restoreALL
iretd
ExternalInterrupt13:
saveALL
call HandlerIRQ13
restoreALL
iretd
ExternalInterrupt14:
saveALL
call HandlerIRQ14
restoreALL
iretd
ExternalInterrupt15:
saveALL
call HandlerIRQ15
restoreALL
iretd

[global Syscall0x80]
Syscall0x80:
saveALL
push dword eax ;paramater address of struct, not taking out might be problem
call SyscallsDelivery
pop dword eax
restoreALL
iretd

[global enablePageasm]
enablePageasm:
push dword eax 
mov  dword eax,cr3
;or eax, 0x80000000
bts   eax,31
mov  dword cr3,eax
pop dword eax
ret

;
;ExternalInterrupt17:
;saveALL
;call HandlerIRQ18
;restoreALL
;iretd
;ExternalInterrupt18:
;saveALL
;call HandlerIRQ19
;restoreALL
;iretd
;ExternalInterrupt19:
;saveALL
;call HandlerIRQ20
;restoreALL
;iretd
;ExternalInterrupt20:
;saveALL
;call HandlerIRQ21
;restoreALL
;iretd
;ExternalInterrupt21:
;saveALL
;call HandlerIRQ22
;restoreALL
;iretd
;ExternalInterrupt22:
;saveALL
;call HandlerIRQ23
;restoreALL
;iretd
;ExternalInterrupt23:
;saveALL
;call HandlerIRQ24
;restoreALL
;iretd
;ExternalInterrupt24:
;saveALL
;call HandlerIRQ25
;restoreALL
;iretd
;ExternalInterrupt25:
;saveALL
;call HandlerIRQ26
;restoreALL
;iretd
;ExternalInterrupt26:
;saveALL
;call HandlerIRQ27
;restoreALL
;iretd
;ExternalInterrupt27:
;saveALL
;call HandlerIRQ28
;restoreALL
;iretd
;ExternalInterrupt28:
;saveALL
;call HandlerIRQ29
;restoreALL
;iretd
;ExternalInterrupt29:
;saveALL
;call HandlerIRQ30
;restoreALL
;iretd
;ExternalInterrupt30:
;saveALL
;call HandlerIRQ31
;restoreALL
;iretd

section .data
align 4

SavedErrorCode dd 0
SavedPageDir dd 0