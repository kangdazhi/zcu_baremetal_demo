# Bao Hypervisor - ZCU10X bare metal guest demo

This demo showcases a multi-core bare-metal guest running over the bao
hypervisor in one of the Xilinx ZCU boards.
The guest cpu 0 sets up a 1Hz timer interrupt and forwards an IPI to the next
core in each tick.
Each time a core receives an IPI it forwards the same IPI to next core.
Also, a uart RX interrupt is setup that can be forward to any of the active cores.

## 1) Download firmware

Download latest pre-built zynqmp firmware and bootloader 20xx.x-zcu10x-release.tar.xz:
 * https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842316/Zynq+Releases

Alternatively you can build the FSBL, pmu firmware, arm trusted firmware and u-boot from source and generate BOOT.BIN from your own .bif file using xilinx's bootgen. Follow:
 * https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841722/ZCU102+Image+creation+in+OSL+flow
OR
 * https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18841738/Getting+Started in "Building Linux Yourself (DIY)"

## 2) Build the bare metal app

`cd zcu_baremetal_guest`\
`export CROSS_COMPILE=toolchain-prefix-`\
`make`


## 6) Download bao

`cd ..`\
`git clone https://github.com/bao-project/bao-hypervisor.git`


## 7) Setup bao configuration

Copy the provided configuration to bao's tree.

`cp -r configs/zcu_baremetal_demo bao-hypervisor/configs`

Setup the vm image binary paths in *bao-hypervisor/configs/zcu_baremetal_demo/config.c*:

`VM_IMAGE(vm1, /path/to/zcu_baremetal_guest/zcu_baremetal_guest.bin);`


## 8) Compile bao and configuration

`cd bao-hypervisor`\
`export CROSS_COMPILE=toolchain-prefix-`\
`make PLATFORM=zcu10x CONFIG=zcu_baremetal_demo`

If anything goes wrong:

`make PLATFORM=zcu10x CONFIG=zcu_baremetal_demo clean`\
`make PLATFORM=zcu10x CONFIG=zcu_baremetal_demo`


## 9) Create bao u-boot image

Make sure you have u-boot-tools installed. In bao top-level directory run:

`mkimage -n bao_uboot -A arm64 -O linux -C none -T kernel -a 0x100000 -e 0x100000 -d bin/zcu10x/bao.bin baoImage`


## 10) Setup SD card

Copy the following files to the bootable partition:

* *BOOT.BIN*
* *bao-hypervisor/baoImage*
* *bao-hypervisor/configs/zcu_baremetal_demo/zcu_baremetal_demo.bin*


## 11) Setup board

First make sure you have the board configured to boot from the SD card.
Connect to both UARTs available on the zcu (baud 115200).


## 12) Run u-boot commands

`fatload mmc 0 0x100000 baoImage`\
`fatload mmc 0 0x200000 zcu_baremetal_demo.bin`\
`bootm start 0x100000 - 0x200000`\
`bootm loados`\
`bootm go`

## Tools versions
 * 2019.1-zcu10x-release.tar.xz
 * dtc 1.4.5
 * aarch64-elf-gcc (GNU Toolchain for the A-profile Architecture 8.2-2019.01 (arm-rel-8.28)) 8.2.1 20180802 (https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)
 * mkimage version 2018.07-rc3+dfsg1-0ubuntu3~18.04.1


