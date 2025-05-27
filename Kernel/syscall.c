#include "naiveConsole.h"
#include <include/syscalls.h>

// Agregar headers de funciones auxiliares si es necesario
// #include "time.h", "keyboard.h", etc.

uint64_t syscall_handler_c(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3) {
    switch (syscallNumber) {
        case 1: { // write
            sys_write((uint64_t)arg1, (char *)arg2, (uint64_t)arg3);
            break;
        }
        case 2: // clear_screen
            ncClear();
            break;

        case 3: // print_dec
            ncPrintDec(arg1);
            break;

        case 4: // print_hex
            ncPrintHex(arg1);
            break;

        case 5: // set_font_size
            sys_set_font_size((size_t)arg1);
            break;

        case 6: // get_char
            char c = sys_get_char();
            // devolver el valor de retorno usando rax
            __asm__ __volatile__("movb %0, %%al" :: "r"(c));
            return c;
            break;

        case 7: // is_key_pressed
            return sys_is_key_pressed();
            break;

        case 8: // get_time
            sys_get_time((uint64_t *)arg1, (uint64_t *)arg2, (uint64_t *)arg3);
            break;


        case 9: // trigger_div_zero
            (void)(1 / 0);
            break;

        case 10: // trigger_invalid_opcode
            __asm__ __volatile__("ud2");
            break;

        case 11: // get_registers_snapshot
            sys_get_registers_snapshot((uint64_t *)arg1);
            break;

        case 12: // beep
            // playBeep();
            break;

        default:
            ncPrint("[unknown syscall]");
            ncPrintNewline();
            break;
    }
}
