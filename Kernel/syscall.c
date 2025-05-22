#include "naiveConsole.h"
#include <stdint.h>
#include <lib.h>  // Si querés usar funciones auxiliares como strlen más adelante
#include "syscall.h"

void syscall_handler_c(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3) {
    switch (syscallNumber) {
        case 1: {
            char *msg = (char *)arg1;
            int len = (int)arg2;
            for (int i = 0; i < len; i++) {
                ncPrintChar(msg[i]);
            }
            break;
        }
        default:
            ncPrint("[SYSCALL desconocida]");
            ncNewline();
            break;
    }
}

void syscall(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3) {
	__asm__ __volatile__ (
		"int $0x80"
		:
		: "a"(syscallNumber), "b"(arg1), "c"(arg2), "d"(arg3)
	);
}
