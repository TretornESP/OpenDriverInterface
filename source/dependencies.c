#include "dependencies.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"

int odi_dep_strcmp(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}
int odi_dep_strncmp(const char* str1, const char* str2, int n) {
    return strncmp(str1, str2, n);
}

void* odi_dep_malloc(int size) {
    return malloc(size);
}
void odi_dep_free(void* ptr) {
    free(ptr);
}

void odi_dep_vprintf(const char* format, odi_va_list args) {
    vprintf(format, args);
}
void odi_dep_vsnprintf(char* buffer, int size, const char* format, odi_va_list args) {
    vsnprintf(buffer, size, format, args);
}
void odi_dep_printf(const char* format, ...) {
    odi_va_list args;
    odi_dep_va_start(args, format);
    odi_dep_vprintf(format, args);
    odi_dep_va_end(args);
}