#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h>  // para uint64_t y size_t

void sys_set_font_size(size_t size);
size_t sys_get_font_size();
void sys_get_time(uint64_t *h, uint64_t *m, uint64_t *s);
void sys_get_registers_snapshot(uint64_t *buffer);

#endif
