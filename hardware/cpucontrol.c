#include "cpucontrol.h"

#define HW_ID       0x06b09c12
#define HW_VER      0x0001
#define AUTHOR_ID   0xFA5D0000

/* Initialize */
void *init_cpucontrol (void)
{
    return NULL;
}

/* Process a tick */
void tick_cpucontrol (dcpu16_t *dcpu, dcpu_hardware_t *hardware)
{
}

/* handle interrupts */
void interrupt_cpucontrol (dcpu16_t *dcpu, dcpu_hardware_t *hardware)
{
    uint32_t a = dcpu->A;
    switch (a)
    {
        case 0x0000:
            dcpu->state = HALTING;
            return;
    }
}

/* Create a printer */
dcpu_hardware_t* create_cpucontrol (void)
{
    NEW_HARDWARE (cpucontrol);
}
