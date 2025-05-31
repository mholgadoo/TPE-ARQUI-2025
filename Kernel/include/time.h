#ifndef TIME_H
#define TIME_H

#include <stdint.h>

// Manejador de interrupción del temporizador
void timer_handler(void);

// Ticks y segundos transcurridos desde el arranque
int  ticks_elapsed(void);
int  seconds_elapsed(void);

// Hora actual: rellena h, m y s
void getTime(int *h, int *m, int *s);

#endif // TIME_H
