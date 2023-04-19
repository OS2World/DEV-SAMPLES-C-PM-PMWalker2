# DEV-SAMPLE-PM-PMWalker2
PMWalker2 - How to make an animated icon 

LICENSE
===============
* 3-Clause BSD License

COMPILE TOOLS
===============
* GCC, Make, OS2 Tooklit, BinUtils
* yum install git gcc make libc-devel binutils 

COMPILE INSTRUCTIONS
===============
This version of this sample was modified to compile on ArcaOS with GCC 9 compiler. 
1) Remember to have correct OS/2 toolkit header files your path. For GCC the correct ones are the included on the "libc-devel", not the ones from the OS/2 Toolkit.
2) Run "make" or "make 2>&1 |tee make.out" to get the log file.
3) If you want to use an open source linker like wl.exe, remember to include SET EMXOMFLD_LINKER=wl.exe and SET EMXOMFLD_TYPE=WLINK on the config.sys or when you start the session.
 
AUTHORS
===============
* Martin Iturbide
* David Charlap

LINKS
===============
* 
