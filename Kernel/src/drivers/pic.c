#include "pic.h"
#include "port_io.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#define ICW1_INIT    0x11
#define ICW4_8086    0x01

void remapPIC(void) {
    // Comienzo de inicialización
    outb(PIC1_COMMAND, ICW1_INIT);
    outb(PIC2_COMMAND, ICW1_INIT);
    // Offset de vectores: PIC1 → 0x20, PIC2 → 0x28
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);
    // Conectores en cascada
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);
    // Modo 8086
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);
    // Al arrancar dejamos todo enmascarado; luego habilitaremos líneas concretas
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}

void picMasterMask(uint8_t mask) {
    outb(PIC1_DATA, mask);
}

void picSlaveMask(uint8_t mask) {
    outb(PIC2_DATA, mask);
}
