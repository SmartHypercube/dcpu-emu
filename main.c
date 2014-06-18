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

    read_prog(file);
    fclose(file);

    dcpu_create( &dcpu, mem );

    signal( SIGKILL, _kill );
    signal( SIGTERM, _kill );
    signal( SIGINT, _kill );

    struct timeval start, end;
    while( !dcpu_complete( &dcpu ) && !killed )
    {
        gettimeofday( &start, NULL );
        int ticks = dcpu_tick( &dcpu );

        gettimeofday( &end, NULL );
        int elapsed = (end.tv_sec - start.tv_sec)*1000*1000 + (end.tv_usec - start.tv_usec);

        int to_sleep = 10*ticks - elapsed;

        if( to_sleep > 0 )
        {
            usleep( to_sleep );
        }
    }

    struct pollfd pollinfo[1];
    pollinfo[0].fd = 0;
    pollinfo[0].events = POLLIN;

    dcpu_free( &dcpu );

    return 0;
}
