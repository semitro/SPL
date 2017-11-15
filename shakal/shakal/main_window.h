#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stddef.h>
#include <stdlib.h>

Display *dis;
int screen;
Window win;
GC gc;

void window_go();

#endif // MAIN_WINDOW

