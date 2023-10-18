#ifndef _AHCI_DD_H
#define _AHCI_DD_H

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "../../odi/driver.h"

#define IOCTL_ATAPI_IDENTIFY   0x1
#define IOCTL_GENERIC_STATUS   0x2
#define IOCTL_INIT             0x3
#define IOCTL_CTRL_SYNC        0x4
#define IOCTL_CTRL_TRIM        0x5
#define IOCTL_GET_SECTOR_SIZE  0x6
#define IOCTL_GET_SECTOR_COUNT 0x7
#define IOCTL_GET_BLOCK_SIZE   0x8

#define DISK_DD_LICENSE ODI_LICENSE_TYPE_MIT
#define DISK_DD_VENDOR "OPENDRIVERINTERFACE\0"

#define DISK_ATA_DD_NAME "ATA DRIVER\0"
#define DISK_ATA_DD_MAJOR 8

#define DISK_ATAPI_DD_NAME "ATAPI DRIVER\0"
#define DISK_ATAPI_DD_MAJOR 9

void init_ata(void);
void exit_ata(void);

void init_atapi(void);
void exit_atapi(void);
#endif