#ifndef MODULELOADER_H
#define MODULELOADER_H

#include <stdint.h>

// Carga módulos en memoria.
//   payloadStart: puntero al inicio de la imagen con todos los módulos
//   targetModuleAddress: array de direcciones destino por módulo
void loadModules(void *payloadStart, void **targetModuleAddress);

#endif // MODULELOADER_H
