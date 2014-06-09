#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>

#include "dcpu.h"
#include "hardware/sdl.h"
#include "hardware/LEM1802.h"
#include "hardware/generic_keyboard.h"
#include "hardware/generic_clock.h"

/* makeup of an instruction */
typedef union {
    uint16_t all;
    struct {
        uint16_t o : 5;
        uint16_t b : 5;
        uint16_t a : 6;
    };
} dcpu_inst_t;
