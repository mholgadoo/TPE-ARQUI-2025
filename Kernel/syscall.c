#include "naiveConsole.h"
#include <stdint.h>

// Agregar headers de funciones auxiliares si es necesario
// #include "time.h", "keyboard.h", etc.

void syscall_handler_c(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3) {
    switch (syscallNumber) {
        case 1: { // print
            char *msg = (char *)arg1;
            int len = (int)arg2;
            for (int i = 0; i < len; i++) {
                ncPrintChar(msg[i]);
            }
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
            // fontSetSize(arg1); // Implementar si se desea cambiar tamaño
            break;

        case 6: // get_char
            // uint8_t c = getChar(); // Requiere definición de función getChar
            break;

        case 7: // is_key_pressed
            // return isKeyPressed(); // Requiere definición
            break;

        case 8: // get_time
            // getTime((int *)arg1, (int *)arg2, (int *)arg3); // H, M, S (punteros)
            break;

        case 9: // trigger_div_zero
            (void)(1 / 0);
            break;

        case 10: // trigger_invalid_opcode
            __asm__ __volatile__("ud2");
            break;

        case 11: // get_registers_snapshot
            // getRegisters((uint64_t*)arg1); // Supone un buffer en userland
            break;

        case 12: // beep
            // playBeep();
            break;

        case 13: // draw_pixel
            // drawPixel(arg1, arg2, arg3);
            break;

        case 14: // draw_rect
            // drawRect(arg1, arg2, arg3, arg4, color);
            break;

        case 15: // clear_graphics
            // clearGraphics();
            break;

        case 16: // draw_text
            // drawText(arg1, arg2, (char *)arg3, arg4);
            break;

        case 17: // set_graphics_mode
            // setGraphicsMode(arg1);
            break;

        default:
            ncPrint("[unknown syscall]");
            ncPrintNewline();
            break;
    }
}
