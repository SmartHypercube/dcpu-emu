#include "main.h"

uint16_t mem[0x10000];

void _kill (int x)
{
    arch_exit_program ();
    exit (1);
}

void read_prog( FILE *file )
{
    int i;
    for ( i=0; !feof(file) && i<0x20000 ; i++ )
    {
        fread ( ((uint8_t*)mem)+i , 1, 1, file);
    }
}

int main( int argc, char ** argv )
{
    dcpu16_t dcpu;
    dcpu_inst_t *inst;

    if( argc != 2 )
    {
        fprintf (stderr, "Usage: %s file.bin\n", argv[0] );
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if( !file )
    {
        perror(argv[1]);
        return 1;
    }

    arch_begin_program ();

    signal (SIGKILL, _kill);
    signal (SIGTERM, _kill);
    signal (SIGINT,  _kill);

    read_prog(file);
    fclose(file);

    dcpu_create( &dcpu, mem );

    dcpu_add_hardware (&dcpu, create_printer ());
    dcpu_add_hardware (&dcpu, create_cpucontrol ());

    struct timeval start, end;
    while ( ! dcpu_complete (&dcpu) )
    {
        gettimeofday( &start, NULL );
        int ticks = dcpu_tick( &dcpu );

        gettimeofday( &end, NULL );
        int elapsed = (end.tv_sec - start.tv_sec)*1000*1000 + (end.tv_usec - start.tv_usec);

        int to_sleep = 10*ticks - elapsed;

        if( to_sleep > 0 && to_sleep <100 )
        {
            usleep( to_sleep );
        }
    }

    dcpu_free( &dcpu );

    arch_exit_program ();

    return 0;
}
