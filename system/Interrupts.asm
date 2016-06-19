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
pushad
mov     dword   eax,cr3
mov     dword   [SavedPageDirInts],eax
mov     dword   eax,[kerPageDir]
mov     dword   cr3,eax 
%endmacro

%macro toKernelPage 0
mov     dword   eax,cr3
mov     dword   [SavedPageDirInts],eax
mov     dword   eax,[kerPageDir]
mov     dword   cr3,eax 
%endmacro

%macro restoreALL 0
mov     dword   eax,[SavedPageDirInts]
mov     dword   cr3,eax
popad
%endmacro

%macro backFromKernelPage 0
mov     dword   eax,[SavedPageDirInts]
mov     dword   cr3,eax
%endmacro

%macro restoreTaskState 0
mov dword ecx,[ecxReg]
mov dword edx,[edxReg]
mov dword ebx,[ebxReg]
;mov dword esp,[espReg]
mov dword ebp,[ebpReg]
mov dword esi,[esiReg]
mov dword edi,[ediReg]

;mov word ax,[ssReg]  ; restored automatically
;mov word ss,ax
mov word ax,[dsReg]
mov word ds,ax
mov word ax,[esReg]
mov word es,ax
mov word ax,[fsReg]
mov word fs,ax
mov word ax,[gsReg]
mov word gs,ax

mov dword eax,0
mov word ax,[ssReg]
push eax        ; oldSS
mov dword eax,[espReg]
push eax        ; oldESP
mov dword eax,[eflags]
push eax        ; out eflags
mov eax,[csReg]
push eax        ; code segment
mov dword eax,[eipReg]
push eax        ; retun adress
mov dword eax,[cr3Reg]
mov dword cr3,eax
mov dword eax,[eaxReg]
%endmacro

%macro saveTaskState 0
mov dword [eaxReg],eax
mov dword [ebxReg],ebx
mov dword [ecxReg],ecx
mov dword [edxReg],edx
;mov dword [espReg],esp
mov dword [ebpReg],ebp
mov dword [esiReg],esi
mov dword [ediReg],edi

;mov word ax,ss
;mov word [ssReg],ax
mov word ax,ds
mov word [dsReg],ax
mov word ax,es
mov word [esReg],ax
mov word ax,fs
mov word [fsReg],ax
mov word ax,gs
mov word [gsReg],ax

pop eax,                ;save return address
mov dword [eipReg],eax
pop eax                 ; code segment
mov dword [csReg],eax
pop eax                 ;eflags
mov dword [eflags],eax
pop eax                 ;remove oldESP 
mov dword [espReg],eax
pop eax                 ;remove oldSS from stack 
mov word [ssReg],ax
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
mov     dword   eax,[kerPageDir]
mov     dword   cr3,eax                     ;hangle task switch in kernel page dir
call IntsReturnTaskSwitch
call HandlerIRQ00
restoreTaskState
iretd

ExternalInterrupt01:
saveTaskState
toKernelPage
call HandlerIRQ01
backFromKernelPage
restoreTaskState
iretd

ExternalInterrupt02:
saveTaskState
toKernelPage
call HandlerIRQ02
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt03:
saveTaskState
toKernelPage
call HandlerIRQ03
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt04:
saveTaskState
toKernelPage
call HandlerIRQ04
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt05:
saveTaskState
toKernelPage
call HandlerIRQ05
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt06:
saveTaskState
toKernelPage
call HandlerIRQ06
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt07:
saveTaskState
toKernelPage
call HandlerIRQ07
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt08:
saveTaskState
toKernelPage
call HandlerIRQ08
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt09:
saveTaskState
toKernelPage
call HandlerIRQ09
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt10:
saveTaskState
toKernelPage
call HandlerIRQ10
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt11:
saveTaskState
toKernelPage
call HandlerIRQ11
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt12:
saveTaskState
toKernelPage
call HandlerIRQ12
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt13:
saveTaskState
toKernelPage
call HandlerIRQ13
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt14:
saveTaskState
toKernelPage
call HandlerIRQ14
backFromKernelPage
restoreTaskState 
iretd

ExternalInterrupt15:
saveTaskState
toKernelPage
call HandlerIRQ15
backFromKernelPage
restoreTaskState 
iretd

[global Syscall0x80]
Syscall0x80:
mov dword [SavedSyscalParameter],eax 
pushad
mov     dword   eax,cr3
mov     dword   [SavedPageDirSysCall],eax
mov     dword   eax,[kerPageDir]
mov     dword   cr3,eax                     ;hangle system call in kernel page dir
push dword [SavedPageDirSysCall]
push dword [SavedSyscalParameter]
call SyscallsDelivery
pop dword eax
pop dword eax
mov     dword   eax,[SavedPageDirSysCall]
mov     dword   cr3,eax
popad
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

;[global callDriver]
;callDriver:
;mov     dword      [SavedEax],eax
;mov     dword      eax,cr3
;mov     dword      [SavedCr3],eax
;mov     dword      cr3,ebx
;call    dword      [SavedEax]
;mov     dword      eax,[SavedCr3]
;mov     dword      cr3,eax
;mov     dword      esp,[SavedEsp]
;ret

section .data
align 4

SavedErrorCode dd 0
SavedPageDir dd 0
SavedPageDirSysCall dd 0
SavedPageDirInts dd 0
SavedSyscalParameter dd 0
SavedCr3 dd 0
SavedEax dd 0

IntsEax dd 0
IntsEbx dd 0
IntsEcx dd 0
IntsEdx dd 0
IntsEbp dd 0
IntsEsp dd 0
IntsEsi dd 0
IntsEdi dd 0