include Makefile.inc

KERNEL=kernel.bin
SOURCES=kernel.c lib.c moduleLoader.c naiveConsole.c idtLoader.c irqDispatcher.c exceptions.c time.c syscall.c
SOURCES_ASM=asm/libasm.asm interrupts.asm
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)

# Regla genérica
%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

# Regla explícita para syscall.c
syscall.o: syscall.c
	$(GCC) $(GCCFLAGS) -I./include -c syscall.c -o syscall.o

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin

.PHONY: all clean
#./Toolchain/ModulePacker/mp.bin Kernel/kernel.bin Userland/0000-sampleCodeModule.bin Userland/0001-sampleDataModule.bin -o Image/x64BareBonesImage.img
#	qemu-img convert -O qcow2 Image/x64BareBonesImage.img Image/x64BareBonesImage.qcow2
#	./run.sh
