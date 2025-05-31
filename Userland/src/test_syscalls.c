#include "user_syscalls.h"
#include <stdint.h>

int main(void) {
    write(1, "Presiona una tecla...\n", 22);
    char c = getChar();
    write(1, &c, 1);
    write(1, "\n", 1);

    write(1, "¿Tecla disponible? ", 20);
    int kp = isKeyPressed();
    if (kp)
        write(1, "Sí\n", 4);
    else
        write(1, "No\n", 3);

    // … resto de pruebas …
    return 0;
}
