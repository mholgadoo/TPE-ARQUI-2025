// syscall.h
#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

void syscall(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3);

#endif
