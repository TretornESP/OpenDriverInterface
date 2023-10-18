#include "dependencies.h"
#include "types.h"

#ifdef USE_BMOON
#include "../memory/heap.h"
#include "../util/printf.h"
#include "../util/string.h"
#endif

#define STR_MAX_SIZE 65536

int odi_dep_strcmp(const char* s1, const char* s2) {
    #ifdef USE_BMOON
    return strcmp(s1, s2);
    #endif

    //You can implement your own strcmp here
}

int odi_dep_strncmp(const char* s1, const char* s2, int n) {
    #ifdef USE_BMOON
    return strncmp(s1, s2, n);
    #endif

    //You can implement your own strncmp here
}

int odi_dep_strlen(const char* str) {
    #ifdef USE_BMOON
    return strlen(str);
    #endif

    //You can implement your own strlen here
}

void* odi_dep_malloc(int size) {
    #ifdef USE_BMOON
    return malloc(size);
    #endif

    //You can implement your own malloc here
}

void odi_dep_free(void* ptr) {
    #ifdef USE_BMOON
    free(ptr);
    #endif

    //You can implement your own free here
}

void odi_dep_vprintf(const char* format, odi_va_list args) {
    #ifdef USE_BMOON
    vprintf(format, args);
    #endif

    //You can implement your own vprintf here
}
void odi_dep_vsnprintf(char* buffer, int size, const char* format, odi_va_list args) {
    #ifdef USE_BMOON
    vsnprintf(buffer, size, format, args);
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

    //You can implement your own printf here
}