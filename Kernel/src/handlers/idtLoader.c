// src/handlers/idtLoader.c
#include <stdint.h>
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>

#pragma pack(push)
#pragma pack(1)
typedef struct {
    uint16_t offset_l;
    uint16_t selector;
    uint8_t  cero;
    uint8_t  access;
    uint16_t offset_m;
    uint32_t offset_h;
    uint32_t other_cero;
} DESCR_INT;
#pragma pack(pop)

// IDT base address: 256 entradas
static DESCR_INT *idt = (DESCR_INT *) 0;

// Stubs ASM proporcionados por la cátedra (ORIGINAL)
extern void _exception0Handler(void);
extern void _irq00Handler(void);

// Stubs ASM que debes agregar (ADICIÓN)
extern void _exception6Handler(void);
extern void _irq01Handler(void);
extern void _syscallDispatcher(void);

// Helper: llena una entrada de la IDT
static void setup_IDT_entry(int idx, uint64_t off, uint8_t access) {
    idt[idx].offset_l   = off & 0xFFFF;
    idt[idx].selector   = 0x08;               // CS descriptor en GDT
    idt[idx].cero       = 0;
    idt[idx].access     = access;
    idt[idx].offset_m   = (off >> 16) & 0xFFFF;
    idt[idx].offset_h   = (off >> 32) & 0xFFFFFFFF;
    idt[idx].other_cero = 0;
}

void load_idt() {
    // 1) Entradas de excepciones
    setup_IDT_entry(0x00, (uint64_t)&_exception0Handler, ACS_INT);  // #DE
    setup_IDT_entry(0x06, (uint64_t)&_exception6Handler, ACS_INT);  // #UD

    // 2) Entradas de IRQ hardware (remapeadas en GDT a 0x20,0x21)
    setup_IDT_entry(0x20, (uint64_t)&_irq00Handler,    ACS_INT);   // timer
    setup_IDT_entry(0x21, (uint64_t)&_irq01Handler,    ACS_INT);   // teclado

    // 3) Entrada de syscall software
    setup_IDT_entry(0x80, (uint64_t)&_syscallDispatcher, ACS_SYSCALL);

    // 4) Cargar la IDT
    struct {
        uint16_t limit;
        uint64_t base;
    } __attribute__((packed)) IDTR = {
        .limit = sizeof(DESCR_INT) * 256 - 1,
        .base  = (uint64_t)idt
    };
    __asm__ volatile("lidt %0" : : "m"(IDTR));

    // 5) Desenmascarar IRQ0 (timer) e IRQ1 (teclado)
    picMasterMask(0xFC);  // 1111_1100b → bit0=0(IRQ0), bit1=0(IRQ1)
    picSlaveMask(0xFF);   // todas en esclavo enmascaradas

    // 6) Habilitar interrupciones en el CPU
    __asm__ volatile("sti");
}




/*
Vecto­r 0x06 → _exception6Handler para manejo de invalid‐opcode.

Vector 0x21 → _irq01Handler para el driver de teclado por IRQ.

Vector 0x80 → _syscallDispatcher para invocar syscalls desde userland.

*/