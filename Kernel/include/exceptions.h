// Kernel/include/exceptions.h
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

/// Dispatcher que el stub ASM invoca al producirse una excepción.
/// @param code 0 = División por cero (#DE), 6 = Invalid Opcode (#UD)
void exceptionDispatcher(int code);

/// Manejador específico para la excepción de División por Cero (#DE).
void zero_division(void);

/// Manejador específico para la excepción de Invalid Opcode (#UD).
void invalid_opcode(void);

#endif // EXCEPTIONS_H
