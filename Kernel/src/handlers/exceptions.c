// Kernel/src/handlers/exceptions.c
#include "exceptions.h"
#include "naiveConsole.h"
#include "registers.h"

// Etiquetas para el volcado de registros
static const char *labels[16] = {
    "RAX","RBX","RCX","RDX","RSI","RDI","RBP","RSP",
    "R8", "R9", "R10","R11","R12","R13","R14","R15"
};

void zero_division(void) {
    ncSetFontColor(RED_ON_BLACK);
    ncPrint("[#DE] División por cero");
    ncPrintNewline();
    ncSetFontColor(WHITE_ON_BLACK);
}

void invalid_opcode(void) {
    ncSetFontColor(RED_ON_BLACK);
    ncPrint("[#UD] Opcode inválido");
    ncPrintNewline();
    ncSetFontColor(WHITE_ON_BLACK);
}

void exceptionDispatcher(int code) {
    // 1) Mensaje según el tipo de excepción
    if (code == 0) {
        zero_division();
    } else if (code == 6) {
        invalid_opcode();
    } else {
        ncSetFontColor(RED_ON_BLACK);
        ncPrint("[??] Excepción ");
        ncPrintDec(code);
        ncPrintNewline();
        ncSetFontColor(WHITE_ON_BLACK);
    }

    // 2) Volcado de registros
    uint64_t regs[16];
    getRegistersSnapshot(regs);
    printRegisters(labels, regs);

    // 3) Tras iretq en ASM, volvemos al flujo anterior (shell o kernel)
}


/*


Diagnóstico de fallos
Cuando ocurre una excepción crítica—como una división por cero (#DE) o un código de operación inválido (#UD)—tu sistema no sabe continuar de forma segura. Mostrar en pantalla el estado de todos los registros (RAX, RBX, RCX, …, R15) en el momento del fallo te permite:

Ver qué valores manejaba cada variable interna del kernel o de la aplicación.

Comprender la instrucción que provocó el error (e IP/EIP), y los operandos que la rodeaban.

Localizar más rápidamente el bug en tu código (o detectar un acceso indebido a memoria, desbordamiento de pila, etc.).

Requisitos del enunciado
El TPE te pide explícitamente que, ante esas dos excepciones (#DE y #UD), muestres un mensaje de error más
la traza completa de los registros del procesador, antes de volver al prompt de la shell


*/