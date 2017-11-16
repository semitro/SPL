#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>

#include <math.h>

#include "image.h"
#include "transform.h"

#define MAX_X_COLOR_NUMBER 65535
#define MAX_IMG_PIXEL_COLOR_NUMBER 255
#define BOTTOM_SLIDER_ALIGN 20
#define SLIDER_POINT_WIDE	17
#define SLIDER_MAX			6.28318530718

Display *dis;
int screen;
Window win;
GC gc;



void start_GUI();
void set_img(struct image *img);

#endif // MAIN_WINDOW

