#ifndef TIME_H
#define TIME_H

#include <stdint.h>

/// Inicializa el PIT a freq_hz tics por segundo
void initPIT(uint32_t freq_hz);

/// Handler de IRQ0 (timer tick); debe ser llamado desde irqDispatcher
void timer_handler(void);

/// Ajusta la frecuencia lógica de segundos
void setTickFrequency(uint16_t hz);

/// (Opcional) Sleep bloqueante en tics
void sleep(uint32_t ticksToWait);

/// Estructura para hora real
typedef struct {
    int hours, minutes, seconds, day, month, year;
} Timestamp;

/// Lee el reloj CMOS y rellena @ts
void getTime(Timestamp *ts);

#endif // TIME_H
