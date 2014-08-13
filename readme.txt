PMWALKER2 - one way to get an animated icon

The following changes were made from the original sources (Lee S.
Fields, 1989) in November, 1992 to get walker to run under OS/2 2.0
and compile with GCC/2:

The Msg parameter of ClientWndProc changed from USHORT to ULONG
Prototype for ClientWndProc moved to walker.h, where it belongs.
Instances of NULL changed to NULLHANDLE where necessary.  This should have
    been done under OS/2 1.3, since NULL is a pointer and NULLHANDLE is
    an integer.
More frame creation flags added to get the window to appear.
WinSetWindowPosition() call added to make window visible and active
WM_PAINT handler added so the window fills in white instead of being
    left not drawn
walker.def modified - export changed to _ClientWndProc, since GCC/2
    prepends an underscore to EXPENTRY code, contrary to IBM convention.
Icons updated to OS/2 2.0 format, 16x16 icons added so the walking man in
    the system menu box looks OK.
A make file was written.

This program is now a 32-bit app which will only run under OS/2 2.0.
It was compiled with GCC/2, but it should easilly compile with C Set/2
or EMX/GCC with a minor change to the .DEF file.

With minor changes, it should compile fine under OS/2 1.x as well.
These changes include converting the icons (*.ICO) from 2.0 format to
1.2 format, and changing the Msg parameter to ClientWndProc from a
ULONG to a USHORT.

--- David Charlap
    dic5340@hertz.njit.edu
