#ifndef _ODI_DEPENDENCIES_H
#define _ODI_DEPENDENCIES_H

#include "types.h"

#include <stdarg.h>
typedef va_list odi_va_list;

//Conversion management.
char* odi_dep_itoa(s64, int);
s64 odi_dep_atoi(const char * str);

//String management.
int odi_dep_strcmp(const char* str1, const char* str2);
int odi_dep_strncmp(const char* str1, const char* str2, int n);
int odi_dep_strlen(const char* str);
void odi_dep_strncpy(char *dest, const char *src, int n);

//Heap management.
void* odi_dep_malloc(int size);
void odi_dep_free(void* ptr);

//Virtual memory management.
//Here the current makes reference to the current process (pml4).
//Maps n bytes (starting at page aligned virtual_address) to physical_memory.
void odi_dep_map_current_memory_size(void* virtual_address, void* physical_memory, u64 bytes);
//Maps the page aligned virtual_address to physical_memory.
void odi_dep_map_current_memory(void* virtual_memory, void* physical_memory);

//Print management.
void odi_dep_vprintf(const char* format, odi_va_list args);
void odi_dep_vsnprintf(char* buffer, int size, const char* format, odi_va_list args);
void odi_dep_printf(const char* format, ...);

//IO Management. Usually an embedded assembly line does the trick.
void odi_dep_outb(u16 port, u8 value);
void odi_dep_outw(u16 port, u16 value);
void odi_dep_outl(u16 port, u32 value);
u8 odi_dep_inb(u16 port);
u16 odi_dep_inw(u16 port);
u32 odi_dep_inl(u16 port);
void odi_dep_insw(u16 port, u8* buffer, int count);
void odi_dep_outsw(u16 port, u8 *buffer, int count);
void odi_dep_io_wait();

//va_start, va_end, va_arg
#define odi_dep_va_start va_start
#define odi_dep_va_end va_end
#define odi_dep_va_arg va_arg

#endif