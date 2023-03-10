                       Galactix fuse
                          
                       Version 0.6.8

            Resource extraction tool for Galactix by Popov Evgeniy Alekseyevich

System requirement

48 kilobytes free space on storage media.

Description and usage

Galactix is old scroll-shooter by Cygnus Studios. This game store resources in FILE0001.GLB and FILE0002.GLB files.
Do you want to extract files from these pseudo-archives? You can use my software for doing it.
This software intends for DOS version of Galactix.
This program takes a target file name and output path as command line arguments.
Always add directory separator(\ or /) at the end of output path.

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create output file.
3 - Can't jump to target offset.
4 - Can't allocate memory.
5 - Invalid format.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The program source code was compiled under Open Watcom.
But you can do it under any modern C compiler.
Source code can be compiled for wide range operating systems, but you need to create makefile or build script by yourself.
I provide only two things: compiled the binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run as root for installation: make install
Run as root for uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

0.1 - Initial version.
0.2 - 0.3 - Small bug fixed.
0.4 - 0.6.2 - Small changes.
0.6.2.1 - Makefile updated.
0.6.3 - 0.6.4 - Small bug fixed.
0.6.5 - Small changes.
0.6.6 - 0.6.7 - Small bug fixed.
0.6.8 - Small changes.