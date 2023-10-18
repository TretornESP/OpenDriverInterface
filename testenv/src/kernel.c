#include "odi/odi.h"
#include "odi/debug.h"

#include "drivers/test/basic/basic_dd.h"

#include "arch/simd.h"
#include "arch/gdt.h"
#include "io/interrupts.h"
#include "memory/memory.h"
#include "memory/paging.h"
#include "memory/heap.h"
#include "util/printf.h"

#define STR_MAX_SIZE 65536

void _start(void) {
    init_simd();
    init_memory();
    init_paging();
    init_heap();
    init_gdt();
    init_interrupts();

    odi_hello();
    init_basic();
    
    odi_debug_flusha();

    odi_manual_device_register(255, 0x0);
    odi_list_devices();

    odi_read("basica", 0x0, 0x200, 0x0);

    odi_debug_flusha();

    while(1);
}