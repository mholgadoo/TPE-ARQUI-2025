#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <stddef.h> // para size_t

// syscalls obligatorias TP5/TPE
void sys_write(uint64_t fd, const char *buffer, uint64_t length);
void sys_clear_screen(void);
void sys_set_font_size(size_t size);
char sys_get_char(void);
int  sys_is_key_pressed(void);
void sys_get_time(int *hours, int *minutes, int *seconds);
void sys_get_registers_snapshot(uint64_t *regs);
void sys_beep(void);
// excepciones de prueba
// (disparadas directamente desde syscall handler)
void sys_trigger_div_zero(void);
void sys_trigger_invalid_opcode(void);

#endif // SYSCALLS_H
