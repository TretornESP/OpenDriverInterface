#ifndef _ODI_DRIVER_H
#define _ODI_DRIVER_H

#define ODI_DRIVER_TYPE_GRAPHICS        0x00
#define ODI_DRIVER_TYPE_AUDIO           0x01
#define ODI_DRIVER_TYPE_LAN             0x02
#define ODI_DRIVER_TYPE_USB             0x03
#define ODI_DRIVER_TYPE_STORAGE         0x04
#define ODI_DRIVER_TYPE_WIFI            0x05
#define ODI_DRIVER_TYPE_BLUETOOTH       0x06
#define ODI_DRIVER_TYPE_RGB             0x07
#define ODI_DRIVER_TYPE_UNCLASSIFIED    0xFF

#include "types.h"

struct odi_driver_info {
    u8 type;
    void * functions; //This can be any kind of driver function, usually generic_driver_functions
    u8 license;
    u8 vendor[24];
};

struct generic_driver_functions {
    void * (*init)(struct odi_driver_info * self, void* iobuff);
    void * (*exit)(struct odi_driver_info * self, void* iobuff);
    void * (*read)(struct odi_driver_info * self, void* iobuff, u64 read_size, u64 read_offset);
    void * (*write)(struct odi_driver_info * self, void* iobuff, u64 write_size, u64 write_offset);
    void * (*ioctl)(struct odi_driver_info * self, void* iobuff, u64 operation);
};

#endif