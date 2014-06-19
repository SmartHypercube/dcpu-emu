#include "printer.h"

#define HW_ID       0x475E72C3
#define HW_VER      0x0001
#define AUTHOR_ID   0xFA5D0000

uint8_t buffer[0x10000];

/* Initialize */
void *init_printer (void)
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
    uint32_t a = dcpu->A;
    uint32_t b = dcpu->B;
    uint32_t c = dcpu->C;
    switch (a)
    {
        case 0x0000:
            if ( b+c > 0x10000 )
            {
                dcpu->A = 0xFFFF;
                return;
            }
            dcpu->A = fwrite (dcpu->memory + b, 2*c, 1, stdout);
            fflush (stdout);
            return;
        case 0x0001:
            if ( b+c > 0x10000 )
            {
                dcpu->A = 0xFFFF;
                return;
            }
            uint16_t *p, *end;
            p   = dcpu->memory + b;
            end = dcpu->memory + b+c;
            int i;
            for (i=0 ; p<end; p++, i++)
            {
                buffer[i] = (*p) & 0x00FF;
            }
            dcpu->A = fwrite (buffer, c, 1, stdout);
            fflush (stdout);
            return;
    }
}

/* Create a printer */
dcpu_hardware_t* create_printer (void)
{
    NEW_HARDWARE (printer);
}
