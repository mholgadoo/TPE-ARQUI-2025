#include "time.h"

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void getTime(int *h, int *m, int *s){
	int total_seconds = seconds_elapsed();
	*h = (total_seconds / 3600) % 24; // Horas en formato 24h
	*m = (total_seconds / 60) % 60;   // Minutos
	*s = total_seconds % 60;          // Segundos
}