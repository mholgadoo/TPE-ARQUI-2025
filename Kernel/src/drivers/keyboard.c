#include "keyboard.h"
#include <stdint.h>

#define BUFFER_SIZE 128

static char buffer[BUFFER_SIZE];
static int read_index = 0;
static int write_index = 0;
static int count = 0;

void kb_push_char(char c) {
    if (count < BUFFER_SIZE) {
        buffer[write_index] = c;
        write_index = (write_index + 1) % BUFFER_SIZE;
        count++;
    }
}

char kb_get_char() {
    while (count == 0);
    char c = buffer[read_index];
    read_index = (read_index + 1) % BUFFER_SIZE;
    count--;
    return c;
}

int kb_has_char() {
    return count > 0;
}
