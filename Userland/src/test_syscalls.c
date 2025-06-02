// Userland/src/test_syscalls.c
#include <stdint.h>
#include "lib.h"
#define STDOUT 1
#define STDERR 2

extern void _start();
void *memset(void *dst, int c, uint64_t n);  // ya existe en tu loader

int main() {
    char msg1[] = "Prueba sys_write STDOUT\n";
    char msg2[] = "Prueba sys_write STDERR\n";
    uint64_t val;
    
    // 1) sys_write: STDOUT
    syscall(1, STDOUT, (uint64_t)msg1, sizeof(msg1)-1);

    // 1b) sys_write: STDERR (texto en rojo)
    syscall(1, STDERR, (uint64_t)msg2, sizeof(msg2)-1);

    // 2) sys_clear_screen: verás pantalla limpia
    syscall(2, 0, 0, 0);

    // 3) sys_print_dec: imprime en decimal '123456'
    syscall(3, 123456, 0, 0);

    // Nuevo renglón tras el decimal
    syscall(1, STDOUT, (uint64_t)"\n", 1);

    // 4) sys_print_hex: imprime en hexadecimal '0xABCDEF'
    syscall(4, 0xABCDEF, 0, 0);
    syscall(1, STDOUT, (uint64_t)"\n", 1);

    // 6 y 7) sys_get_char / sys_is_key_pressed
    // Espera a que presiones una tecla:
    while (!syscall(7, 0, 0, 0));   // bucle hasta que haya tecla
    val = syscall(6, 0, 0, 0);      // obtiene scancode/ASCII
    // Imprimir el código de la tecla en hex
    syscall(1, STDOUT, (uint64_t)"Tecla read (hex): ", 18);
    syscall(4, val, 0, 0);
    syscall(1, STDOUT, (uint64_t)"\n", 1);

    // 8) sys_get_time: hora actual en 3 enteros (h,m,s)
    int h, m, s;
    syscall(8, (uint64_t)&h, (uint64_t)&m, (uint64_t)&s);
    // Imprimir “Hora: hh:mm:ss”
    char fmt1[] = "Hora: 00:00:00\n";
    // convertir h,m,s a ASCII en el buffer
    // asume que h<100, m<60, s<60
    fmt1[6]  = '0' + (h/10);
    fmt1[7]  = '0' + (h%10);
    fmt1[9]  = '0' + (m/10);
    fmt1[10] = '0' + (m%10);
    fmt1[12] = '0' + (s/10);
    fmt1[13] = '0' + (s%10);
    syscall(1, STDOUT, (uint64_t)fmt1, sizeof(fmt1)-1);

    // 9) sys_trigger_div_zero: dejará caer la excepción #DE y mostrará dump
    syscall(9, 0, 0, 0);
    // Tras el dump vuelve aquí (shell o userland)

    // 10) sys_trigger_invalid_opcode: mostrará excepción #UD y dump
    syscall(10, 0, 0, 0);

    // 11) sys_get_registers_snapshot
    // Reserva espacio para 16 registros
    uint64_t regs[16];
    syscall(11, (uint64_t)regs, 0, 0);
    // Imprime un registro de muestra, p.ej. RAX
    syscall(1, STDOUT, (uint64_t)"RAX: ", 5);
    syscall(4, regs[0], 0, 0);  // regs[0] = RAX
    syscall(1, STDOUT, (uint64_t)"\n", 1);

    return 0;
}
