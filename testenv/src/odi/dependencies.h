#ifndef _ODI_DEPENDENCIES_H
#define _ODI_DEPENDENCIES_H

#include <stdarg.h>

typedef va_list odi_va_list;

int odi_dep_strcmp(const char* str1, const char* str2);
int odi_dep_strncmp(const char* str1, const char* str2, int n);
int odi_dep_strlen(const char* str);

void* odi_dep_malloc(int size);
void odi_dep_free(void* ptr);

void odi_dep_vprintf(const char* format, odi_va_list args);
void odi_dep_vsnprintf(char* buffer, int size, const char* format, odi_va_list args);
void odi_dep_printf(const char* format, ...);

//va_start, va_end, va_arg
#define odi_dep_va_start va_start
#define odi_dep_va_end va_end
#define odi_dep_va_arg va_arg

#endif