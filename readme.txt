                       Galactix fuse
                          
                       Version 0.7.4

            Resource extraction tool for Galactix by Popov Evgeniy Alekseyevich

System requirements

32 kilobytes of free space on storage media.

Description and usage

Galactix is an old scroll shooter by Cygnus Studios. This game stores resources in GLB pseudo-archives.
Do you want to extract files from these pseudo-archives? You can use my software for doing it.
This software is intended for Galactix version 1.3.
This program takes a target file name and an output path as the command-line arguments.
Always add a directory separator (\ or /) at the end of the output path.

Exit codes

0: Operation was successfully completed.
1: Can't open the input file.
2: Can't create the output file.
3: Can't jump to the target offset.
4: Can't allocate memory.
5: Invalid format.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The source code was compiled under Tiny C Compiler.
But you can compile it with any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Contact

You can send me a letter at tuzik87@inbox.ru.

Version history

0.1: Initial version.
0.2-0.3: A small bug has been fixed.
0.4-0.6.2: The small changes.
0.6.2.1: The makefile has been updated.
0.6.3-0.6.4: The small bug has been fixed.
0.6.5: The small changes.
0.6.6-0.6.7: A small bug has been fixed.
0.6.8-0.7: The small changes.
0.7.1: Visual C++ support has improved.
0.7.1.1: The documentation has been updated.
0.7.2: The small changes.
0.7.2.1-0.7.2.2: The documentation has been updated.
0.7.3: The source code was recompiled under Tiny C Compiler.
0.7.4: The small changes.