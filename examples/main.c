#include "../source/odi.h"
#include "../source/debug.h"

int main(int argc, char* argv[]) {
    odi_debug_append(ODI_DTAG_INFO, "Hello, world!");
    odi_debug_flush(ODI_DTAG_INFO);
    return 0;
}