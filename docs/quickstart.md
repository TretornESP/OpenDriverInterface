# Quickstart Guide

To get started with OpenDriverInterface, follow these steps:

## Installation

1. First, make sure you have all the dependencies installed as specified in [dependencies.md](dependencies.md).

## Running the Example

1. Clone this repository and navigate to the `testenv` directory.

    ```bash
    git clone https://github.com/your-repo.git
    cd your-repo/testenv
    ```

2. Setup the environment using `make`:

    ```bash
    make setup
    ```

3. Run the software:

    ```bash
    make
    ```

## Implementing the Library

If you want to integrate our library into your own operating system or project, you can do so by following these steps:

1. Copy the contents of the `source` folder to your project.

2. Implement the necessary functions in `dependencies.c` according to your operating system's requirements.

3. Include the `odi.h` header (and any other that you may need) in your source files and use the library as described in the [usage](#usage) section.

## Usage

### Fully Managed (PCI Devices Only)

If you want to use the fully managed mode for PCI devices, you should provide the RSDT (Root System Description Table) pointer to the `odi_start_managed` function. Here's how you can use it:

```c
// Include the necessary headers
#include "odi.h"

// Provide the RSDT pointer
void* rsdt_pointer = /* your RSDT pointer */;

// Start in fully managed mode
odi_start_managed(rsdt_pointer);

// Get the number of devices
uint32_t device_count = odi_get_device_count();

// Create a buffer to store the device information
struct odi_device_info* devices = malloc(sizeof(struct odi_device_info) * device_count);

// Get the device information
if (!odi_get_devices(devices, device_count)) {
    // Handle error
}

uint32_t device_id = /* your device ID */;

// Get a specific device by its ID (you can also access the devices array directly)
struct odi_device_info* device = odi_get_device(device_id);

// Get the driver associated with the device
struct odi_driver_info* driver = odi_get_driver(device);

// Call any function on the driver
driver->function(device, /* additional parameters */);

### How to get the RSDT pointer with limine

First of all, you may want to get the RSDT without limine, thats absolutely possible. [See how](https://wiki.osdev.org/RSDP#Detecting_the_RSDP)

Else, you should clone limine, copy the .EFI file to your image, create the limine.cfg file. An example [Here](https://github.com/limine-bootloader/limine-barebones)

You can check the limine boot protocol documentation [Here](https://github.com/limine-bootloader/limine/blob/v5.x-branch/PROTOCOL.md)

Then basically you have to copy the [limine.h](https://raw.githubusercontent.com/limine-bootloader/limine/v5.x-branch/limine.h) file to your source.

And request the rsdp with this code fragment:

```c
static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

uint64_t get_rsdp_address() {
    return (uint64_t)(rsdp_request.response)->address;
}
```

### Manual mode

In this mode you have to provide the device information manually. Each one is slightly different, so you should check the documentation for each one.

There are a few fields that are always required, though:

- `u8 valid`: A sanity flag. If this is set to 0, the device will be ignored.
- `u32 major`: The device driver identifier. This is used to identify the device type. See the [device types](#device-types) section for more information.
- `u32 minor`: The device identifier inside that specific type. See [device identification](#device-identification) for more information.	
- `void* control`: This field depends on the device type. See [device control](#device-control) for more information.

You may register the device with the `odi_register_device` function.

### Driver registration

For rolling your own driver, fill the following structure:

```c
struct odi_driver_info {
    u8 type;
    u32 major;
    void * functions; //This can be any kind of driver function, usually generic_driver_functions
    u8 license;
    u8 vendor[24];
};
```

And implement as many functions as you wish in the functions struct. The default one is:

```c
struct generic_driver_functions {
    void * (*init)(struct odi_device_info * device, void* iobuff);
    void * (*exit)(struct odi_device_info * device, void* iobuff);
    void * (*read)(struct odi_device_info * device, void* iobuff, u64 read_size, u64 read_offset);
    void * (*write)(struct odi_device_info * device, void* iobuff, u64 write_size, u64 write_offset);
    void * (*ioctl)(struct odi_device_info * device, void* iobuff, u64 operation);
};

```

If you use managed mode, you should encapsulate all advanced operations in the ioctl function, and use the read and write functions for basic operations.

### Device types

The device type is a 32-bit integer that identifies the driver that will handle this device. The following types are currently supported:

- `ODI_MAJOR_TTY`: tty device.
- `ODI_MAJOR_SERIAL`: serial device.
- `ODI_MAJOR_ATA`: ATA device.
- `ODI_MAJOR_ATAPI`: ATAPI device.
- `ODI_MAJOR_USB`: USB device.
- `ODI_MAJOR_NETWORK`: PCI network card device.
- `ODI_MAJOR_PS2_KEYBOARD`: PS2 Keyboard device.
- `ODI_MAJOR_PCI`: GenericPCI device.

### Device identification

The identification usually is made by a id string calculated from the major and minor numbers. 

For example, the major number for a tty device is `ODI_MAJOR_TTY` which has the assotiated string "tty". The minor number will be
converted to a letter and concatenated. So the device with major `ODI_MAJOR_TTY` and minor `0` will be identified as `ttya`.

You can get the id string with the `odi_get_device_id` function.

### Device control

The control field is a pointer to a structure that contains the device-specific information. For example, for a tty device, it will contain the tty buffer and the tty type. For a PCI device, it will contain the PCI device information. This will be used internally by the driver to perform the operations.


### Special cases.

There are a few edge cases like network controllers where the r/w/ioctl scheme doesn't make sense, here we specify an alternative driver functions struct.