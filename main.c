#include "main.h"

uint16_t mem[0x10000];

int killed = 0;
void _kill( int x )
{
    killed = 1;
}

void read_prog( FILE *file )
{
    int i;
    for ( i=0; !feof(file) && i<0x20000 ; i++ )
    {
        fread ( ((uint8_t*)mem)+i , 1, 1, file);
    }
}

void reg_debug( dcpu16_t *dcpu )
{
    /* data registers */
    printf( " A=0x%04x  B=0x%04x  C=0x%04x \n X=0x%04x  Y=0x%04x  Z=0x%04x \n I=0x%04x  J=0x%04x\n",
            dcpu->A, dcpu->B, dcpu->C, dcpu->X, dcpu->Y, dcpu->Z, dcpu->I, dcpu->J);

    /* state/extra */
    printf( "PC=0x%04x SP=0x%04x EX=0x%04x IA=0x%04x \nIAQ=0x%04x clocks=%i\tstate=%s\n",
            dcpu->PC, dcpu->SP, dcpu->EX, dcpu->IA, dcpu->IAQ, dcpu->clocks, state_strs[dcpu->state]);

    printf( "\n" );
}

int main( int argc, char ** argv )
{
    dcpu16_t dcpu;
    dcpu_inst_t *inst;

    if( argc != 2 )
    {
        printf( "Usage: %s file.bin\n", argv[0] );
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if( !file )
    {
        perror(argv[1]);
        return 1;
    }

    read_prog(file);
    fclose(file);

    dcpu_create( &dcpu, mem );

    signal( SIGKILL, _kill );
    signal( SIGTERM, _kill );
    signal( SIGINT, _kill );

    struct timeval start, end;
    while( !dcpu_complete( &dcpu ) && !killed )
    {
        int ticks = dcpu_tick( &dcpu );
        reg_debug ( &dcpu );
        sleep (1);
    }

    struct pollfd pollinfo[1];
    pollinfo[0].fd = 0;
    pollinfo[0].events = POLLIN;

    printf("Run complete press enter to exit..."); fflush(stdout);

    dcpu_free( &dcpu );

    return 0;
}
