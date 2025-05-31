#include "syscallDispatcher.h"
#include "syscalls.h"
#include "naiveConsole.h"

uint64_t syscall_handler_c(uint64_t num, uint64_t a1, uint64_t a2, uint64_t a3) {
    switch (num) {
        case 1:  sys_write(a1, (const char*)a2, a3);             break;
        case 2:  sys_clear_screen();                            break;
        case 3:  /* opcional print_dec, no syscall */           break;
        case 4:  /* opcional print_hex, no syscall */           break;
        case 5:  sys_set_font_size((size_t)a1);                 break;
        case 6:  return (uint64_t)sys_get_char();
        case 7:  return (uint64_t)sys_is_key_pressed();
        case 8:  sys_get_time((int*)a1, (int*)a2, (int*)a3);    break;
        case 9:  sys_trigger_div_zero();                        break;
        case 10: sys_trigger_invalid_opcode();                  break;
        case 11: sys_get_registers_snapshot((uint64_t*)a1);     break;
        case 12: sys_beep();                            break;
        default:
            ncPrint("[unknown syscall]");
            ncPrintNewline();
    }
    return 0;
}
