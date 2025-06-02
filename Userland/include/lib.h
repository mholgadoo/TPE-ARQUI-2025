// Userland/include/lib.h
#ifndef LIB_H
#define LIB_H

#include <stddef.h>
#include <stdint.h>

/// Invoca la interrupción 0x80 con los cuatro argumentos dados.
/// @param syscallNumber Número de la llamada al sistema.
/// @param arg1 Primer argumento de la syscall.
/// @param arg2 Segundo argumento de la syscall.
/// @param arg3 Tercer argumento de la syscall.
/// @return El valor de retorno devuelto en RAX.
uint64_t syscall(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3);

/// Escribe `len` bytes de `buf` en el descriptor de archivo `fd`.
/// @param fd 1 = STDOUT, 2 = STDERR.
/// @param buf Puntero al buffer de caracteres a escribir.
/// @param len Número de bytes a escribir.
void write(uint64_t fd, const char *buf, uint64_t len);

/// Limpia la pantalla en modo texto.
void clear(void);

/// Ajusta el tamaño de fuente (stub; puede no implementarse).
/// @param size Tamaño de fuente deseado.
void setFontSize(size_t size);

/// Lee un carácter de entrada (bloqueante).
/// @return El carácter leído.
char getChar(void);

/// Consulta si hay alguna tecla presionada.
/// @return 1 si hay tecla disponible, 0 en caso contrario.
int isKeyPressed(void);

/// Obtiene la hora del sistema (horas, minutos, segundos).
/// @param h Puntero para recibir las horas.
/// @param m Puntero para recibir los minutos.
/// @param s Puntero para recibir los segundos.
void getTime(int *h, int *m, int *s);

/// Fuerza una excepción de división por cero (#DE).
void triggerDivZero(void);

/// Fuerza una excepción de invalid opcode (#UD).
void triggerInvalidOpcode(void);

/// Copia el snapshot de los 16 registros generales en `regs`.
/// @param regs Array de 16 uint64_t donde se almacenarán los registros.
void getRegisters(uint64_t *regs);

/// Emite un pitido simple (puede quedarse como stub si no se implementa).
void beep(void);

#endif // LIB_H
