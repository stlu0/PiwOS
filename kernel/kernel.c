#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../cpu/timer.h"
#include <stdint.h>

void get_cpu_info() {
    unsigned int eax, ebx, ecx, edx;

    asm volatile("cpuid"
                 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                 : "a"(0) 
    );
    char cpu_vendor[13];
    *(unsigned int*)&cpu_vendor[0] = ebx;
    *(unsigned int*)&cpu_vendor[4] = edx;
    *(unsigned int*)&cpu_vendor[8] = ecx;
    cpu_vendor[12] = '\0';

    kprint("CPU: ");
    kprint(cpu_vendor);
    kprint("\n");
}

void print_os_info() {
    kprint("  .   *   ..  . *  *\n");
    kprint("*  * @()Ooc()*   o  .\n");
    kprint("    (Q@*0CG*O()  ___\n");
    kprint("   |\\_________/|/ _ \\\n");
    kprint("   |  |  |  |  | / | |\n");
    kprint("   |  |  |  |  | | | |\n");
    kprint("   |  |  |  |  | | | |\n");
    kprint("   |  |  |  |  | | | |\n");
    kprint("   |  |  |  |  | | | |\n");
    kprint("   |  |  |  |  | \\_| |\n");
    kprint("   |  |  |  |  |\\___/\n");
    kprint("   |\\_|__|__|_/|\n");
    kprint("    \\_________/\n");

    kprint("OS: PiwOS\n");
    kprint("Kernel: 1.0.0\n");
}

void neofetch() {
    print_os_info();
    get_cpu_info();
}

void page_call() {
    uint32_t phys_addr;
    uint32_t page = kmalloc(1000, 1, &phys_addr);
    char page_str[16] = "";
    hex_to_ascii(page, page_str);
    char phys_str[16] = "";
    hex_to_ascii(phys_addr, phys_str);
    kprint("Page: ");
    kprint(page_str);
    kprint(", physical address: ");
    kprint(phys_str);
    kprint("\n");
}

void clear() {
    clear_screen();
    kprint("[piwo_user@piwOS~]>");
}

void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();

    kprint("Welcome to PiwOS!\n"
        "Type END to halt the CPU\n"
        "Type PAGE to request a kmalloc()\n"
        "Type NEOFETCH to.. yeah..\n[piwo_user@piwOS~]>"
    );
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Baai!\n");
        asm volatile("hlt");
    }
    else if (strcmp(input, "NEOFETCH") == 0) {
        neofetch();
    }
    else if (strcmp(input, "PAGE") == 0) {
        page_call();
    }
    else if (strcmp(input, "CLEAR") == 0) {
        clear();
    }

    kprint("bro really said: ");
    kprint(input);
    kprint("\n[piwo_user@piwOS~]> ");
}
