#include <config.h>

/**
 * Declare VM images.
 */
VM_IMAGE(vm1, /path/to/zcu_baremetal_guest/zcu_baremetal_guest.bin);

/**
 * Config each VM.
 */
struct vm_config vm_config = {
    
    VM_CONFIG_HEADER
    
    .vmlist_size = 1,
    .vmlist = {
        { 
            .image = {
                .base_addr = 0x00000000,
                .load_addr = VM_IMAGE_OFFSET(vm1),
                .size = VM_IMAGE_SIZE(vm1)
            },

            .entry = 0x00000000,

            .platform = {
                .cpu_num = 4,
                
                .region_num = 1,
                .regions =  (struct mem_region[]) {
                    {
                        .base = 0x00000000,
                        .size = 0x10000000 // 256MB
                    }
                },

                .dev_num = 2,
                .devs =  (struct dev_region[]) {
                    {   
                        /* uart 1 */
                        .pa = 0xFF010000,
                        .va = 0xFF010000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = 
                            (uint64_t[]) {54}                         
                    },
                    {   
                        /* generic timer interrupt */
                        .interrupt_num = 1,
                        .interrupts = 
                            (uint64_t[]) {27}                         
                    },
                },

                .arch = {
                    .gic = {
                        .gicc_addr = 0xF9020000,
                        .gicd_addr = 0xF9010000
                    }
                }
            },
        }
    },
};