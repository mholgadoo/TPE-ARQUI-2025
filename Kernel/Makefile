include Makefile.inc

# Nombre del binario final
KERNEL := kernel.bin

# Linker script
LDSCRIPT := kernel.ld

# Todos los .asm en asm/
ASM_SRCS := $(wildcard asm/*.asm)
ASM_OBJS := $(ASM_SRCS:.asm=.o)

# Todos los .c en src/ y subdirectorios
C_SRCS  := $(shell find src -name '*.c')
C_OBJS  := $(C_SRCS:.c=.o)

# Regla por defecto
all: $(KERNEL)

# Cómo enlazar kernel.bin
$(KERNEL): $(ASM_OBJS) $(C_OBJS)
	$(LD) $(LDFLAGS) -T $(LDSCRIPT) -o $@ $(ASM_OBJS) $(C_OBJS)

# Compilar cualquier .c
%.o: %.c
	$(GCC) $(GCCFLAGS) -Iinclude -c $< -o $@

# Ensamblar cualquier .asm
%.o: %.asm
	$(ASM) $(ASMFLAGS) -f elf64 $< -o $@

# Limpiar artefactos
clean:
	rm -f $(ASM_OBJS) $(C_OBJS) $(KERNEL)

.PHONY: all clean
