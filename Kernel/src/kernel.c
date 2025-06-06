#include <stdint.h>
#include <string.h>
#include <lib.h>
#include "moduleLoader.h"
#include "naiveConsole.h"
#include "idtLoader.h"    // IDT: vectores 0x00,06,20,21,80
#include "pic.h"            // remapPIC(), picMasterMask(), picSlaveMask()
#include "time.h"           // initPIT(), setTickFrequency(), timer_handler()
#include "interrupts.h"    // Stub de irqDispatcher, exceptionDispatcher

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncPrintNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncPrintNewline();

	ncPrint("[Loading modules]");
	ncPrintNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncPrintNewline();
	ncPrintNewline();

	ncPrint("[Initializing kernel's binary]");
	ncPrintNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncPrintNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncPrintNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncPrintNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncPrintNewline();

	ncPrint("[Done]");
	ncPrintNewline();
	ncPrintNewline();
	return getStackBase();
}

int main()
{	
	ncClear();
    ncPrint("DEBUG: entro a main()\n");
    ncPrint("> ");
    // ——— Inicialización del subsistema de interrupciones ———
    load_idt();           // 1) Monta la IDT con vectores 0x00/#DE,0x06/#UD,0x20/IRQ0,0x21/IRQ1,0x80/syscall
    remapPIC();           // 2) Remapea PIC1→0x20, PIC2→0x28 (ICW1–4)
    setTickFrequency(100);// 3) Inicializa el PIT a 100 Hz y actualiza tickFrequency
    picMasterMask(0xFC);  // 4) Habilita IRQ0 (bit0=0) e IRQ1 (bit1=0) en PIC maestro
    picSlaveMask(0xFF);   // 5) Enmascara todas las líneas en PIC esclavo
    __asm__ volatile("sti"); // 6) Activa interrupciones en el CPU

	ncPrint("[Kernel Main]");
	ncPrintNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncPrintNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncPrintNewline();
	ncPrintNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncPrintNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncPrintNewline();
	
	while(1);

	ncPrint("[Finished]");
	return 0;
}