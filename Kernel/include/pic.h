#ifndef PIC_H
#define PIC_H

#include <stdint.h>

/// Remapea el PIC maestro/esclavo a los vectores 0x20–0x2F
void remapPIC(void);
#endif // PIC_H
