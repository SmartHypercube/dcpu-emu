#include "keyboard.h"

#define HW_ID       0xec402d15
#define HW_VER      0x0001
#define AUTHOR_ID   0xFA5D0000

typedef struct {
    uint16_t interrupt;
} keyboard_data;

/* Initialize */
void *init_keyboard (void)
{
    void *p = malloc (sizeof (keyboard_data));
    if (p==NULL)
    {
        arch_exit_program ();
        exit (1);
    }
    return p;
}

/* Process a tick */
void tick_keyboard (dcpu16_t *dcpu, dcpu_hardware_t *hardware)
{
    if ( ( (keyboard_data*) hardware->device_data) ->interrupt != 0 )
    
}

/* handle interrupts */
void interrupt_keyboard (dcpu16_t *dcpu, dcpu_hardware_t *hardware)
{
    uint32_t a = dcpu->A;
    uint32_t b = dcpu->B;
    switch (a)
    {
        case 0x0000:
            dcpu->state = HALTING;
            return;
        case 0x0001:
            
    }
}

dcpu_hardware_t* create_keyboard (void)
{
    NEW_HARDWARE (keyboard);
}
