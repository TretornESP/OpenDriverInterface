#include "odi/odi.h"
#include "odi/debug.h"

#include "drivers/test/basic/basic_dd.h"
#include "drivers/bus/pci/pci_dd.h"

#include "arch/simd.h"
#include "arch/gdt.h"
#include "io/interrupts.h"
#include "memory/memory.h"
#include "memory/paging.h"
#include "memory/heap.h"
#include "util/printf.h"
#include "dev/acpi/acpi.h"

#define STR_MAX_SIZE 65536

void _start(void) {
    init_simd();
    init_memory();
    init_paging();
    init_heap();
    init_gdt();
    init_interrupts();
    init_acpi();

    odi_hello();
    init_pci();
    
    odi_debug_flusha();

    struct mcfg_header* mcfg = get_acpi_mcfg();
    struct pci_ioctl_scan_bus_control *scan_control = malloc(sizeof(struct pci_ioctl_scan_bus_control));
    scan_control->entries = malloc(mcfg->header.length - sizeof(struct mcfg_header));
    scan_control->devconf_size = mcfg->header.length - sizeof(struct mcfg_header);

    odi_manual_device_register(86, (void*)scan_control);
    odi_debug_flusha();

    odi_ioctl("pcia", PCI_IOCTL_SCAN_BUS, 0x0);
    odi_debug_flusha();

    while(1);
}