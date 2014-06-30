#include "linux.h"

void arch_begin_program ()
{
    system ("stty -icanon -echo");
}

void arch_exit_program ()
{
    system ("stty -raw echo");
}
