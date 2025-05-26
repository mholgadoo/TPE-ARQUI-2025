// sampleCodeModule.c
#include <stdint.h>
#include "syscall.h"

int main() {
    char *msg = "Hola desde syscall!\n";
    syscall(1, (uint64_t)msg, 21, 0);
    return 0;
}
