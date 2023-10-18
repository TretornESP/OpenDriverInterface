# EDIT THIS LINES
#########################DESKTOP SETTINGS##################################
QEMU := "/mnt/c/Program Files/qemu/qemu-system-x86_64.exe"
GDB := gdb
###########################################################################

override KERNEL := kernel.elf
override ISO := limine-cd.iso
override IMG := limine-cd.img
override VDI := limine-cd.vdi
override IMG_RAW := raw.img
override LIMINECFG := limine.cfg
override GDBCFG := debug.gdb

CC := /usr/bin/cc
LD := /usr/bin/ld
LMN := limine/limine-deploy.exe
BOOTEFI := ./limine/BOOTX64.EFI
ASMC := nasm

ABSDIR := $(shell pwd)
ODIDIR := $(ABSDIR)/../source
DRVDIR := $(ABSDIR)/../drivers
LMNDIR := limine
OVMFDIR := OVMFbin
SRCDIR := src
BUILDHOME := build
BUILDDIR := build/bin
OBJDIR := build/lib
ISOBUILDDIR := build/iso_root
ISODIR := build/image
MNTDIR := $(ABSDIR)/mounts
SYSDIR := $(MNTDIR)/system
DATDIR := $(MNTDIR)/data
FSDIR := $(ABSDIR)/filesystem
DIRS := $(wildcard $(SRCDIR)/*)

LMNREPO := https://github.com/limine-bootloader/limine.git
LMNBRCH := v3.0-branch-binary
OVMFREPO := https://github.com/Absurdponcho/OVMFbin
OVMFBRCH := main

CMDNEWSCREEN := cmd.exe /c start cmd /c wsl -e
KERNEL_ENTRY := _start
BLOCKSIZE := 1024
MEMSIZE := 1024
VMEMSIZE := 128
QFLAGS ?= -cpu qemu64 -d cpu_reset -machine q35 -m $(MEMSIZE) -boot d -serial stdio -serial telnet::4444,server,nowait -cdrom 
QFLAGSEXP ?= -cpu qemu64 -d cpu_reset -machine q35 -m $(MEMSIZE) -boot d -drive if=pflash,format=raw,unit=0,file=./OVMFbin/OVMF_CODE-pure-efi.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=./OVMFbin/OVMF_VARS-pure-efi.fd -serial stdio -device e1000,mac=51:52:53:54:55:56 -drive file=
CFLAGS ?= -O2 -g -Wall -Wextra -pipe -std=c11
NASMFLAGS ?= -F dwarf -g
LDFLAGS ?=
CPPFLAGS ?=
GDBFLAGS ?=  --nx --command=$(GDBCFG)
GDBPORT ?= 1234

WSLHOSTIP := $(shell ipconfig.exe | grep 'vEthernet (WSL)' -a -A4 | tail -n1 | cut -d":" -f 2 | tail -n1 | sed -e 's/\s*//g')
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Check that given variables are set and all have non-empty values,
# die with an error otherwise.
#
# Params:
#   1. Variable name(s) to test.
#   2. (optional) Error message to print.
check_defined = \
    $(strip $(foreach 1,$1, \
        $(call __check_defined,$1,$(strip $(value 2)))))
__check_defined = \
    $(if $(value $1),, \
      $(error Undefined $1$(if $2, ($2))))

override CFLAGS +=       \
    -I.                  \
    -std=c11             \
	-DUSE_BMOON		     \
    -ffreestanding       \
    -fno-stack-protector \
    -fno-stack-check     \
    -fno-pie             \
    -fno-pic             \
    -m64                 \
    -march=x86-64        \
    -mabi=sysv           \
    -mno-80387           \
    -mno-red-zone        \
    -mcmodel=kernel      \
    -MMD
override CFLAGS += $(CEXTRA)

override LDFLAGS +=         \
    -nostdlib               \
    -static                 \
    -z max-page-size=0x1000 \
    -T linker.ld

override NASMFLAGS += \
    -f elf64

override CFILES :=$(call rwildcard,$(SRCDIR),*.c)        
override ASFILES := $(call rwildcard,$(SRCDIR),*.S)
override NASMFILES := $(call rwildcard,$(SRCDIR),*.asm)
override OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CFILES))
override OBJS += $(patsubst $(SRCDIR)/%.S, $(OBJDIR)/%_s.o, $(ASFILES))
override OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%_asm.o, $(NASMFILES))
override HEADER_DEPS := $(CFILES:.c=.d) $(ASFILES:.S=.d)

all:
	@make copy
	@make kernel
	@make ccopy
	@echo "Building GPT..."
#This is required to be before buildimggpt!
	@cp $(ISODIR)/$(IMG_RAW) $(ISODIR)/$(IMG)
	@sudo losetup -f $(ISODIR)/$(IMG)
# Due to eval weird behaviour
	@make buildimggpt
	@echo "Running GPT QEMU..."
	@make run
	@echo "Done!"

kernel: $(OBJS) link

$(OBJDIR)/io/interrupts.o: $(SRCDIR)/io/interrupts.c
#	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	@$(CC) $(CFLAGS) -mgeneral-regs-only -c $^ -o $@

$(OBJDIR)/drivers/serial/serial.o: $(SRCDIR)/drivers/serial/serial.c
#	@ echo !==== COMPILING $^ with -mgeneral-regs-only
	@ mkdir -p $(@D)
	@$(CC) $(CFLAGS) -mgeneral-regs-only -c $^ -o $@

$(OBJDIR)/util/dbgprinter.o: $(SRCDIR)/util/dbgprinter.c
#	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	@$(CC) $(CFLAGS) -mgeneral-regs-only -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
#	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
#	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	@$(ASMC) $^ -felf64 -o $@

$(OBJDIR)/%_s.o: $(SRCDIR)/%.S
#	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	@$(ASMC) $(NASMFLAGS) $^ -f elf64 -o $@

copy:
	@echo !==== COPYING FILES
	@rm -rf $(SRCDIR)/odi
	@rm -rf $(SRCDIR)/drivers
	@cp -a $(ODIDIR)/. $(SRCDIR)/odi/
	@cp -a $(DRVDIR)/. $(SRCDIR)/drivers/
	@tree $(SRCDIR)/

ccopy:
	@rm -rf $(SRCDIR)/odi
	@rm -rf $(SRCDIR)/drivers

link: 
#	@ echo !==== LINKING $^
	@$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)

clean:
	@rm -rf $(OBJDIR)/*
	@rm -rf $(OBJS)
	@rm -f $(ISOBUILDDIR)/$(KERNEL)
	@rm -f $(ISOBUILDDIR)/$(LIMINECFG)
	@rm -f $(BUILDDIR)/$(KERNEL)
	@rm -f $(ISODIR)/$(IMG)
	@rm -f $(ISODIR)/$(ISO)
	@rm -f $(ISODIR)/$(VDI)

setup:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(ISOBUILDDIR)
	@mkdir -p $(ISODIR)
	@dd if=/dev/zero of=$(ISODIR)/$(IMG_RAW) bs=4096 count=102400
	@git clone $(OVMFREPO) --branch=$(OVMFBRCH) --depth=1
	@git clone $(LMNREPO) --branch=$(LMNBRCH) --depth=1
	@cp -v $(LMNDIR)/limine.sys $(LMNDIR)/limine-cd.bin $(LMNDIR)/limine-cd-efi.bin $(ISOBUILDDIR)
	@echo file $(ABSDIR)/$(BUILDDIR)/$(KERNEL) > debug.gdb
	@echo target remote $(WSLHOSTIP):$(GDBPORT) >> debug.gdb
	@echo set disassembly-flavor intel >> debug.gdb
	@echo b $(KERNEL_ENTRY) >> debug.gdb
	@echo c >> debug.gdb

cleansetup:
	@rm -rf $(BUILDHOME)
	@rm -f debug.gdb
	@rm -rf $(LMNDIR)
	@rm -rf $(OVMFDIR)

buildimggpt:

	$(eval LOOP_DEV_PATH := $(shell losetup -a | grep $(IMG) | cut -d: -f1))
	@echo Loop device path: $(LOOP_DEV_PATH)
	
	@sudo sgdisk --new 1:0:+50M --typecode 1:ef00 $(LOOP_DEV_PATH)
	@sudo sgdisk --new 2:0:0  -t 2:8300 $(LOOP_DEV_PATH)
	@sudo sgdisk -p $(LOOP_DEV_PATH)
	@sudo partprobe $(LOOP_DEV_PATH)
	@sudo fdisk -l $(LOOP_DEV_PATH)
	@sudo mkfs.fat -n PATATA -F32 $(LOOP_DEV_PATH)p1
	@sudo mkfs.ext2 -L FDATA2 $(LOOP_DEV_PATH)p2 -b $(BLOCKSIZE)
	@sudo mkdir $(MNTDIR)
	@sudo mkdir $(SYSDIR)
	@sudo mkdir $(DATDIR)

	@sudo mount $(LOOP_DEV_PATH)p1 $(SYSDIR)

	@echo Disk mounted, creating system files
	@sudo mkdir -p $(SYSDIR)/efi/boot
	@sudo mkdir -p $(SYSDIR)/test

	@sudo cp $(BOOTEFI) $(SYSDIR)/efi/boot
	@sudo cp ./startup.nsh $(SYSDIR)
	@sudo cp $(BUILDDIR)/$(KERNEL) $(SYSDIR)
	@sudo cp ./limine.cfg $(SYSDIR)
	@sudo umount $(SYSDIR)


	@echo Creating ext2 data files
	@sudo mount $(LOOP_DEV_PATH)p2 $(DATDIR)
	@sudo cp -r $(FSDIR) $(DATDIR)
	@sudo tree $(FSDIR)
	@sudo umount $(DATDIR)

	@sudo rm -rf $(MNTDIR)
	@sudo losetup -d $(LOOP_DEV_PATH)

run:
	$(QEMU) $(QFLAGSEXP)$(ISODIR)/$(IMG)

help:
	@echo To build the kernel, first setup it with
	@echo make setup
	@echo Then build and run it with
	@echo make
	@echo .
	@echo To re-run the kernel, just run
	@echo make run
	@echo .
	@echo Before submitting changes run make clean
	@echo and make cleansetup
	@echo .
	@echo To fix a bad build, please run:
	@echo sudo mount
	@echo Find any mounted device on the mounts folder
	@echo umount it with sudo umount \<folder\>
	@echo Then run: sudo losetup -l
	@echo and unmap the loop device with sudo losetup -d \<loop device\>
	@echo Next remove the mounts folder with sudo rm -rf \<mounts folder\>
	@echo Finally run: make clean

debug:
	@echo "WARNING: RIGHT NOW ONLY WSL DEBUGGING IS SUPPORTED"
	@make copy
	@make kernel
	@echo "Building GPT..."
#This is required to be before buildimggpt!
	@cp $(ISODIR)/$(IMG_RAW) $(ISODIR)/$(IMG)
	@sudo losetup -f $(ISODIR)/$(IMG)
# Due to eval weird behaviour
	@make buildimggpt
	@make rundebug
	@make ccopy

rundebug:
	@echo "Running GPT QEMU..."
	$(CMDNEWSCREEN) $(GDB) $(GDBFLAGS) &
	$(QEMU) -S -s $(QFLAGSEXP)$(ISODIR)/$(IMG)