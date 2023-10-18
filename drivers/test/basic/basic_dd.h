#ifndef _AHCI_DD_H
#define _AHCI_DD_H

#include "../../../odi/driver.h"
#include "../../../odi/types.h"

#define IOCTL_BASIC_SAY_HI   0x1
#define IOCTL_BASIC_BE_BAD   0x2


#define BASIC_DD_LICENSE ODI_LICENSE_TYPE_MIT
#define BASIC_DD_VENDOR "OPENDRIVERINTERFACE\0"

#define BASIC_DD_NAME "DUMMY DRIVER\0"
#define BASIC_DD_MAJOR 255

void init_basic(void);
void exit_basic(void);
#endif