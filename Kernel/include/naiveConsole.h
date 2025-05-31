// naiveConsole.h
#ifndef NAIVECONSOLE_H
#define NAIVECONSOLE_H

#include <stdint.h>

// VGA text mode attribute macros (background<<4 | foreground)
#define WHITE_ON_BLACK 0x0F
#define RED_ON_BLACK   0x0C
#define GREEN_ON_BLACK 0x0A
#define BLUE_ON_BLACK  0x09
// …puedes añadir más combinaciones si las necesitas

// Obtiene el color (atributo VGA) actualmente seleccionado
uint8_t ncGetFontColor(void);

// Establece el color (atributo VGA) para futuras impresiones
void    ncSetFontColor(uint8_t color);

// Imprime una cadena terminada en '\0'
void    ncPrint(const char* str);

// Imprime un solo carácter con el color actual
void    ncPrintChar(char c);

// Salta a la siguiente línea
void    ncPrintNewline(void);

// Limpia toda la pantalla (rellena con espacios)
void    ncClear(void);

// Imprime un entero en base decimal
void    ncPrintDec(uint64_t value);

// Imprime un entero en base hexadecimal
void    ncPrintHex(uint64_t value);

// Imprime un entero en base binaria
void    ncPrintBin(uint64_t value);

// Imprime un entero en cualquier base (2, 10, 16, …)
void    ncPrintBase(uint64_t value, uint32_t base);

#endif // NAIVECONSOLE_H
