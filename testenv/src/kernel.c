#include "odi/odi.h"

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

    while(1);
}