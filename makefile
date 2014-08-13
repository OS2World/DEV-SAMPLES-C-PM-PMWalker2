walker : walker.exe

walker.exe : walker.obj walker.res walker.def
   link386 /ALIGN:4 /BASE:0x10000 /EXEPACK walker.obj, walker.exe, nul,\
           os2.lib, walker.def
   rc walker.res

walker.obj : walker.c walker.h
   gcc -c -O2 walker.c

walker.res : walker.rc step1.ico step2.ico step3.ico
   rc -r walker.rc
