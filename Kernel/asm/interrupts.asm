;===============================================================================
; File: interrupts.asm
;   Agrupa los handlers de CPU, PIC, IRQ, excepciones y syscalls
;===============================================================================

;─────────────────────────────────────────────────────────────────────────────
; ORIGINAL: símbolos exportados por la cátedra
;─────────────────────────────────────────────────────────────────────────────
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler

;─────────────────────────────────────────────────────────────────────────────
; ADICIÓN: exportar handler de invalid-opcode (#UD)
;─────────────────────────────────────────────────────────────────────────────
GLOBAL _exception6Handler           ; Excepción #UD

;─────────────────────────────────────────────────────────────────────────────
; ADICIÓN: handler de syscalls (vector 0x80)
;─────────────────────────────────────────────────────────────────────────────
GLOBAL _syscallDispatcher

;─────────────────────────────────────────────────────────────────────────────
; ORIGINAL: referencias externas
;─────────────────────────────────────────────────────────────────────────────
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscall_handler_c 

SECTION .text

;===============================================================================
; Macros para salvar/restaurar el estado de registro
;===============================================================================
%macro pushState 0
    push    rax
    push    rbx
    push    rcx
    push    rdx
    push    rbp
    push    rdi
    push    rsi
    push    r8
    push    r9
    push    r10
    push    r11
    push    r12
    push    r13
    push    r14
    push    r15
%endmacro

%macro popState 0
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     r11
    pop     r10
    pop     r9
    pop     r8
    pop     rsi
    pop     rdi
    pop     rbp
    pop     rdx
    pop     rcx
    pop     rbx
    pop     rax
%endmacro

;===============================================================================
; Macro genérico para manejar IRQs
;===============================================================================
%macro irqHandlerMaster 1
    pushState
    mov     rdi, %1           ; número de IRQ
    call    irqDispatcher
    ; Señal EOI al PIC maestro
    mov     al, 0x20
    out     0x20, al
    popState
    iretq
%endmacro

;===============================================================================
; Macro genérico para manejar excepciones
;===============================================================================
%macro exceptionHandler 1
    pushState
    mov     rdi, %1           ; número de excepción
    call    exceptionDispatcher
    popState
    iretq
%endmacro

;===============================================================================
; ORIGINAL: instrucciones básicas de control CPU
;===============================================================================
_hlt:
    sti
    hlt
    ret

_cli:
    cli
    ret

_sti:
    sti
    ret

;===============================================================================
; PIC Masking (original)
;===============================================================================
picMasterMask:
    push    rbp
    mov     rbp, rsp
    mov     ax, di            ; máscara de 16 bits (solo AL se usa)
    out     0x21, al
    pop     rbp
    retn

picSlaveMask:
    push    rbp
    mov     rbp, rsp
    mov     ax, di
    out     0xA1, al
    pop     rbp
    retn

;===============================================================================
; IRQ Handlers (timer, teclado, …)
;===============================================================================
; Canal 0: Timer
_irq00Handler:
    irqHandlerMaster 0

; Canal 1: Keyboard
_irq01Handler:
    irqHandlerMaster 1

; Cascade pic never called
_irq02Handler:
    irqHandlerMaster 2

; Serial Port 2 and 4
_irq03Handler:
    irqHandlerMaster 3

; Serial Port 1 and 3
_irq04Handler:
    irqHandlerMaster 4

; USB
_irq05Handler:
    irqHandlerMaster 5

;===============================================================================
; Exception Handlers
;===============================================================================
; Zero Division Exception
_exception0Handler:
    exceptionHandler 0

; Invalid Opcode (#UD)
_exception6Handler:
    exceptionHandler 6

;===============================================================================
; Syscall Dispatcher (vector 0x80)
;===============================================================================
_syscallDispatcher:
    pushState

    ; Organizar argumentos para syscall_handler_c(num, a1, a2, a3)
    mov     rdi, rax        ; número de syscall
    mov     rsi, rbx        ; arg1
    mov     r10, rdx        ; temp ← arg3
    mov     rdx, rcx        ; arg2
    mov     rcx, r10        ; arg3

    call    syscall_handler_c

    popState
    iretq

;===============================================================================
; ORIGINAL: halt CPU
;===============================================================================
haltcpu:
    cli
    hlt
    ret

SECTION .bss
    aux resq 1
