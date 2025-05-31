#include "naiveConsole.h"
#include <stdint.h>

// Buffer auxiliar para convertir números
static char buffer[64];

// Dirección de memoria de video en modo texto (VGA)
static uint8_t * const video = (uint8_t*)0xB8000;
// Puntero al siguiente carácter a imprimir
static uint8_t * currentVideo = (uint8_t*)0xB8000;

// Dimensiones de pantalla en caracteres
static const uint32_t width  = 80;
static const uint32_t height = 25;

// Color de texto actual (atributo VGA)
static uint8_t currentColor = WHITE_ON_BLACK;

// Prototipo interno para conversión a base
static uint32_t uintToBase(uint64_t value, char* buf, uint32_t base);

// Obtener el color actual
uint8_t ncGetFontColor(void) {
    return currentColor;
}

// Establecer el color actual
void ncSetFontColor(uint8_t color) {
    currentColor = color;
}

// Imprimir cadena completa
void ncPrint(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        ncPrintChar(str[i]);
    }
}

// Imprimir un carácter (usa el atributo actual)
void ncPrintChar(char c) {
    *currentVideo = c;          // byte de carácter
    currentVideo++;             // avance al byte de atributo
    *currentVideo = currentColor; // byte de atributo
    currentVideo++;             // al siguiente carácter
}

// Nueva línea: avanza hasta inicio de siguiente fila
void ncPrintNewline(void) {
    while (((currentVideo - video) / 2) % width != 0) {
        ncPrintChar(' ');
    }
}

// Limpiar pantalla (rellena con espacios)
void ncClear(void) {
    for (uint32_t i = 0; i < width * height; i++) {
        video[2*i]   = ' ';
        video[2*i+1] = currentColor;
    }
    currentVideo = video;
}

// Imprimir número decimal
void ncPrintDec(uint64_t value) {
    ncPrintBase(value, 10);
}

// Imprimir número hexadecimal
void ncPrintHex(uint64_t value) {
    ncPrintBase(value, 16);
}

// Imprimir número binario
void ncPrintBin(uint64_t value) {
    ncPrintBase(value, 2);
}

// Invoca conversión interna y luego muestra el buffer
void ncPrintBase(uint64_t value, uint32_t base) {
    uint32_t len = uintToBase(value, buffer, base);
    buffer[len] = '\0';
    ncPrint(buffer);
}

// Convierte 'value' a cadena en 'buf' según 'base', devuelve dígitos
static uint32_t uintToBase(uint64_t value, char* buf, uint32_t base) {
    char* p = buf;
    uint32_t digits = 0;
    do {
        uint32_t rem = value % base;
        *p++ = (rem < 10) ? ('0' + rem) : ('A' + (rem - 10));
        digits++;
    } while (value /= base);
    return digits;
}
