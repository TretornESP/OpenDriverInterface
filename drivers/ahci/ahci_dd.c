#include "ahci_dd.h"
#include "../../odi/debug.h"
#include "../../odi/driver.h"

void * ata_init(struct odi_driver_info * self, void* iobuff) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA INIT\n");
    return 0;
}

void * ata_exit (struct odi_driver_info * self, void* iobuff) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA EXIT\n");
    return 0;
}

void * ata_read (struct odi_driver_info * self, void* iobuff, u32 minor, u64 read_size, u64 read_offset) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA READ\n");
    return 0;
}

void * ata_write (struct odi_driver_info * self, void* iobuff, u32 minor, u64 write_size, u64 write_offset) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA WRITE\n");
    return 0;
}

void * ata_ioctl (struct odi_driver_info * self, void* iobuff, u32 minor, u64 operation) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA IOCTL\n");
    return 0;
}

void * atapi_init(struct odi_driver_info * self, void* iobuff) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI INIT\n");
    return 0;
}

void * atapi_exit (struct odi_driver_info * self, void* iobuff) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI EXIT\n");
    return 0;
}

void * atapi_read (struct odi_driver_info * self, void* iobuff, u32 minor, u64 read_size, u64 read_offset) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI READ\n");
    return 0;
}

void * atapi_write (struct odi_driver_info * self, void* iobuff, u32 minor, u64 write_size, u64 write_offset) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI WRITE\n");
    return 0;
}

void * atapi_ioctl (struct odi_driver_info * self, void* iobuff, u32 minor, u64 operation) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI IOCTL\n");
    return 0;
}

struct odi_driver_functions ata_ops = {
    .init = ata_init,
    .exit = ata_exit,
    .read = ata_read,
    .write = ata_write,
    .ioctl = ata_ioctl
};

struct odi_driver_functions atapi_ops = {
    .init = atapi_init,
    .exit = atapi_exit,
    .read = atapi_read,
    .write = atapi_write,
    .ioctl = atapi_ioctl
};

void init_ata(void) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA REGISTER STARTED\n");
    struct odi_driver_info * driver = odi_driver_register(DISK_ATA_DD_MAJOR, (void*)&ata_ops, DISK_DD_LICENSE, DISK_DD_VENDOR);
    if (driver == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "AHCI DRIVER ATA REGISTER FAILED\n");
        return;
    }

    ((struct odi_driver_functions*)driver->functions)->init(driver, 0);

    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA REGISTER FINISHED\n");
}

void exit_ata(void) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA UNREGISTER STARTED\n");
    struct odi_driver_info * driver = odi_driver_get(DISK_ATA_DD_MAJOR);
    if (driver == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "AHCI DRIVER ATA UNREGISTER FAILED\n");
        return;
    }

    ((struct odi_driver_functions*)driver->functions)->exit(driver, 0);

    if (odi_driver_unregister(DISK_ATA_DD_MAJOR)) {
        odi_debug_append(ODI_DTAG_ERROR, "AHCI DRIVER ATA UNREGISTER FAILED\n");
        return;
    }

    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATA UNREGISTER FINISHED\n");
}

void init_atapi(void) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI REGISTER STARTED\n");
    struct odi_driver_info * driver = odi_driver_register(DISK_ATAPI_DD_MAJOR, (void*)&atapi_ops, DISK_DD_LICENSE, DISK_DD_VENDOR);
    if (driver == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "AHCI DRIVER ATAPI REGISTER FAILED\n");
        return;
    }

    ((struct odi_driver_functions*)driver->functions)->init(driver, 0);

    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI REGISTER FINISHED\n");
}

void exit_atapi(void) {
    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI UNREGISTER STARTED\n");
    struct odi_driver_info * driver = odi_driver_get(DISK_ATAPI_DD_MAJOR);
    if (driver == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "AHCI DRIVER ATAPI UNREGISTER FAILED\n");
        return;
    }

    ((struct odi_driver_functions*)driver->functions)->exit(driver, 0);

    if (odi_driver_unregister(DISK_ATAPI_DD_MAJOR)) {
        odi_debug_append(ODI_DTAG_ERROR, "AHCI DRIVER ATAPI UNREGISTER FAILED\n");
        return;
    }

    odi_debug_append(ODI_DTAG_INFO, "AHCI DRIVER ATAPI UNREGISTER FINISHED\n");
}