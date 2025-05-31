// Kernel/src/drivers/port_io.c
#include "port_io.h"
#include <stdint.h>

uint8_t read_port(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0"
                      : "=a"(ret)
                      : "Nd"(port));
    return ret;
}

void write_port(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1"
                      :
                      : "a"(value), "Nd"(port));
}

// Wrappers para que el resto del kernel use inb/outb
uint8_t inb(uint16_t port) {
    return read_port(port);
}

void outb(uint16_t port, uint8_t value) {
    write_port(port, value);
}