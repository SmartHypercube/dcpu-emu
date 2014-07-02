DCPU16-Emulator
===============

This is an *command line based* emulator for the
DCPU-16 CPU (1.7) of the game [0x10c][x].

[x]: http://0x10c.com

Project source code can be found at:
[github.com/fasd21/dcpu-emu][g]

[g]: https://github.com/fasd21/dcpu-emu

**Note:** This file has a Chinese (Simple) version,
which is [README.zh-CN.md][r].

[r]: https://github.com/fasd21/dcpu-emu/blob/master/README.zh-CN.md

Features
--------

### designed for dcpu16 operating system

The most important feature is this emulator is
*designed for OS*, as many people like to write complex
programs on it. This means I will try my best to make
it *robust* and *fast*, also, design many *useful
hardwares* for it.

### robustness

In some programs, we may want to `SUB PC,1` to wait for
an interrupt or disk loading. I found that many
emulators will stop running when meet `SUB PC,1`.
That's terrible. Also, sometimes we may run `0x0000`,
printing an error message (instead of ignoring it) is
also bad.

This emulator will *never* print something or stop
running, *unless* this action is a hardware's function.

Also, for this reason, I removed the `ON FIRE` state.

### fast mode

This emulator will work in *fast mode*, which means it
won't have frequency control, and I'm still trying to
speed up it.

### all-in-C, all-for-basic-Linux, all-for-commandline

*   all codes follows C99
*   only support Linux
*   don't need any other libs
*   the least screen/mouse needs

*Note:* I'm using an Android device, these features
make it possible to build ot on my phone -- so I
believe it can be build in any Linux system.

### support forever

...and welcome any contributions!

Story
-----

I knew the DCPU-16 by the Android APP "ADCPU" (Android
package name: `uk.co.sticksoft.adce`). I love this
thing and wrote an OS for it happily. But I was very
sad when I found that ADCPU have a bug which broke the
floppy disk hardware.

Now, I want to make a tiny but *reliable* DCPU-16
emulator, in C and works on command line, and keep
updating. I will be grateful if anyone likes my work.

Note: I forked [github.com/Imajie/dcpu-emu][i].

[i]: https://github.com/Imajie/dcpu-emu

Fasd Snake <fasd.snake@gmail.com>

This project uses *Semantic versioning*. See <http://semver.org> for more information.
