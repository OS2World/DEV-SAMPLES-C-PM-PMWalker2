# nmake makefile
#
# Tools used:
#  Compile::Resource Compiler
#  Compile::GNU C
#  Make: nmake or GNU make
all : walker.exe

walker.exe : walker.obj walker.res walker.def
	gcc -Zomf walker.obj walker.def -o walker.exe
	rc walker.res

walker.obj : walker.c walker.h
	gcc -Wall -Zomf -c -O2 walker.c -o walker.obj

walker.res : walker.rc step1.ico step2.ico step3.ico
	rc -r walker.rc

clean :
	rm -rf *exe *RES *obj