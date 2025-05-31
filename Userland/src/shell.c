// sampleCodeModule.c
#include "user_syscalls.h"
#include <stdint.h>
#include <stddef.h>
// …

int main() {
    char *msg = "Hola desde syscall!\n";
    write(1, msg, 21);
    return 0;
}
