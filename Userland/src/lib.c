#include <stddef.h>
#include <stdint.h>
#include "lib.h"

uint64_t syscall(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3) {
    uint64_t ret;
    __asm__ __volatile__ (
        "int $0x80"
        : "=a"(ret)
        : "a"(syscallNumber), "b"(arg1), "c"(arg2), "d"(arg3)
    );
    return ret;
}

// Wrappers de las syscalls
void write(uint64_t fd, const char *buf, uint64_t len) {
    syscall(1, fd, (uint64_t)buf, len);
}

void clear(void) {
    syscall(2, 0, 0, 0);
}

void setFontSize(size_t size) {
    syscall(5, size, 0, 0);
}

char getChar(void) {
    return (char)syscall(6, 0, 0, 0);
}

int isKeyPressed(void) {
    return (int)syscall(7, 0, 0, 0);
}

void getTime(int *h, int *m, int *s) {
    syscall(8, (uint64_t)h, (uint64_t)m, (uint64_t)s);
}

void triggerDivZero(void) {
    syscall(9, 0, 0, 0);
}

void triggerInvalidOpcode(void) {
    syscall(10, 0, 0, 0);
}

void getRegisters(uint64_t *regs) {
    syscall(11, (uint64_t)regs, 0, 0);
}

void beep(void) {
    syscall(12, 0, 0, 0);
}
