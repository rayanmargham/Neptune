# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := Neptune.elf

# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
# change this to the path to your cross compiler.
CC := /home/guy/osdev/cross/bin/x86_64-elf-gcc
CC_ASM := /usr/bin/nasm
# Likewise, "ld" here is just a placeholder and your mileage may vary if using the
# host's "ld".

LD := /home/guy/osdev/cross/bin/x86_64-elf-ld

 
# User controllable CFLAGS.
CFLAGS ?= -O2 -g -Wall -Wextra -Wpedantic -pipe
ASMFLAGS ?= -f elf64
# User controllable linker flags. We set none by default.
LDFLAGS ?=
 
# Internal C flags that should not be changed by the user.
override INTERNALCFLAGS :=   \
	-I.                  \
	-std=c2x             \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-stack-check     \
	-fno-pic             \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD				 \
	-w 					 \
	-O2                  \
    -Wall                \
    -Wextra              \
	-Isrc/lai/include/
 
# Internal linker flags that should not be changed by the user.
override INTERNALLDFLAGS :=    \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static
 
# Use find to glob all *.c files in the directory and extract the object names.
override CFILES := $(shell find ./ -type f -name '*.c')
# get asm stub files
override ASMSTUB := $(shell find ./ -type f -name '*.s')
override OBJ := $(CFILES:.c=.o)
override HEADER_DEPS := $(CFILES:.c=.d)
override OBJ_ASM := $(ASMSTUB:.s=.o)
override HEADER_DEPS_ASM := $(ASMSTUB:.s=.d)
override CARGOPROJECTFOLDERS := $(shell find ./ -type f -name '*Cargo.toml' -exec dirname {} \;)
 
# Default target.
.PHONY: all
all: $(KERNEL)
 
# Link rules for the final kernel executable.
$(KERNEL): $(OBJ) $(OBJ_ASM)
	@make crust
ifneq "$(CARGOPROJECTFOLDERS)" ""
	$(LD) $(OBJ) $(OBJ_ASM) $(CARGOPROJECTFOLDERS)/target/x86_64-unknown-none/release/libcrust.a $(LDFLAGS) $(INTERNALLDFLAGS) -o $@
else
	$(LD) $(OBJ) $(OBJ_ASM) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@
endif
crust:
ifneq "$(CARGOPROJECTFOLDERS)" ""
	@echo "compiling crust :trl:"
	cargo +nightly build --release --manifest-path $(CARGOPROJECTFOLDERS)/Cargo.toml
endif
# Compilation rules for *.c files.
-include $(HEADER_DEPS)
%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@
-include $(HEADER_DEPS_ASM)
%.o: %.s
	$(CC_ASM) $(ASMFLAGS) -s $< -o $@
.PHONY: everything
everything:
	@echo "---OS BUILD START!---"
	@echo "---BUILDING THE KERNEL---"
	@make
	@echo "---KERNEL BUILD COMPLETE---"
	@echo "---PERFORMING STAGE2---"
	@make stage2
	@echo "---STAGE2 COMPLETE---"
	@echo "OS BUILT WITH NO ERRORS!"
	@echo "---OS BUILD COMPLETE---"
.PHONY: upsubs
upsubs:
	@echo "Updating Github SubModules..."
	@git submodule foreach git pull origin master
	@echo "SubModules Updated!"
.PHONY: run
run:
	@echo "---RUNNING---"
	@qemu-system-x86_64 image.iso -serial stdio -enable-kvm -m 3G -smp 2 -bios /usr/share/ovmf/OVMF.fd -machine q35
	@echo "---RUNNING FINISHED---"
.PHONY: debug_run
debug_run:
	@echo "---RUNNING---"
	@qemu-system-x86_64 image.iso -serial stdio	-d int -m 3G -smp 2 -no-reboot -no-shutdown -gdb tcp::1234 -S -bios /usr/share/ovmf/OVMF.fd -machine q35 -D qemu_log.txt
	@echo "---RUNNING FINISHED---"
# Remove object files and the final executable.
.PHONY: clean
clean:
ifeq "$(wildcard $(KERNEL))" "$(KERNEL)"
	@echo "Removing Kernel and object files..."
	@rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)
	@echo "Done!"
else
	@echo "No kernel or object files to clean, Skipping..."
endif
ifneq "$(wildcard *.iso)" ""
	@echo "Removing image.iso"
	@rm -rf *.iso
	@echo "Done!"
else
	@echo "No image to clean, Skipping..."
endif
ifeq "$(wildcard limine)" "limine"
	@echo "Removing the Limine Folder"
	@rm -rf limine
	@echo "Done!"
else
	@echo "No limine folder to clean, Skipping..."
endif
ifeq "$(wildcard iso_root)" "iso_root"
	@echo "Removing the iso_root Folder"
	@rm -rf iso_root
	@echo "Done!"
else
	@echo "No iso_root folder to clean, Skipping..."
endif
	@echo "---LEFTOVER CLEANUP---"
ifneq "$(wildcard *.d)" ""
	@echo "Removing .d files"
	@rm -rf *.d
	@echo "Done!"
else
	@echo "No .d files to clean, Skipping..."
endif
ifneq "$(wildcard *.o)" ""
	@echo "Removing .o files"
	@rm -rf *.o
	@echo "Done!"
else
	@echo "No .o files to clean, Skipping..."
endif
ifneq "$(wildcard *.a)" ""
	@echo "Removing .a files"
	@rm -rf *.a
	@echo "Done!"
else
	@echo "No .a files to clean, Skipping..."
endif
	@echo "---LEFTOVER CLEANUP---"
stage2:
	@echo "---STAGE 2---"
	@./stage2.sh
	@echo "---STAGE 2---"
