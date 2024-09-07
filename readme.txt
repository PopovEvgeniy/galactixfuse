                       Galactix fuse
                          
                       Version 0.7.1.1

            Resource extraction tool for Galactix by Popov Evgeniy Alekseyevich

System requirements

64 kilobytes of free space on storage media.

Description and usage

Galactix is an old scroll shooter by Cygnus Studios. This game stores resources in GLB pseudo–archives.
Do you want to extract files from these pseudo–archives? You can use my software for doing it.
This software intends for Galactix version 1.3.
This program takes a target file name and output path as command-line arguments.
Always add a directory separator (\ or /) at the end of the output path.

Exit codes

0 – Operation successfully completed.
1 – Can't open input file.
2 – Can't create output file.
3 – Can't jump to target offset.
4 – Can't allocate memory.
5 – Invalid format.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The source code was compiled under Open Watcom.
But you can compile it under any modern C compiler.
Source code can be compiled for a wide  range of operating systems, but you need to create makefile or build script by yourself.
I provide only two things: the binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to installation: make install
Run as root to uninstall: make uninstall

Contact

You can send me a letter at tuzik87@inbox.ru.

Version history

0.1 – Initial version.
0.2 – 0.3 – Small bug fixed.
0.4 – 0.6.2 – Small changes.
0.6.2.1 – Makefile updated.
0.6.3 – 0.6.4 – Small bug fixed.
0.6.5 – Small changes.
0.6.6 – 0.6.7 – Small bug fixed.
0.6.8 – 0.7 – Small changes.
0.7.1 – Visual C++ support improved.
0.7.1.1 – Documentation updated.