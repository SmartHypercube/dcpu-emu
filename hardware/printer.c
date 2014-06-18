#include "printer.h"

#define HW_ID       0x475E72C3
#define HW_VER      0x0001
#define AUTHOR_ID   0xFA5D0000

/* interrupt types */
#define PRINTER_PRINT 0

/* Initialize */
printer_t *init_printer (void)
{
    return NULL;
}

/* Process a tick */
void tick_printer (dcpu16_t *dcpu, dcpu_hardware_t *hardware)
{
}

/* handle interrupts */
void interrupt_printer (dcpu16_t *dcpu, dcpu_hardware_t *hardware)
{
    switch ( dcpu->A )
    {
        case PRINTER_PRINT:

            break;
    }
}

/* Create a printer */
dcpu_hardware_t* create_printer (void)
{
    NEW_HARDWARE (printer);
}

