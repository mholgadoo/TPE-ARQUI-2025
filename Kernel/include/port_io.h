// Kernel/include/port_io.h
#ifndef PORT_IO_H
#define PORT_IO_H

#include <stdint.h>

/// Lee un byte del puerto de E/S dado.
/// @param port Número de puerto (p.ej. 0x60 para teclado, 0x64 para estado)
/// @return El byte leído.
uint8_t read_port(uint16_t port);

/// Escribe un byte al puerto de E/S dado.
/// @param port  Número de puerto (p.ej. 0x61 para beep, 0x70/0x71 para RTC)
/// @param value El valor a escribir.
void write_port(uint16_t port, uint8_t value);


void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
/// Lee un byte del p