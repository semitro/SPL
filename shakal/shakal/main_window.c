#include "main_window.h"

void window_go(){
	dis = XOpenDisplay((char*)0);
	screen = DefaultScreen(dis);
	unsigned long black=BlackPixel(dis,screen);	/* get color black */
	unsigned long white=WhitePixel(dis, screen);  /* get color white */

	win = XCreateSimpleWindow(dis,DefaultRootWindow(dis), 0, 0, 200, 300, 5, black,black );
	/* here is where some properties of the window can be set.
		   The third and fourth items indicate the name which appears
		   at the top of the window and the name of the minimized window
		   respectively.
		*/
	XSetStandardProperties(dis,win,"My Window","HI!",None,NULL,0,NULL);

	/* this routine determines which types of input are allowed in
	   the input.  see the appropriate section for details...
	*/
	XSelectInput(dis, win, StructureNotifyMask | ExposureMask|ButtonPressMask|KeyPressMask);

	/* create the Graphics Context */
	gc=XCreateGC(dis, win, 0,0);

	/* here is another routine to set the foreground and background
	   colors _currently_ in use in the window.
	*/
	XSetBackground(dis,gc,black);
	XSetForeground(dis,gc,white);

	// max - from zero to max
        Colormap colormap= XDefaultColormap(dis,screen);
        //XStandardColormap color_map = *XAllocStandardColormap();

	XMapWindow  (dis, win);

	for(;;) {
		XEvent e;
		XNextEvent(dis, &e);
		if (e.type == MapNotify)
			break;
	}
	/* clear the window and bring it on top of the other windows */
	XColor color;
		color.blue = 65524;
	color.green = 54;
		color.red = 655;
	color.flags = DoBlue | DoRed | DoGreen;
	XAllocColor(dis, colormap, &color);

        XSetForeground(dis, gc, color.pixel);


			XDrawLine(dis,win,gc,0,0,10000,10000);

	XFlush(dis);

	sleep(4);
        XFreeGC(dis, gc);

}
