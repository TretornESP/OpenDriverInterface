#include "basic.h"
#include "basic_dd.h"

#include "../../../odi/debug.h"
#include "../../../odi/driver.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

void * basic_init(struct odi_driver_info * self, void* iobuff) {
    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER INIT\n");

    return 0;
}

void * basic_exit (struct odi_driver_info * self, void* iobuff) {
    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER EXIT\n");
    return 0;
}

void * basic_read (struct odi_driver_info * self, void* iobuff, void* control, u64 read_size, u64 read_offset) {
    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER READ\n");
    return 0;
}

void * basic_write (struct odi_driver_info * self, void* iobuff, void* control, u64 write_size, u64 write_offset) {
    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER WRITE\n");
    return 0;
}

void * basic_ioctl (struct odi_driver_info * self, void* iobuff, void* control, u64 operation) {
    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER IOCTL\n");

    return 0;
}

struct odi_driver_functions basic_ops = {
    .init = basic_init,
    .exit = basic_exit,
    .read = basic_read,
    .write = basic_write,
    .ioctl = basic_ioctl
};

void init_basic(void) {
    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER REGISTER STARTED\n");
    struct odi_driver_info * driver = odi_driver_register(BASIC_DD_MAJOR, (void*)&basic_ops, BASIC_DD_LICENSE, BASIC_DD_VENDOR);
    if (driver == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "BASIC DRIVER REGISTER FAILED\n");
        return;
    }

    ((struct odi_driver_functions*)driver->functions)->init(driver, 0);

    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER REGISTER FINISHED\n");
}

void exit_basic(void) {
    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER UNREGISTER STARTED\n");
    struct odi_driver_info * driver = odi_driver_get(BASIC_DD_MAJOR);
    if (driver == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "BASIC DRIVER UNREGISTER FAILED\n");
        return;
    }

    ((struct odi_driver_functions*)driver->functions)->exit(driver, 0);

    if (odi_driver_unregister(BASIC_DD_MAJOR)) {
        odi_debug_append(ODI_DTAG_ERROR, "BASIC DRIVER UNREGISTER FAILED\n");
        return;
    }

    odi_debug_append(ODI_DTAG_INFO, "BASIC DRIVER UNREGISTER FINISHED\n");
}