#ifndef _syscall_h_
#define _syscall_h_

#include <stdint.h>


void syscall_handler_c(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3);
void syscall(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3);

#endif
