.PHONY: all bootloader kernel userland image run clean

all: bootloader kernel userland image

bootloader:
	cd Bootloader && make all

kernel:
	cd Kernel && make all

userland:
	cd Userland && make all

image:
	cd Image && make all

run:
	@echo "Ya podés ejecutar './run.sh' en otra terminal fuera del contenedor."

clean:
	cd Bootloader && make clean
	cd Kernel && make clean
	cd Userland && make clean
	cd Image && make clean
