#ifndef _ODI_H
#define _ODI_H

#include "core/types.h"
#include "core/driver.h"
#include "core/device.h"

//Only in automatic mode
u32 odi_discover_devices();
u32 odi_discover_drivers();

//Both available in manual and automatic mode
void * odi_manual_device_register(u32 major, void* control);
u8 odi_manual_device_unregister(u32 major, u32 minor);

//Operations
u64 odi_read(const char * device, u64 offset, u64 size, void * buffer);
u64 odi_write(const char * device, u64 offset, u64 size, void * buffer);
u64 odi_ioctl(const char * device, u64 operation, void * buffer);

//Debug
void odi_list_devices();
void odi_list_drivers();
void odi_hello();

#endif