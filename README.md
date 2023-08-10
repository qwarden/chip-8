# Quimby's CHIP-8 Interpreter
This repo contains an implementation of the chip-8 interpreter based on
[this](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) specification.
The specification page is also saved in the `spec` directory.

## Getting Started
This project uses GNU Make as its build system. To build the binary run
`make` in the root directory.

You can then run the interpreter from the project root like so:

```bash
bin/chip-8 programs/wait_for_key.bin
```

There is currently one example program attached but I plan on working on
more in the future including a pong game. 

## chex.py
chex.py is a simple python script in the `programs` directory which will convert 
an ASCII text file containing hex characters and python style comments into raw 
hex bytes. This allows for primative editing of chip-8 programs until I get around 
to writing an assembler.
