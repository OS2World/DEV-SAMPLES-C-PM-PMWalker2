/* WALKER.C - Sample Animated Icon Program   */
/* Copyright (C) Lee S. Fields, 1989         */

/*
 * The following changes were made from the original sources by David Charlap
 * in November, 1992 to get walker to run under OS/2 2.0 and compile with
 * GCC/2:
 *
 * The Msg parameter of ClientWndProc changed from USHORT to ULONG
 * Prototype for ClientWndProc moved to walker.h, where it belongs.
 * Instances of NULL changed to NULLHANDLE where necessary.  This should have
 *     been done under OS/2 1.3, since NULL is a pointer and NULLHANDLE is
 *     an integer.
 * More frame creation flags added to get the window to appear.
 * WinSetWindowPosition() call added to make window visible and active
 * WM_PAINT handler added so the window fills in white instead of being
 *     left not drawn
 * walker.def modified - export changed to _ClientWndProc, since GCC/2
 *     prepends an underscore to EXPENTRY code, contrary to IBM convention.
 * Icons updated to OS/2 2.0 format, 16x16 icons added so the walking man in
 *     the system menu box looks OK.
 * A make file was written.
 *
 */

#define INCL_WIN
#define INCL_GPICONTROL

#include <os2.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "walker.h"

HAB hab;
HMQ hmq;
HWND hwndClient, hwndFrame;
QMSG qmsg;

CHAR szCaption[80] = "Walker";

int main (int argc, char *argv[]) {
  static CHAR szClientClass[] = "Walker";

  ULONG flFrameFlags = FCF_ICON | FCF_SYSMENU | FCF_SIZEBORDER | FCF_MINMAX |
                       FCF_TITLEBAR | FCF_TASKLIST | FCF_SHELLPOSITION;

  ULONG flFrameStyle = WS_VISIBLE;

  hab = WinInitialize (0);
  hmq = WinCreateMsgQueue (hab, 0);
  WinRegisterClass (hab, szClientClass, ClientWndProc, CS_SIZEREDRAW, 0);
  hwndFrame = WinCreateStdWindow (HWND_DESKTOP, flFrameStyle,
				  &flFrameFlags, szClientClass,
				  szCaption, 0L, NULLHANDLE,
				  IDP_STEP1, &hwndClient);
  WinSetWindowPos (hwndFrame, HWND_TOP, 0L, 0L, 0L, 0L,
		   SWP_SHOW | SWP_ZORDER | SWP_ACTIVATE );
  
  while (WinGetMsg (hab, &qmsg, NULLHANDLE, 0, 0))
    WinDispatchMsg (hab, &qmsg);
  
  WinDestroyWindow (hwndFrame);
  WinDestroyMsgQueue (hmq);
  WinTerminate (hab);
  return 0;
}

MRESULT EXPENTRY ClientWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
  static HPOINTER step[IDP_STEP4];
  static SHORT counter = IDP_STEP1;
  HPS hps;

  switch (msg) {
  case WM_CREATE:
    for (counter = IDP_STEP1; counter <= IDP_STEP4; counter++)
      step[counter] = WinLoadPointer (HWND_DESKTOP, NULLHANDLE, counter);
    if (!WinStartTimer (hab, hwnd, ID_TIMER, 333)) {
      WinMessageBox (HWND_DESKTOP, hwnd, "Too many timers",
		     szCaption, 0, MB_OK | MB_ICONEXCLAMATION);
      WinPostMsg (hwnd, WM_QUIT, 0L, 0L);
    }
    return 0;

  case WM_PAINT:
    hps = WinBeginPaint(hwnd, NULLHANDLE, NULL);
    GpiErase(hps);
    WinEndPaint (hps);
    return 0;

  case WM_TIMER:
    if (counter > IDP_STEP4)
      counter = IDP_STEP1;

    WinSendMsg (hwndFrame, WM_SETICON, MPFROMLONG(step[counter]), NULL);
    WinInvalidateRect (hwndFrame, NULL, FALSE);
    counter++;
    return 0;

  case WM_DESTROY:
    WinStopTimer (hab, hwnd, ID_TIMER);
    for (counter = IDP_STEP1; counter <= IDP_STEP4; counter++)
      WinDestroyPointer (step[counter]);
    return 0;
  }
  return WinDefWindowProc (hwnd, msg, mp1, mp2);
}
