#include "odi.h"
#include "dependencies.h"
#include "debug.h"

struct odi_driver_info odi_list_drivers();
bool odi_register_driver(struct odi_driver_info driver);

struct odi_bus_info odi_list_buses();
bool odi_register_bus(struct odi_bus_info bus);

void odi_hello() {
    odi_debug_append(ODI_DTAG_INFO, "Hello from ODI!\n");
    odi_debug_flush(ODI_DTAG_INFO);
}