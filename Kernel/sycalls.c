#include <stddef.h>
#include "keyboard.h"
#include "naiveConsole.h"
#include <stdint.h>

static size_t currentFontSize = 1;


void sys_write(uint64_t fd, char *buffer, uint64_t length) {
    int original_color = ncGetFontColor();  // si tenés función para guardar color

    if (fd == 2) {
        ncSetFontColor(RED);  // STDERR → texto rojo
    }

    for (uint64_t i = 0; i < length; i++) {
        ncPrintChar(buffer[i]);
    }

    if (fd == 2) {
        ncSetFontColor(original_color);  // restaurar color
    }
}


void sys_set_font_size(size_t size) {
    if (size == 0) return;
    currentFontSize = size;
}

extern char kb_get_char(void);
extern uint8_t kb_has_char(void);

uint64_t sys_get_char(void) {
    return (uint64_t)kb_get_char();  // Se expande automáticamente a 64 bits
}

uint64_t sys_is_key_pressed(void) {
    return (uint64_t)kb_has_char();  // También, por convención
}

void sys_get_time(uint64_t *h, uint64_t *m, uint64_t *s) {
    int hour, min, sec;
    getTime(&hour, &min, &sec);  // usa la función del kernel

    *h = (uint64_t)hour;
    *m = (uint64_t)min;
    *s = (uint64_t)sec;
}


//implementar en interrupts.c
void sys_get_registers_snapshot(uint64_t *buffer) {
    getRegisters(buffer);  // función que debe copiar los registros actuales
}