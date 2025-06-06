# Makefile (Userland)

# Herramientas
CC       := gcc
LD       := ld
NASM     := nasm

# Flags
CFLAGS   := -m64 -ffreestanding -O2 -Wall -Wextra -Iinclude
LDFLAGS  := -m elf_x86_64 -T userland.ld

# Fuentes ASM (comunes a ambos binarios)
ASM_SRCS   := asm/call_80h.asm
ASM_OBJS   := $(ASM_SRCS:.asm=.o)

# Fuentes C para shell.bin
C_SRCS_SHELL := \
    asm/_loader.c \
    src/lib.c \
    src/shell.c \
    src/commands/clear.c \
    src/commands/divzero.c \
    src/commands/help.c \
    src/commands/invalop.c \
    src/commands/regs.c \
    src/commands/time.c

C_OBJS_SHELL := $(C_SRCS_SHELL:.c=.o)

# Fuentes C para test_syscalls.bin
C_SRCS_TEST := \
    asm/_loader.c \
    src/lib.c \
    src/test_syscalls.c

C_OBJS_TEST := $(C_SRCS_TEST:.c=.o)

# Nombres de los ejecutables finales
USER_BIN := shell.bin
TEST_BIN := test_syscalls.bin

.PHONY: all clean

all: $(USER_BIN) $(TEST_BIN)

# -------------------------------------------------------------------
# Generar shell.bin (sólo con shell.c y sus comandos, sin test_syscalls)
# -------------------------------------------------------------------
$(USER_BIN): $(ASM_OBJS) $(C_OBJS_SHELL)
	$(LD) $(LDFLAGS) -o $@ $^

# -------------------------------------------------------------------
# Generar test_syscalls.bin (sólo con test_syscalls.c, sin shell)
# -------------------------------------------------------------------
$(TEST_BIN): $(ASM_OBJS) $(C_OBJS_TEST)
	$(LD) $(LDFLAGS) -o $@ $^

# -------------------------------------------------------------------
# Regla genérica para compilar .c -> .o
# -------------------------------------------------------------------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# -------------------------------------------------------------------
# Regla genérica para compilar .asm -> .o
# -------------------------------------------------------------------
%.o: %.asm
	$(NASM) -f elf64 $< -o $@

# -------------------------------------------------------------------
# Limpiar objetos y binarios
# -------------------------------------------------------------------
clean:
	rm -f $(ASM_OBJS) $(C_OBJS_SHELL) $(C_OBJS_TEST) $(USER_BIN) $(TEST_BIN)
