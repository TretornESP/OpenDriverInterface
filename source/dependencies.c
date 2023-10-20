#include "dependencies.h"
#include "types.h"

#ifdef USE_KOT
//Kot imports go here
#endif

#ifdef USE_BMOON
#include "../memory/heap.h"
#include "../memory/paging.h"
#include "../util/dbgprinter.h"
#include "../util/printf.h"
#include "../util/string.h"
#include "../io/io.h"
#endif

#define STR_MAX_SIZE 65536

char* odi_dep_itoa(s64 value, int base) {
    #ifdef USE_BMOON
    return itoa(value, base);
    #endif
    #ifdef USE_KOT
    //Kot itoa implementation
    #endif
    //You can implement your own itoa here
}

s64 odi_dep_atoi(const char * str) {
    #ifdef USE_BMOON
    return atoi(str);
    #endif
    #ifdef USE_KOT
    //Kot atoi implementation
    #endif
    //You can implement your own atoi here
}

int odi_dep_strcmp(const char* s1, const char* s2) {
    #ifdef USE_BMOON
    return strcmp(s1, s2);
    #endif
    #ifdef USE_KOT
    //Kot strcmp implementation
    #endif
    //You can implement your own strcmp here
}

int odi_dep_strncmp(const char* s1, const char* s2, int n) {
    #ifdef USE_BMOON
    return strncmp(s1, s2, n);
    #endif
    #ifdef USE_KOT
    //Kot strncmp implementation
    #endif
    //You can implement your own strncmp here
}

void odi_dep_strncpy(char *dest, const char *src, int n) {
    #ifdef USE_BMOON
    return strncpy(dest, src, n);
    #endif
    #ifdef USE_KOT
    //Kot strncpy implementation
    #endif
    //You can implement your own strncpy here
}

int odi_dep_strlen(const char* str) {
    #ifdef USE_BMOON
    return strlen(str);
    #endif
    #ifdef USE_KOT
    //Kot strlen implementation
    #endif
    //You can implement your own strlen here
}

void* odi_dep_malloc(int size) {
    #ifdef USE_BMOON
    return malloc(size);
    #endif
    #ifdef USE_KOT
    //Kot malloc implementation
    #endif
    //You can implement your own malloc here
}

void odi_dep_free(void* ptr) {
    #ifdef USE_BMOON
    free(ptr);
    #endif
    #ifdef USE_KOT
    //Kot free implementation
    #endif
    //You can implement your own free here
}

void odi_dep_map_current_memory_size(void* virtual_address, void* physical_memory, u64 bytes) {
    #ifdef USE_BMOON
    map_current_memory_size(virtual_address, physical_memory, bytes);
    #endif
    #ifdef USE_KOT
    //Kot map_current_memory_size implementation
    #endif
    //You can implement your own map_current_memory_size here
}

void odi_dep_map_current_memory(void* virtual_memory, void* physical_memory) {
    #ifdef USE_BMOON
    map_current_memory(virtual_memory, physical_memory);
    #endif
    #ifdef USE_KOT
    //Kot map_current_memory implementation
    #endif
    //You can implement your own map_current_memory here
}

void odi_dep_outb(u16 port, u8 value) {
    #ifdef USE_BMOON
    outb(port, value);
    #endif
    #ifdef USE_KOT
    //Kot outb implementation
    #endif
    //You can implement your own outb here
}

void odi_dep_outw(u16 port, u16 value) {
    #ifdef USE_BMOON
    outw(port, value);
    #endif
    #ifdef USE_KOT
    //Kot outw implementation
    #endif
    //You can implement your own outw here
}

void odi_dep_outl(u16 port, u32 value) {
    #ifdef USE_BMOON
    outl(port, value);
    #endif
    #ifdef USE_KOT
    //Kot outl implementation
    #endif
    //You can implement your own outl here
}

u8 odi_dep_inb(u16 port) {
    #ifdef USE_BMOON
    return inb(port);
    #endif
    #ifdef USE_KOT
    //Kot inb implementation
    #endif
    //You can implement your own inb here
}

u16 odi_dep_inw(u16 port) {
    #ifdef USE_BMOON
    return inw(port);
    #endif
    #ifdef USE_KOT
    //Kot inw implementation
    #endif
    //You can implement your own inw here
}

u32 odi_dep_inl(u16 port) {
    #ifdef USE_BMOON
    return inl(port);
    #endif
    #ifdef USE_KOT
    //Kot itoa implementation
    #endif
    //You can implement your own inl here
}

void odi_dep_insw(u16 port, u8* buffer, int count) {
    #ifdef USE_BMOON
    insw(port, buffer, count);
    #endif
    #ifdef USE_KOT
    //Kot insw implementation
    #endif
    //You can implement your own insw here
}

void odi_dep_outsw(u16 port, u8 *buffer, int count) {
    #ifdef USE_BMOON
    outsw(port, buffer, count);
    #endif
    #ifdef USE_KOT
    //Kot outsw implementation
    #endif
    //You can implement your own outsw here
}

void odi_dep_io_wait() {
    #ifdef USE_BMOON
    io_wait();
    #endif
    #ifdef USE_KOT
    //Kot io_wait implementation
    #endif
    //You can implement your own io_wait here
}

void odi_dep_vprintf(const char* format, odi_va_list args) {
    #ifdef USE_BMOON
    vprintf(format, args);
    #endif
    #ifdef USE_KOT
    //Kot vprintf implementation
    #endif
    //You can implement your own vprintf here
}

void odi_dep_vsnprintf(char* buffer, int size, const char* format, odi_va_list args) {
    #ifdef USE_BMOON
    vsnprintf(buffer, size, format, args);
    #endif
    #ifdef USE_KOT
    //Kot vsprintf implementation
    #endif
    //You can implement your own vsnprintf here
}

void odi_dep_printf(const char* format, ...) {
    #ifdef USE_BMOON
    odi_va_list args;
    odi_dep_va_start(args, format);
    odi_dep_vprintf(format, args);
    odi_dep_va_end(args);
    #endif
    #ifdef USE_KOT
    //Kot printf implementation
    #endif
    //You can implement your own printf here
}