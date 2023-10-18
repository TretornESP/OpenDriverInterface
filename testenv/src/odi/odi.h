#ifndef _ODI_H
#define _ODI_H

#include "types.h"
#include "driver.h"
#include "bus.h"

struct odi_driver_info odi_list_drivers();
bool odi_register_driver(struct odi_driver_info driver);

void odi_start_managed(void * rdsp);

struct odi_bus_info odi_list_buses();
bool odi_register_bus(struct odi_bus_info bus);

void odi_hello();


#endif