#include "speaker.h"
#include "lib.h"       
#include "port_io.h" // para inb(), outb()

#define PIT_CONTROL_PORT   0x43
#define PIT_CHANNEL2_PORT  0x42
#define SPEAKER_PORT       0x61
#define PIT_FREQUENCY      1193180

void playBeep(void) {
    // Frecuencia deseada: 1000 Hz
    uint32_t divisor = PIT_FREQUENCY / 1000;

    // Configura PIT canal 2, modo 3 (square wave), LSB/MSB
    outb(PIT_CONTROL_PORT, 0xB6);
    outb(PIT_CHANNEL2_PORT, divisor & 0xFF);
    outb(PIT_CHANNEL2_PORT, (divisor >> 8) & 0xFF);

    // Activa speaker: pone los bits 0 y 1 de puerto 0x61
    uint8_t tmp = inb(SPEAKER_PORT);
    outb(SPEAKER_PORT, tmp | 3);

    // Duración aproximada ~100 ms (busy-wait)
    for (volatile uint32_t i = 0; i < 1000000; i++);

    // Desactiva speaker: limpia los bits 0 y 1
    tmp = inb(SPEAKER_PORT) & ~3;
    outb(SPEAKER_PORT, tmp);
}
