#include "registers.h"
#include "naiveConsole.h"
#include <stdint.h>

// Temporal: nombres de registros para printRegisters si no los recibes
static const char *defaultLabels[16] = {
    "RAX","RBX","RCX","RDX","RSI","RDI","RBP","RSP",
    "R8","R9","R10","R11","R12","R13","R14","R15"
};

void getRegistersSnapshot(uint64_t *regs) {
    __asm__ volatile (
        "mov %%rax,   (%0)\n\t"
        "mov %%rbx,  8(%0)\n\t"
        "mov %%rcx, 16(%0)\n\t"
        "mov %%rdx, 24(%0)\n\t"
        "mov %%rsi, 32(%0)\n\t"
        "mov %%rdi, 40(%0)\n\t"
        "mov %%rbp, 48(%0)\n\t"
        "mov %%rsp, 56(%0)\n\t"
        "mov %%r8,  64(%0)\n\t"
        "mov %%r9,  72(%0)\n\t"
        "mov %%r10, 80(%0)\n\t"
        "mov %%r11, 88(%0)\n\t"
        "mov %%r12, 96(%0)\n\t"
        "mov %%r13,104(%0)\n\t"
        "mov %%r14,112(%0)\n\t"
        "mov %%r15,120(%0)\n\t"
        : /* no outputs */
        : "r"(regs)
        : "memory"
    );
}

void printRegisters(const char *labels[16], uint64_t regs[16]) {
    for (int i = 0; i < 16; i++) {
        ncPrint(labels ? labels[i] : defaultLabels[i]);
        ncPrint(": ");
        ncPrintHex(regs[i]);
        ncPrintNewline();
    }
}
