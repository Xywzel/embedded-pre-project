This is preproject demonstration for embedded systems
=====================================================

Requirements
------------
Following packages are needed in unix eniviroment to use this project.
gcc-avr | Compiler and other utilities
avr-libc | C libraries
avrdude | Used to program the AVR device
yaamake | Required to use projects `Makefile`. Packages for yaamake are in [github source](https://github.com/raphendyr/yaamake)

Files
-----

### .gitignore

This file contains files to be ignored by git. These files contain build result and other binary files. You should not put this type of files in git.

### Makefile

`Makefile` contains definitions and rules for the `make` program. This project uses `yaamake` to do all the heavy lifting so the `Makefile` is quite sort. More information and configuration variables can be viewed with `make help`.

When you change the `demo.c` filename to something else or add another source file, you need to edit `SRC` line in this file.

### Makefile.alternative

This is an alternative makefile that can be used without yaamake. If you want to use this instead the former, then rename this file to `Makefile` (overwrite the other file). If you dom't want to replace the other you can run `make -f Makefile.alternative` instead of `make`.

You can use this makefile if you don't want to or can't use yaamake.

### demo.c

This contains most of the source code for the pre-project.

Yaamake makefile usage
----------------------

Makefile uses yaamake makefile system to simplify things. Yaamake contains all the information how to do things and `Makefile` only configurations for them.

### Actions

command | description
--: | ---
`make` | runs `make build`
`make build` | compiles and links your source files
`make clean` | removes all build files (created by above command)
`make program_check` | validate that avr device is connected and is programmable
`make program` | program the AVR board (remember to connect the usb cable first)
`make help` | yaamake's help message about these commands and variables to be defined in `Makefile`
`make listen` | can be used to open serial listener (can be used to listen serial bytes send from your avr program. For that you need to implement USART functions. google `avr usart`)


### Created files

All of this files are more or less useless to you. Basically these are used to get your code to the actual aVR device. You get rid of these by running `make clean`

This files are listed here, to give some reference.

command | description
--: | ---
`simpleled.elf` | Binary in ELF format (result of compiling and linking)
`simpleled.hex` | Binary in hex format (raw binary bytes as hex). This is used to program the device.
`simpleled.lss` | Disassembly (assembly code matched to your c code) Some what human readable, compared to elf and hex.
`simpleled.map` | Object map
`simpleled.sym` | Symbol map
`.cache/*` | Build support files (object files, dependencies, etc.)


Alternative makefile
--------------------

Alternative makefile is easy to extend, but offers less features. It is totally sufficient to pass the project.

### Actions

command | description
--: | ---
`make` | compiles and links your source files
`make clean` | removes all build files (created by above command)
`make program_check` | validate that avr device is connected and is programmable
`make program` | program the AVR board (remember to connect the usb cable first)
`make sizedummy` | prints some size statistics of your binary

### Created files

command | description
--: | ---
`simpleled.elf` | same as above
`simpleled.hex` | same as above
`simpleled.d` | source file dependencies for Makefile
`simpleled.o` | compiled source file (object file)
