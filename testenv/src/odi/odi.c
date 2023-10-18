#include "odi.h"
#include "dependencies.h"
#include "debug.h"
#include "config.h"

const char* MAJOR_PREFIXES[ODI_MAX_MAJORS] = {
    [0x0 ... 0x7] = "none",
    [8] = "hd",   // 8
    [9] = "cd",   // 9
    [0xa] = "semb", // a
    [0xb] = "pm",   // b
    [0xc] = "umsd", // c
    [0xd] = "usb", // d
    [0xe] = "tty", // e
    [0xf] = "kbd", // f
    [0x10] = "mouse", // 10
    [0x11] = "net", // 11
    [0x12 ... ODI_MAX_MAJORS - 1] = "none",
};

struct identifier {
    u32 major;
    u32 minor;
};

u8 convert_name(const char * name , struct identifier * identifier) {
    //Get last character of name
    char last = name[odi_dep_strlen(name) - 1];
    //The minor is the last character converted to a number
    if (last >= '0' && last <= '9') {
        identifier->minor = last - '0';
    } else if (last >= 'a' && last <= 'z') {
        identifier->minor = last - 'a' + 10;
    } else if (last >= 'A' && last <= 'Z') {
        identifier->minor = last - 'A' + 10;
    } else {
        return 0;
    }

    //The major is the rest of the name as an index into MAJOR_PREFIXES
    u32 length = odi_dep_strlen(name);
    char major[length];
    odi_dep_strncpy(major, name, length - 1);

    for (u32 i = 0; i < ODI_MAX_MAJORS; i++) {
        if (odi_dep_strcmp(major, MAJOR_PREFIXES[i]) == 0) {
            identifier->major = i;
            return 1;
        }
    }

    return 0;
}

//Only in automatic mode
u32 odi_discover_devices() {
    odi_debug_append(ODI_DTAG_INFO, "ODI DISCOVER DEVICES REQUEST\n");
    odi_debug_append(ODI_DTAG_ERROR, "Not implemented yet\n");
    return 0;
}

u32 odi_discover_drivers() {
    odi_debug_append(ODI_DTAG_INFO, "ODI DISCOVER DRIVERS REQUEST\n");
    odi_debug_append(ODI_DTAG_ERROR, "Not implemented yet\n");
    return 0;
}

//Both available in manual and automatic mode
struct odi_device_info * odi_manual_device_register(u32 major, void* control) {
    odi_debug_append(ODI_DTAG_INFO, "ODI MANUAL DEVICE REGISTER REQUEST\n");
    return odi_device_register(major, control);
}

u8 odi_manual_device_unregister(u32 major, u32 minor) {
    odi_debug_append(ODI_DTAG_INFO, "ODI MANUAL DEVICE UNREGISTER REQUEST\n");
    return odi_device_unregister(major, minor);
}

//Operations
u64 odi_read(const char * device, u64 offset, u64 size, void * buffer) {
    odi_debug_append(ODI_DTAG_INFO, "ODI READ REQUEST\n");
    struct identifier identifier;
    if (convert_name(device, &identifier) == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "ODI READ FAILED, DEVICE %s NOT FOUND\n", device);
        return 0;
    }

    struct odi_device_info * device_info = odi_device_get(identifier.major, identifier.minor);
    if (device_info == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "ODI READ FAILED\n");
        return 0;
    }

    //TODO: Make this return the number of bytes read
    ((struct odi_driver_functions*)device_info->control)->read(device_info->control, buffer, device_info->minor, size, offset);

    return 1;
}

u64 odi_write(const char * device, u64 offset, u64 size, void * buffer) {
    odi_debug_append(ODI_DTAG_INFO, "ODI WRITE REQUEST\n");
    struct identifier identifier;
    if (convert_name(device, &identifier) == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "ODI WRITE FAILED, DEVICE %s NOT FOUND\n", device);
        return 0;
    }

    struct odi_device_info * device_info = odi_device_get(identifier.major, identifier.minor);
    if (device_info == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "ODI WRITE FAILED\n");
        return 0;
    }

    //TODO: Make this return the number of bytes written
    ((struct odi_driver_functions*)device_info->control)->write(device_info->control, buffer, device_info->minor, size, offset);

    return 1;
}

u64 odi_ioctl(const char * device, u64 operation, void * buffer) {
    odi_debug_append(ODI_DTAG_INFO, "ODI IOCTL REQUEST\n");
    struct identifier identifier;
    if (convert_name(device, &identifier) == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "ODI IOCTL FAILED, DEVICE %s NOT FOUND\n", device);
        return 0;
    }

    struct odi_device_info * device_info = odi_device_get(identifier.major, identifier.minor);
    if (device_info == 0) {
        odi_debug_append(ODI_DTAG_ERROR, "ODI IOCTL FAILED\n");
        return 0;
    }

    ((struct odi_driver_functions*)device_info->control)->ioctl(device_info->control, buffer, device_info->minor, operation);

    return 1;
}

//Debug
void odi_list_devices() {
    odi_debug_append(ODI_DTAG_INFO, "ODI LIST DEVICES REQUEST\n");
    for (int i = 0; i < ODI_MAX_MAJORS; i++) {
        struct odi_device_info * device = odi_device_getall(i);
        if (device == 0) continue;
        odi_debug_append(ODI_DTAG_INFO, "[DUMPING MAJOR %d]\n", i);
        
        while (device != 0) {
            odi_debug_append(ODI_DTAG_INFO, "[DEVICE] MAJ: %d | MIN: %d | VALID: %d | CONTROL: %p | NEXT: %p] \n", device->major, device->minor, device->valid, device->control, device->next);
            device = odi_device_next(device);
        }
    }
    odi_debug_flush(ODI_DTAG_INFO);
}

void odi_list_drivers() {
    odi_debug_append(ODI_DTAG_INFO, "ODI LIST DRIVERS REQUEST\n");
    for (int i = 0; i < ODI_MAX_MAJORS; i++) {
        struct odi_driver_info * driver = odi_driver_get(i);
        if (driver == 0) continue;
        odi_debug_append(ODI_DTAG_INFO, "[DRIVER] MAJ: %d | VALID: %d |  FUNCTIONS: %p | LICENSE: %d | VENDOR: %s | NEXT: %p] \n", driver->major, driver->valid, driver->functions, driver->license, driver->vendor, driver->next);
    }
    odi_debug_flush(ODI_DTAG_INFO);
}

void odi_hello() {
    odi_debug_append(ODI_DTAG_INFO, "Hello from ODI!\n");
    odi_debug_flush(ODI_DTAG_INFO);
}