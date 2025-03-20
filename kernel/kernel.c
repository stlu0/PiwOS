#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"

void kernel_main() {
    isr_install();
    irq_install();

    kprint("Welcome to PiwOS!\n"
        "Type END to halt the CPU\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Baai!\n");
        asm volatile("hlt");
    }
    else if (strcmp(input, "NEOFETCH") == 0) {
        kprint("piwosz@piwOS\n OS: PiwOS x86\n");
    }

    kprint("bro really said: ");
    kprint(input);
    kprint("\n> ");
}
