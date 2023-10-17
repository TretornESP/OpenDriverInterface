#ifndef _ODI_BUS_H
#define _ODI_BUS_H

#define ODI_BUS_TYPE_PCI            0x00
#define ODI_BUS_TYPE_USB            0x01
#define ODI_BUS_TYPE_SATA           0x02
#define ODI_BUS_TYPE_RS232          0x03
#define ODI_BUS_TYPE_NVME           0x04
#define ODI_BUS_TYPE_ISA            0x05
#define ODI_BUS_TYPE_FLOPPY         0x06
#define ODI_BUS_TYPE_UNCLASSIFIED   0xFF

#include "types.h"

struct odi_bus_info {
    u8 type;
    void * address;
    void * driver; 
};

#endif