#ifndef PIC_H
#define PIC_H

#include <stdint.h>

/// Remapea el PIC maestro/esclavo a los vectores 0x20–0x2F
void remapPIC(void);

/// Enmascara/habilita líneas IRQ en el PIC maestro (porta 0x21)
void picMasterMask(uint8_t mask);

/// Enmascara/habilita líneas IRQ en el PIC esclavo (porta 0xA1)
void picSlaveMask(uint8_t mask);

#endif // PIC_H
