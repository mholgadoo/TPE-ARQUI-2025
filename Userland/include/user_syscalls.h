// include/user_syscalls.h
#ifndef USER_SYSCALLS_H
#define USER_SYSCALLS_H

#include <stdint.h>
#include <stddef.h>
void     write(uint64_t fd, const char *buf, uint64_t len);
void     clear(void);
void     setFontSize(size_t s);
char     getChar(void);
int      isKeyPressed(void);
void     getTime(int *h, int *m, int *s);
void     triggerDivZero(void);
void     triggerInvalidOpcode(void);
void     getRegisters(uint64_t *r);
void     beep(void);

#endif // USER_SYSCALLS_H
