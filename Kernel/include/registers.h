// Kernel/include/registers.h
#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

// Captura el snapshot de los registros generales (RAX, RBX, ..., R15)
// regs debe apuntar a un array de al menos 16 uint64_t
void getRegistersSnapshot(uint64_t *regs);

// Imprime por pantalla los registros cuya etiqueta pasas en labels[]
// y sus valores en regs[]. labels debe ser un array de 16 cadenas:
//   {"RAX", "RBX", ..., "R15"}
void printRegisters(const char *labels[16], uint64_t regs[16]);

#endif // REGISTERS_H
