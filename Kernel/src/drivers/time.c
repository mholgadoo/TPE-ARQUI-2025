#include "time.h"
#include "port_io.h"
#include <stdint.h>

#define PIT_COMMAND_PORT   0x43
#define PIT_CHANNEL0_PORT  0x40
#define PIT_BASE_FREQ      1193182UL

static volatile uint64_t ticks = 0;
static int tickFrequency = 18;

// ——— PIT ———
void initPIT(uint32_t freq_hz) {
    tickFrequency = freq_hz;
    uint32_t divisor = PIT_BASE_FREQ / freq_hz;
    outb(PIT_COMMAND_PORT, 0x36);
    outb(PIT_CHANNEL0_PORT, divisor & 0xFF);
    outb(PIT_CHANNEL0_PORT, (divisor >> 8) & 0xFF);
}

// ——— Handler de IRQ0 ———
void timer_handler(void) {
    ticks++;
}

// ——— APIs de tics ———
void setTickFrequency(uint16_t hz) {
    initPIT(hz);
}

void sleep(uint32_t t) {
    uint64_t start = ticks;
    while ((ticks - start) < t) ;
}

// ——— RTC ———
#define NMI_DISABLE_BIT  0x80
static const uint8_t rtc_regs[6] = {0x00,0x02,0x04,0x07,0x08,0x09};

static uint8_t bcd2dec(uint8_t bcd) {
    return (uint8_t)(((bcd >> 4) & 0xF)*10 + (bcd & 0xF));
}

void getTime(Timestamp *ts) {
    uint8_t raw[6];
    for (int i = 0; i < 6; i++) {
        outb(0x70, rtc_regs[i] | NMI_DISABLE_BIT);
        raw[i] = inb(0x71);
    }
    ts->seconds = bcd2dec(raw[0]);
    ts->minutes = bcd2dec(raw[1]);
    ts->hours   = bcd2dec(raw[2]);
    ts->day     = bcd2dec(raw[3]);
    ts->month   = bcd2dec(raw[4]);
    ts->year    = 2000 + bcd2dec(raw[5]);
}
