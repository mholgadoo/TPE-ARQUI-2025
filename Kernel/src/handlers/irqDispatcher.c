// src/handlers/irqDispatcher.c

#include <stdint.h>
#include "time.h"     // Tu header con timer_handler()

// Dispatcher genérico de IRQs
void irqDispatcher(uint64_t irq) {
    switch (irq) {
        case 0:
            // Llamamos al handler de timer
            int_20();
            break;

        default:
            // IRQ no contemplada
            break;
    }
}

void int_20() {
    ncPrint("TIMERTICK");
    timer_handler();
}
