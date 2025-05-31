// src/sys/syscalls.c

#include <stdint.h>
#include <stddef.h>
#include "syscalls.h"
#include "naiveConsole.h"   // ncGetFontColor, ncSetFontColor, ncPrintChar, ncClear
#include "keyboard.h"       // kb_get_char, kb_has_char
#include "time.h"           // getTime
#include "registers.h"      // getRegistersSnapshot
#include "syscall.h"
#include "speaker.h"        // playbeep

#define WHITE_ON_BLACK 0x0F
#define RED_ON_BLACK   0x0C

// 1) write: STDOUT(1) normal, STDERR(2) rojo
void sys_write(uint64_t fd, const char *buffer, uint64_t length) {
    uint8_t prev_color = ncGetFontColor();
    if (fd == 2) {
        ncSetFontColor(RED_ON_BLACK);
    }
    for (uint64_t i = 0; i < length; i++) {
        ncPrintChar(buffer[i]);
    }
    if (fd == 2) {
       ncSetFontColor(prev_color);
    }
}

// 2) clear screen
void sys_clear_screen(void) {
    ncClear();
}

// 3) set font size (stub)
void sys_set_font_size(size_t size) {
    (void)size;  // por implementar
}

// 6) get_char (bloqueante)
char sys_get_char(void) {
    return kb_get_char();
}

// 7) is_key_pressed
int sys_is_key_pressed(void) {
    return kb_has_char();
}

// 8) get_time
void sys_get_time(int *h, int *m, int *s) {
    Timestamp ts;
    getTime(&ts);
    if (h) *h = ts.hours;
    if (m) *m = ts.minutes;
    if (s) *s = ts.seconds;
}

// 11) get_registers_snapshot
void sys_get_registers_snapshot(uint64_t *regs) {
    getRegistersSnapshot(regs);
}

// 9) trigger div zero
void sys_trigger_div_zero(void) {
    (void)(1/0);
}

// 10) trigger invalid opcode
void sys_trigger_invalid_opcode(void) {
    __asm__ __volatile__("ud2");
}

// 12) beep (comentar hasta que exista playBeep)
void sys_beep(void) {
    playBeep();
}
