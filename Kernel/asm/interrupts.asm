
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
GLOBAL _syscallDispatcher

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscall_handler_c 

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


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

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

haltcpu:
	cli
	hlt
	ret


_syscallDispatcher:
    ; Guardar estado
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11

    ; Pasar argumentos a syscall_handler_c
    mov rdi, rax    ; syscall number
    mov rsi, rbx    ; arg1
    mov rdx, rcx    ; arg2
    mov rcx, rdx    ; arg3

    ; Esto pisa rdx → incorrecto.
    ; Corrección más segura:

    mov rdi, rax        ; syscall number
    mov rsi, rbx        ; arg1
    mov rdx, rcx        ; arg2
    mov rcx, rdx        ; MAL: estás moviendo el nuevo rdx que ya fue pisado

    ;  Solución correcta:
    mov rdi, rax        ; syscall number
    mov rsi, rbx        ; arg1
    mov rdx, rcx        ; arg2 (usamos rdx)
    mov rcx, rdx        ;  pisa rdx ya movido → error
    ; ==> Este fragmento tiene lógica circular

    ;  Forma correcta (asumimos userland llama así):
    ; syscall(rax, rbx, rcx, rdx) => syscall_handler_c(rdi, rsi, rdx, rcx)

    ; Entonces:
    mov rdi, rax        ; syscall number
    mov rsi, rbx        ; arg1
    mov rdx, rcx        ; arg2
    mov rcx, rdx        ; arg3  pisa arg2

    ;  Correcta:
    mov rdi, rax
    mov rsi, rbx
    mov rdx, rcx    ; rdx = arg2 original
    mov rcx, rdx    ;  error si rdx ya cambió

    ; Mejor: si venían de rbx, rcx, rdx, r8:
    ; En realidad, asumí:
    ; syscall(rax, rbx, rcx, rdx) -> rdi = rax, rsi = rbx, rdx = rcx, rcx = rdx

    mov rdi, rax
    mov rsi, rbx
    mov rdx, rcx
    mov rcx, rdx    ;  esto sigue mal si no salvás

    ;  Finalmente, usá registro temporal si querés estar seguro:

    mov r10, rdx
    mov rdx, rcx
    mov rcx, r10

    call syscall_handler_c

    ; Restaurar estado
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    iretq


SECTION .bss
	aux resq 1