#ifndef _AHCI_DD_H
#define _AHCI_DD_H

//This is a sample device driver, it contains the basic
//strcture to create a device driver. It is not intended
//to be used in production, but rather as a reference.

//This file is just the compatibility layer between the real
//driver and ODI. The real driver is basic.h and basic.c


//You don't have to use this headers, it is only here
//For portability reasons (type abstraction)
#include "../../../core/types.h"

//Export codes for IOCTL calls (again, optional)
#define IOCTL_BASIC_SAY_HI   0x1
#define IOCTL_BASIC_BE_BAD   0x2

//This is required, export the driver name, major number
//and license type. This is used by the driver manager.
#define BASIC_DD_LICENSE    ODI_LICENSE_TYPE_MIT
#define BASIC_DD_VENDOR     "OPENDRIVERINTERFACE\0"
#define BASIC_DD_NAME       "DUMMY DRIVER\0"
#define BASIC_DD_MAJOR      255

//This is a way to pack the initialization and exit
//routines of the driver. It is not required.
void init_basic(void);
void exit_basic(void);
#endif