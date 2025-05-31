; call_80h.asm — stub para invocar int 0x80 desde userland
global _syscall
_syscall:
    mov eax, [esp+4]
    mov ebx, [esp+8]
    mov ecx, [esp+12]
    mov edx, [esp+16]
    int 0x80
    ret
